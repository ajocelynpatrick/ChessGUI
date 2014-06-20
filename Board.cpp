#include "Board.hpp"

Board::Board() :
  whiteToMove_( true ),
  whiteKingHasMoved_( false ),
  whiteKRookHasMoved_( false ),
  whiteQRookHasMoved_( false ),
  blackKingHasMoved_( false ),
  blackKRookHasMoved_( false ),
  blackQRookHasMoved_( false ),
  movesSincePawnMove_( 0 )
{
  setup();
}

void Board::setup() {
  // TODO
  // don't fill in squares that I'm going to change
  // later anyways
  for (int i = 0; i < BOARD_SIZE; ++i) {
    for (int j = 0; j < BOARD_SIZE; ++j) {
      board_[i][j] = Square;
    }
  }
  
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < BOARD_SIZE; ++j) {
      board_[i][j] = FILLED;
      board_[i+10][j] = FILLED;
      board_[j][i] = FILLED;
      board_[j][i+10] = FILLED;
    }
  }

  square( A, 2 ) = WPawn;
  square( B, 2 ) = WPawn;
  square( C, 2 ) = WPawn;
  square( D, 2 ) = WPawn;
  square( E, 2 ) = WPawn;
  square( F, 2 ) = WPawn;
  square( G, 2 ) = WPawn;
  square( H, 2 ) = WPawn;
  square( A, 1 ) = WRook;
  square( B, 1 ) = WKnight;
  square( C, 1 ) = WBishop;
  square( D, 1 ) = WQueen;
  square( E, 1 ) = WKing;
  square( F, 1 ) = WBishop;
  square( G, 1 ) = WKnight;
  square( H, 1 ) = WRook;

  square( A, 7 ) = BPawn;
  square( B, 7 ) = BPawn;
  square( C, 7 ) = BPawn;
  square( D, 7 ) = BPawn;
  square( E, 7 ) = BPawn;
  square( F, 7 ) = BPawn;
  square( G, 7 ) = BPawn;
  square( H, 7 ) = BPawn;
  square( A, 8 ) = BRook;
  square( B, 8 ) = BKnight;
  square( C, 8 ) = BBishop;
  square( D, 8 ) = BQueen;
  square( E, 8 ) = BKing;
  square( F, 8 ) = BBishop;
  square( G, 8 ) = BKnight;
  square( H, 8 ) = BRook;
}

const Board::Piece & Board::square( const int column, const int rank ) const {
  int c = column, r = rank + 1;
  assert( c > 0 && c < BOARD_SIZE && r > 0 && r < BOARD_SIZE );
  return (board_[r][c]);
}

Board::Piece & Board::square( const int column, const int rank ) {
  int c = column, r = rank + 1;
  assert(c < BOARD_SIZE && r < BOARD_SIZE);
  return (board_[r][c]);
}

void Board::print( std::ostream& os ) const {
  bool color = true;
  for( int i = (BOARD_SIZE - 3); i >= 2; --i ) {
    os << "  ---------------------------------" << std::endl;
    os << i - 1 << " |";
    for( int j = 2; j < (BOARD_SIZE - 2); ++j ) {
      if( board_[i][j] == WPawn ) {
	os << " P |";
      } else if( board_[i][j] == WKnight ) {
	os << " N |";
      } else if( board_[i][j] == WBishop ) {
	os << " B |";
      } else if( board_[i][j] == WRook ) {
	os << " R |";
      } else if( board_[i][j] == WQueen ) {
	os << " Q |";
      } else if( board_[i][j] == WKing ) {
	os << " K |";
      } else if( board_[i][j] == BPawn ) {
	os << " p |";
      } else if( board_[i][j] == BKnight ) {
	os << " n |";
      } else if( board_[i][j] == BBishop ) {
	os << " b |";
      } else if( board_[i][j] == BRook ) {
	os << " r |";
      } else if( board_[i][j] == BQueen ) {
	os << " q |";
      } else if( board_[i][j] == BKing ) {
	os << " k |";
      } else {
	if( color ) {
	  os << "   |";
	} else {
	  os << "---|";
	}
      }
      color ^= true;
    }
    os << std::endl;
    color ^= true;
  }
  os << "  ---------------------------------" << std::endl;
  os << "    a   b   c   d   e   f   g   h" << std::endl;
}

bool Board::canCastle( CastleType type ) const {
  if(whiteToMove_) {
    return (type == KingSide) ? !(whiteKingHasMoved_ && whiteKRookHasMoved_) 
      && (square(F,1) == Square) && (square(G,1) == Square)
	  :
      !(whiteKingHasMoved_ && whiteQRookHasMoved_) &&
      (square(B,1) == Square) && (square(C,1) == Square) && (square(D,1) == Square);
  } else { // black to move
    return (type == KingSide) ? !(blackKingHasMoved_ && blackKRookHasMoved_) 
      && (square(F,1) == Square) && (square(G,1) == Square)
	  :
      !(blackKingHasMoved_ && blackQRookHasMoved_) &&
      (square(B,1) == Square) && (square(C,1) == Square) && (square(D,1) == Square);
  }
}

void Board::castle( CastleType type ) {
  //  assert( canCastle( type ) );

  if (whiteToMove_) {
    if (type == KingSide) {
      square(G, 1) = WKing;
      square(F, 1) = WRook;
      square(H, 1) = Square;
      square(E, 1) = Square;
      whiteKingHasMoved_ = true;
      whiteKRookHasMoved_ = true;
    } else { // QueenSide
      square(C, 1) = WKing;
      square(D, 1) = WRook;
      square(A, 1) = Square;
      square(E, 1) = Square;
      whiteKingHasMoved_ = true;
      whiteKRookHasMoved_ = true;
    }
  } else { // black to move
    if (type == KingSide) {
      square(G,8) = BKing;
      square(F,8) = BRook;
      square(E,8) = Square;
      square(H,8) = Square;
    } else { // QueenSide
      square(C,8) = BKing;
      square(D,8) = BRook;
      square(A,8) = Square;
      square(E,8) = Square;
    }
  }
}

void Board::debugPrint( std::ostream& os ) const {
  bool color = true;
  for( int i = (BOARD_SIZE - 1); i >= 0; --i ) {
    os << "   -------------------------------------------------" << std::endl;
    os << "  " << " |";
    for( int j = 0; j < BOARD_SIZE; ++j ) {
      if( board_[i][j] == WPawn ) {
	os << " P |";
      } else if( board_[i][j] == WKnight ) {
	os << " N |";
      } else if( board_[i][j] == WBishop ) {
	os << " B |";
      } else if( board_[i][j] == WRook ) {
	os << " R |";
      } else if( board_[i][j] == WQueen ) {
	os << " Q |";
      } else if( board_[i][j] == WKing ) {
	os << " K |";
      } else if( board_[i][j] == BPawn ) {
	os << " p |";
      } else if( board_[i][j] == BKnight ) {
	os << " n |";
      } else if( board_[i][j] == BBishop ) {
	os << " b |";
      } else if( board_[i][j] == BRook ) {
	os << " r |";
      } else if( board_[i][j] == BQueen ) {
	os << " q |";
      } else if( board_[i][j] == BKing ) {
	os << " k |";
      } else if( board_[i][j] == FILLED ) {
	os << "XXX|";
      } else {
	if( color ) {
	  os << "   |";
	} else {
	  os << "---|";
	}
      }
      color ^= true;
    }
    os << std::endl;
    color ^= true;
  }
    os << "   -------------------------------------------------" << std::endl;
}

bool Board::move(int col1, int rank1, int col2, int rank2) {
  if( col1 <= 0 && col1 >= BOARD_SIZE && rank1 <= 0 && rank1 >= BOARD_SIZE ) {
    return false;
  }
  if( col2 <= 0 && col2 >= BOARD_SIZE && rank2 <= 0 && rank2 >= BOARD_SIZE ) {
    return false;
  }
  if (col1 == col2 && rank1 == rank2) {
    return false;
  }
  
  Piece& fromSquare = square(col1, rank1);
  Piece& toSquare = square(col2, rank2);
  
  if(fromSquare == Square || fromSquare == FILLED || toSquare == FILLED) {
    return false;
  }

  if (fromSquare == WPawn || fromSquare == BPawn) {
    if (movePawn(col1, rank1, col2, rank2)) {
      movesSincePawnMove_ = 0;
      return true;
    } else {
      return false;
    }
  } else if (fromSquare == WKnight || fromSquare == BKnight) {
    if (moveKnight(col1, rank1, col2, rank2)) {
      movesSincePawnMove_++;
      return true;
    } else {
      return false;
    }
  } else if (fromSquare == WBishop || fromSquare == BBishop) {
    if (moveBishop(col1, rank1, col2, rank2)) {
      movesSincePawnMove_++;
      return true;
    } else {
      return false;
    }
  } else if (fromSquare == WRook || fromSquare == BRook) {
    if (moveRook(col1, rank1, col2, rank2)) {
      movesSincePawnMove_++;
      return true;
    } else {
      return false;
    }
  } else if (fromSquare == WQueen || fromSquare == BQueen) {
    if (moveQueen(col1, rank1, col2, rank2)) {
      movesSincePawnMove_++;
      return true;
    } else {
      return false;
    }
  } else if (fromSquare == WKing || fromSquare == BKing) {
    if (moveKing(col1, rank1, col2, rank2)) {
      if (whiteToMove_) {
        whiteKingHasMoved_ = true;
      } else {
        blackKingHasMoved_ = true;
      }
      movesSincePawnMove_++;
      return true;
    } else {
      return false;
    }
  } else {
    return false;
  }
}

bool Board::movePawn(int col1, int rank1, int col2, int rank2) {
  // TODO
  // Add en passant rules
  Piece& fromSquare = square(col1, rank1);
  Piece& toSquare = square(col2, rank2);

  if(whiteToMove_ && (fromSquare == BKing || fromSquare == BQueen || fromSquare == BBishop ||
		     fromSquare == BKnight || fromSquare == BRook || fromSquare == BPawn )) {
    std::cout << "LOG: (W) Trying to move other player's piece" << std::endl;
  } else if(!whiteToMove_ && (fromSquare == WKing || fromSquare == WQueen || fromSquare == WBishop ||
		     fromSquare == WKnight || fromSquare == WRook || fromSquare == WPawn )) {
    std::cout << "LOG: (B) Trying to move other player's piece" << std::endl;
  } else if(!whiteToMove_ && (toSquare == BKing || toSquare == BQueen || toSquare == BBishop ||
		      toSquare == BKnight || toSquare == BRook || toSquare == BPawn)) {
    std::cout << "LOG: (W) Trying to take own piece" << std::endl;
    return false;
  } else if(whiteToMove_ && (toSquare == WKing || toSquare == WQueen || toSquare == WBishop ||
			      toSquare == WKnight || toSquare == WRook || toSquare == WPawn)) {
    std::cout << "LOG: (B) Trying to take own piece" << std::endl;
    return false;
  }

  // assert( trying to move piece of correct color )

  if(toSquare == Square) { // square is free
    if(col1 != col2) {
      std::cout << "LOG: Columns different, but not capturing a piece" << std::endl;
      return false;
    } else { // moving on same column (col1 == col2)
      if(whiteToMove_) {
	if(rank2 == (rank1 + 1)) { // moving forward 1 space
	  square(col2, rank2) = WPawn;
	  square(col1, rank1) = Square;
	  return true;
	} else if((rank1 == 2) && (rank2 == 4) && (square(col1, 3) == Square)) { // moving 2 spaces
	  square(col2, rank2) = WPawn;
	  square(col1, rank1) = Square;
	  return true;
	} else {
	  std::cout << "LOG: (W) Moving more than 2 square away or squares in between not empty" << std::endl;
	  return false;
	}
      } else { // black to move
	if(rank2 == (rank1 - 1)) { // moving forward 1 space
	  square(col2, rank2) = BPawn;
	  square(col1, rank1) = Square;
	  return true;
	} else if((rank1 == 7) && (rank2 == 5) && (square(col1,6) == Square)) { // moving 2 spaces
	  square(col2, rank2) = BPawn;
	  square(col1, rank1) = Square;
	  return true;
	} else {
	  std::cout << "LOG: (B) Moving more than 2 square away or squares in between not empty" << std::endl;
	  return false;
	}
      }
    }
  } else { // trying to take piece
    if(whiteToMove_) {
      if((rank2 == (rank1 + 1)) && (abs(col2 - col1) == 1)) {
	square(col2, rank2) = WPawn;
	square(col1, rank1) = Square;
	return true;
      } else {
	std::cout << "LOG: (W) Not capturing diagonally one square" << std::endl;
	return false;
      }
    } else { // black to move
      if((rank2 == (rank1 - 1)) && (abs(col2 - col1) == 1)) {
	square(col2, rank2) = BPawn;
	square(col1, rank1) = Square;
	return true;
      } else {
	std::cout << "LOG: (B) Not capturing diagonally one square" << std::endl;
	return false;
      }
    }
  }

  // Never reached
  std::cout << "should never reach here" << std::endl;
  return false;
}

bool Board::moveKnight(int col1, int rank1, int col2, int rank2) {
  if (!checkPieceOkayToMove(col1, rank1, col2, rank2)) {
    return false;
  }

  const int rankDiff = abs(rank2 - rank1);
  const int colDiff = abs(col2 - col1);
  if ((rankDiff == 2 && colDiff == 1) || (rankDiff == 1 && colDiff == 2)) {
    Piece fromSquare = square(col1, rank1);
    square(col1, rank1) = Square;
    square(col2, rank2) = fromSquare;
    return true;
  } else {
    return false;
  }
}

bool Board::checkPieceOkayToMove(int col1, int rank1, int col2, int rank2) const {
  const Piece fromSquare = square(col1, rank1);
  const Piece toSquare = square(col2, rank2);
  
  if (toSquare == FILLED || fromSquare == FILLED) {
    std::cout << "LOG: Square filled" << std::endl;
    return false;
  }

  if (whiteToMove_) {
    if (isBlackPiece(fromSquare)) {
      std::cout << "LOG: (W) Trying to move other player's piece" << std::endl;
      return false;
    }
    if (isWhitePiece(toSquare)) {
      std::cout << "LOG: (W) Trying to take own piece" << std::endl;
      return false;
    }
  } else { // black to move
    if (isWhitePiece(fromSquare)) {
      std::cout << "LOG: (B) Trying to move other player's piece" << std::endl;
      return false;
    }
    if (isBlackPiece(toSquare)) {
      std::cout << "LOG: (B) Trying to take own piece" << std::endl;
      return false;
    }
  }
  
  return true;
}

bool Board::moveBishop(int col1, int rank1, int col2, int rank2) {
  if (!checkPieceOkayToMove(col1, rank1, col2, rank2)) {
    return false;
  } else if (canMoveBishop(col1, rank1, col2, rank2)) {
    const Piece fromSquare = square(col1, rank1);
    square(col2, rank2) = fromSquare;
    square(col1, rank1) = Square;
    return true;
  } else {
    return false;
  }
}

bool Board::checkDiagnol(int col1, int rank1, int col2, int rank2) const {
  int rankDiff = rank2 - rank1;
  int colDiff = col2 - col1;
  
  if (abs(rankDiff) == abs(colDiff)) {
    // Check that not jumping over any pieces
    if (rankDiff < 0 && colDiff < 0) {
      // down left
      int i, j;
      for (i = (col2 + 1), j = (rank2 + 1); (i < col1) && (j < rank1); ++i, ++j) {
        if (square(i,j) != Square) {
          std::cout << "i = " << i << ", j = " << j << std::endl;
          std::cout << square(i,j) << std::endl;
          std::cout << "LOG: (Bishop1) pieces in between to and from square" << std::endl;
          return false;
        }
      }
    } else if (rankDiff < 0 && colDiff > 0) {
      // down right
      int i, j;
      for (i = (col1 + 1), j = (rank1 - 1); (i < col2) && (j > rank2); ++i, --j) {
        if (square(i,j) != Square) {
          std::cout << "i = " << i << ", j = " << j << std::endl;
          std::cout << square(i,j) << std::endl;
          std::cout << "LOG: (Bishop2) pieces in between to and from square" << std::endl;
          return false;
        }
      }
    } else if (rankDiff > 0 && colDiff < 0) {
      // up left
      int i, j;
      for (i = (col2 + 1), j = (rank2 + 1); (i > col1) && (j > rank1); --i, --j) {
        std::cout << "i = " << i << ", j = " << j << std::endl;
        std::cout << square(i,j) << std::endl;
        
        if (square(i,j) != Square) {
          std::cout << "LOG: (Bishop3) pieces in between to and from square" << std::endl;
          return false;
        }
      }
    } else {
      // up right
      int i, j;
      for (i = (col1 + 1), j = (rank1 + 1); (i < col2) && (j < col2); ++i, ++j) {
        if (square(i,j) != Square) {
          std::cout << "i = " << i << ", j = " << j << std::endl;
          std::cout << square(i,j) << std::endl;
          std::cout << "LOG: (Bishop4) pieces in between to and from square" << std::endl;
          return false;
        }
      }
    }
  } else {
    return false;
  }
    
  return true;
}

bool Board::moveRook(int col1, int rank1, int col2, int rank2) {
  if (!checkPieceOkayToMove(col1, rank1, col2, rank2)) {
    return false;
  } else if (canMoveRook(col1, rank1, col2, rank2)) {
    if (col1 == A && rank1 == 1) {
      whiteQRookHasMoved_ = true;
    } else if (col1 == H && rank1 == 1) {
      whiteKRookHasMoved_ = true;
    } else if (col1 == A && rank1 == 8) {
      blackQRookHasMoved_ = true;
    } else if (col1 == H && rank1 == 8) {
      blackKRookHasMoved_ = true;
    }
    
    const Piece fromSquare = square(col1, rank1);
    square(col2, rank2) = fromSquare;
    square(col1, rank1) = Square;
    return true;
  } else {
    return false;
  }
}

bool Board::canMoveRook(int col1, int rank1, int col2, int rank2) const {
  return checkStraightLines (col1, rank1, col2, rank2);
}

bool Board::canMoveQueen(int col1, int rank1, int col2, int rank2) const {
  return (checkStraightLines(col1, rank1, col2, rank2) || checkDiagnol(col1, rank1, col2, rank2));
}

bool Board::canMoveBishop(int col1, int rank1, int col2, int rank2) const {
  return checkDiagnol(col1, rank1, col2, rank2);
}

bool Board::moveQueen(int col1, int rank1, int col2, int rank2) {
  if (!checkPieceOkayToMove(col1, rank1, col2, rank2)) {
    return false;
  } else if (canMoveQueen(col1, rank1, col2, rank2)) {
    const Piece fromSquare = square(col1, rank1);
    square(col2, rank2) = fromSquare;
    square(col1, rank1) = Square;
    return true;
  } else {
    return false;
  }
}

// TODO
// Add check detection
bool Board::moveKing(int col1, int rank1, int col2, int rank2) {
  const Piece fromSquare = square(col1, rank1);
  const Piece toSquare = square(col2, rank2);

  if (!checkPieceOkayToMove(col1, rank1, col2, rank2)) {
    return false;
  }

  //
  // Check if trying to castle
  if (whiteToMove_ && !whiteKingHasMoved_&& rank1 == rank2 && rank1 == 1 && col1 == E) {
    if (col2 == G && !whiteKRookHasMoved_ && square(F,1) == Square && square(G,1) == Square) {
      castle(KingSide);
      return true;
    } else if (col2 == C && !whiteQRookHasMoved_ && square(D,1) == Square && square(C,1) == Square && square(B,1) == Square) {
      castle(QueenSide);
      return true;
    }
  } else if (!whiteToMove_ && !blackKingHasMoved_ && rank1 == rank2 && rank1 == 8 && col1 == E) {
    if (col2 == G && !blackKRookHasMoved_ && square(F,8) == Square && square(G,8) == Square) {
      castle(KingSide);
      return true;
    } else if (col2 == C && !blackQRookHasMoved_ && square(D,8) == Square, square(C,8) == Square && square(B,8) == Square) {
      castle(QueenSide);
      return true;
    }
  }
  
  int colDiff = col2 - col1;
  int rowDiff = rank2 - rank1;

  if (abs(colDiff) <= 1 && abs(rowDiff) <= 1) {
    square(col2, rank2) = fromSquare;
    square(col1, rank1) = Square;
    return true;
  } else {
    return false;
  }
}

bool Board::checkStraightLines(int col1, int rank1, int col2, int rank2) const {
  if (col1 == col2) {
    if (rank1 < rank2) {
        for (int i = (rank1 + 1); i < rank2; ++i) {
          if (square(col1,i) != Square) {
            return false;
          }
        }
    } else if (rank2 < rank1) {
      for (int i = (rank2 + 1); i < rank1; ++i) {
        if (square(col1,i) != Square) {
          return false;
        }
      }
    } else { // trying to move to square already on...
      return false;
    }
  } else if (rank1 == rank2) {
    if (col1 < col2) {
      for (int i = (col1 + 1); i < col2; ++i) {
        if (square(i, rank1) != Square) {
          return false;
        }
      }
    } else if (col2 < col1) {
      for (int i = (col2 + 1); i < col1; ++i) {
        if (square(i, rank1) != Square) {
          return false;
        }
      }
    } else { // trying to move to square already on...
      return false;
    }
  } else {
    return false;
  }

  return true;
}

bool Board::isWhitePiece(Piece piece) const {
  return (piece == WPawn || piece == WKnight || piece == WBishop ||
          piece == WRook || piece == WQueen || piece == WKing);
}

bool Board::isBlackPiece(Piece piece) const {
  return (piece == BPawn || piece == BKnight || piece == BBishop ||
          piece == BRook || piece == BQueen || piece == BKing);
}

void Board::printPiece(int piece) const {
  if (piece == WPawn) {
    std::cout << "P" << std::endl;
  } else if (piece == WKnight) {
    std::cout << "N" << std::endl;
  } else if (piece == WBishop) {
    std::cout << "B" << std::endl;
  } else if (piece == WRook) {
    std::cout << "R" << std::endl;
  } else if (piece == WQueen) {
    std::cout << "Q" << std::endl;
  } else if (piece == WKing) {
    std::cout << "K" << std::endl;
  } else if (piece == Square) {
    std::cout << "Square" << std::endl;
  } else if (piece == BPawn) {
    std::cout << "p" << std::endl;
  } else if (piece == BKnight) {
    std::cout << "n" << std::endl;
  } else if (piece == BBishop) {
    std::cout << "b" << std::endl;
  } else if (piece == BRook) {
    std::cout << "r" << std::endl;
  } else if (piece == BQueen) {
    std::cout << "q" << std::endl;
  } else if (piece == BKing) {
    std::cout << "k" << std::endl;
  } else if (piece == FILLED) {
    std::cout << "Filled" << std::endl;
  } else {
    std::cout << "Unknown" << std::endl;
  }
}
