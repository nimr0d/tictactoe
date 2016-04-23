#include <algorithm>
#include <iostream>
#include <sstream>
#include <time.h>

#include "bitboard.h"
#include "s_base.h"
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

/**
 * This class implements all IO operations.
 * Only one method must be realized:
 *
 *      > BotIO::action
 *
 */
class BotIO {

public:

    /**
     * Initialize your bot here.
     */
    BotIO() {
        srand(static_cast<unsigned int>(time(0)));
        field_.resize(81);
        macroboard_.resize(9);

    }


    void loop() {
        std::string line;
        std::vector<std::string> command;
        command.reserve(256);

        while (std::getline(std::cin, line)) {
            processCommand(split(line, ' ', command));
        }
    }

private:

    std::pair<int, int> action(const std::string &type, int time) {
        return std::pair<int, int>();
    }

    void processCommand(const std::vector<std::string> &command) {
        if (command[0] == "action") {
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
            // It's not my update!
            return;
        }

        if (type == "round") {
            round_ = stringToInt(value);
        }
        else if (type == "move") {
            move_ = stringToInt(value);
        }
        else if (type == "macroboard" || type == "field") {
            std::vector<std::string> rawValues;
            split(value, ',', rawValues);
            std::vector<int>::iterator choice = (type == "field" ? field_.begin() : macroboard_.begin());
            std::transform(rawValues.begin(), rawValues.end(), choice, stringToInt);
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
    std::vector<int> macroboard_;
    std::vector<int> field_;
};

int main() {
	Bitboards::init();
	SBase::init();

    BotIO bot;
    bot.loop();
    return 0;
}