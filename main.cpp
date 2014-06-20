#include <iostream>
#include "Board.hpp"
#include <string>

int toInt(char c) {
  switch(c) {
    case 'A': case 'a': return 1; break;
    case 'B': case 'b': return 2; break;
    case 'C': case 'c': return 3; break;
    case 'D': case 'd': return 4; break;
    case 'E': case 'e': return 5; break;
    case 'F': case 'f': return 6; break;
    case 'G': case 'g': return 7; break;
    case 'H': case 'h': return 8; break;
    case '1': return 1; break;
    case '2': return 2; break;
    case '3': return 3; break;
    case '4': return 4; break;
    case '5': return 5; break;
    case '6': return 6; break;
    case '7': return 7; break;
    case '8': return 8; break;
    default: return 10; break;
  }
}

int main( int argc, char ** argv ) {
  Board * board = new Board();
  bool quit = false;
  std::string con;
  int r1, r2;
  char c1, c2;
  int col1, col2;
  do {
    board->print( std::cout );

    do {
    std::cout << "Move? ";
    std::cin >> c1 >> r1 >> c2 >> r2;
    col1 = toInt(c1);
    col2 = toInt(c2);
    } while(! board->move( col1 + 1, r1, col2 + 1, r2 ) );
    board->nextMove();


    std::cout << "Continue? ";
    std::cin >> con;
    if( con[0] == 'N' || con[0] == 'n' ) {
      quit = true;
    }
  } while(! quit );
  
  delete board;
  return 0;
}
