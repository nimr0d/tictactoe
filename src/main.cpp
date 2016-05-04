#include <algorithm>
#include <iostream>
#include <sstream>
#include <ctime>

#include "base.h"
#include "board.h"
#include "search.h"
#include "time_mgmt.h"
#include "types.h"


std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    elems.clear();
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


int stringToInt(const std::string &s) {
    std::istringstream ss(s);
    int result;
    ss >> result;
    return result;
}

Piece stringToPiece(const std::string &s) {
    return static_cast<Piece>(stringToInt(s));
}

class BotIO {

public:

    BotIO() {

    }

    void loop() {
        std::string line;
        std::vector<std::string> command;
        command.reserve(256);

        while (std::getline(std::cin, line)) {
        	std::cerr << line << "\n";
            processCommand(split(line, ' ', command));
        }
    }

private:

    std::pair<int, int> action(const std::string &type, int t) {

        if (move_ == 1) {
            return std::pair<int, int>(4, 4);
        }

    	Square s = think(field_, macroboard_, lsCount_, numFin_, botId_, t);
        
        printfield(field_);

        return std::pair<int, int>(s % 9, s / 9);
    }

    void processCommand(const std::vector<std::string> &command) {
    	if (command.empty()) {

    	}
        else if (command[0] == "action") {
            auto point = action(command[1], stringToInt(command[2]));
            std::cout << "place_move " << point.first << " " << point.second << std::endl << std::flush;
        }
        else if (command[0] == "update") {
            update(command[1], command[2], command[3]);
        }
        else if (command[0] == "settings") {
            setting(command[1], command[2]);
        }
        else {
            debug("Unknown command <" + command[0] + ">.");
        }
    }

    void update(const std::string& player, const std::string& type, const std::string& value) {
        if (player != "game" && player != myName_) {
            return;
        }
        if (type == "round") {
            round_ = stringToInt(value);

        }
        else if (type == "move") {
            move_ = stringToInt(value);
        }
        else if (type == "field") {
            std::vector<std::string> rawValues;
            split(value, ',', rawValues);
            std::fill(lsCount_, lsCount_ + 9, 0);
            numFree_ = 0;
            for (Square i = 0; i < 81; ++i) {
                Piece p = stringToPiece(rawValues[i]);
                field_[i] = p;
                if (p != NONE) {
                    ++lsCount_[StLS2[i]];
                } else {
                    ++numFree_;
                }
            }
        }
        else if (type == "macroboard") {
            std::vector<std::string> rawValues;
            split(value, ',', rawValues);
            numFin_ = 0;
            for (Square i = 0; i < 9; ++i) {
                Piece p = stringToPiece(rawValues[i]);
                bb_set(macroboard_, p, i);
                if (p == P0 || p == P1 || lsCount_[i] >= 9) {
                    ++numFin_;
                }
            }
        }
        else {
            debug("Unknown update <" + type + ">.");
        }
    }

    void setting(const std::string& type, const std::string& value) {
        if (type == "timebank") {
            timebank_ = stringToInt(value);
        }
        else if (type == "time_per_move") {
            timePerMove_ = stringToInt(value);
        }
        else if (type == "player_names") {
            split(value, ',', playerNames_);
        }
        else if (type == "your_bot") {
            myName_ = value;
        }
        else if (type == "your_botid") {
            botId_ = stringToPiece(value);
        }
        else {
            debug("Unknown setting <" + type + ">.");
        }
    }

    void debug(const std::string &s) const{
        std::cerr << s << std::endl << std::flush;
    }

    void printfield(Piece *field) {
        for (Square i = 0; i < 9; ++i) {
            for (Square j = 0; j < 9; ++j) {
                std::cerr << field[9 * i + j] << " ";
            }
            std::cerr << "\n";
        }
    }

    void printlsc(u8 *lsc) {
        for (Square i = 0; i < 3; ++i) {
            for (Square j = 0; j < 3; ++j) {
                std::cerr << int(lsc[3 * i + j]) << " ";
            }
            std::cerr << "\n";
        }
    }

private:
    // static settings
    int timebank_;
    int timePerMove_;
    Piece botId_;
    std::vector<std::string> playerNames_;
    std::string myName_;

    // dynamic settings
    int round_;
    int move_;

    Piece field_[81];
    Bitboard macroboard_;
    u8 lsCount_[9];
    u8 numFin_;
    u8 numFree_;
};

int main() {
    Boards::init();
    Base::init();  

    BotIO bot;
    bot.loop();
    return 0;
}