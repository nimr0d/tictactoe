#include <algorithm>
#include <iostream>
#include <sstream>
#include <ctime>

#include "bitboard.h"
#include "s_base.h"
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

class BotIO {

public:

    BotIO() {
    	b_.b0 = Bitboard(0ULL, 0ULL);
    	b_.b1 = Bitboard(0ULL, 0ULL);
    	b_.free = ~Bitboard(0ULL, 0ULL);
    	b_.move = SQUARE_NONE;
        // field_.resize(81);
        // macroboard_.resize(9);

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
    	Square s = think(b_, moveTime(timebank_, timePerMove_, t, b_.free.popcount()) + std::time(0));
    	b_.b0 |= SquareBB[s];
    	b_.move = s;
    	updateFree(s, true);
    	std::cerr << "action:\n";
    	print(b_);
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

    void updateFree(Square move, bool p0) {
    	b_.free &= ~SquareBB[move];
    	Square ls = lSquare(move);
    	print(Smallboard(b_.b1, ls));
    	if (EndBase[Smallboard(p0 ? b_.b0 : b_.b1, ls)]) {
    		b_.free &= ~LSquareBB[ls];
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
            for (Square i = 0; i < rawValues.size(); ++i) {
            	int s = stringToInt(rawValues[i]);
            	if (s != 0 && s != botId_) {
            		Bitboard n_b = b_.b1 | SquareBB[i];
        			if (n_b != b_.b1) {
        				b_.b1 = n_b;
        				b_.move = i;
        				updateFree(i, false);
        				break;
        			}
            	}
            }
            std::cerr << "update:\n";
            print(b_);
        }
        else if (type == "macroboard") {
            /*std::vector<std::string> rawValues;
            split(value, ',', rawValues);
            std::vector<int>::iterator choice = (type == "field" ? field_.begin() : macroboard_.begin());
            std::transform(rawValues.begin(), rawValues.end(), choice, stringToInt);*/

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
            botId_ = stringToInt(value);
        }
        else {
            debug("Unknown setting <" + type + ">.");
        }
    }

    void debug(const std::string &s) const{
        std::cerr << s << std::endl << std::flush;
    }

private:
    // static settings
    int timebank_;
    int timePerMove_;
    int botId_;
    std::vector<std::string> playerNames_;
    std::string myName_;

    // dynamic settings
    int round_;
    int move_;

    // std::vector<int> macroboard_;
    // std::vector<int> field_;
    Board b_;
};

int main() {
	Bitboards::init();
	SBase::init();

    BotIO bot;
    bot.loop();
    return 0;
}