#include <algorithm>
#include <iostream>
#include <sstream>

#include "base.h"
#include "board.h"
#include "position.h"
#include "search.h"
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
    	Square s = think(field_, macroboard_, lsCount_, numFin_, numFree_, botId_, t, timePerMove_, move_);
        
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
            for (Square i = 0; i < 81; ++i) {
                Square ct = contLS[s], mg = posLS[s];
                if (rawValues[i] != position->get_piece(i)) {
                    position->do_move(i);
                } 
            }
        }
        else if (type == "macroboard") {
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

                Piece p = field[9 * i + j];
                char c;
                if (p == 0) {
                    c = '_';
                } else if (p == 1) {
                    c = 'X';
                } else {
                    c = 'O';
                }
                std::cerr << c << " ";
                if (j % 3 == 2) {
                    std::cerr << " ";
                }
            }
            if (i % 3 == 2) {
                std::cerr << "\n";
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
    u32 round_;
    u32 move_;

    Position *pos;
};

int main() {
    Boards::init();
    Base::init();  

    BotIO bot;
    bot.loop();
    return 0;
}