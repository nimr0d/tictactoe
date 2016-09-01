#include <iostream>
#include <sstream>
#include <string>

#include "base.h"
#include "board.h"
#include "position.h"
#include "search.h"
#include "types.h"

int main() {
    Boards::init();
    Base::init();  

    Position *pos = new Position();
    SSquare i, j, prev;
    for (std::string line; std::getline(std::cin, line);) {
      if (line.size() >= 3) {
        int x = int(line[0]) - int('0'), y = int(line[2]) - int('0');
        if (0 <= x && x < 9 && 0 <= y && y < 9) {
          Square s = 9 * x + y;
          i = StLS[s][0];
          j = StLS[s][1];          
          prev = pos->do_move(i, j);
        }
      } else if (line == "s") {
        std::cerr << think(pos) << "\n";
        std::cerr << "Search\n"; 
      } else if (line == "u") {
        pos->undo_move(i, j, prev);
        std::cerr << "Undo\n"; 
      } else if (line == "c") {
        pos->clear();
        std::cerr << "Clear\n";
      }
      pos->print();
    }
}