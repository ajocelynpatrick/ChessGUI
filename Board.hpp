#ifndef _BOARD_HPP_
#define _BOARD_HPP_

#include <iostream>
#include <memory>
#include <cmath>
#include <vector>
#include <cassert>

class Board {
public:
  typedef int Piece;
  enum PieceType { Square = 0,
		   WPawn, WKnight, WBishop, WRook, WQueen, WKing,
		   BPawn, BKnight, BBishop, BRook, BQueen, BKing,
		   FILLED = 999
  };
  enum { BOARD_SIZE = 12, A = 2, B = 3, C = 4, D = 5, E = 6, F = 7, G = 8, H = 9 };
  enum Color { Black = 0, White = 1 };
  enum CastleType { QueenSide = 0, KingSide = 1 };

public:
  Board();
  void print( std::ostream& os ) const;
  void debugPrint( std::ostream& os ) const;
  void setup();
  void castle( CastleType type );
  Piece& square(const int column, const int rank);
  const Piece& square(const int column, const int rank) const;
  bool move(int col1, int rank1, int col2, int rank2);
  void nextMove() { whiteToMove_ ^= true; }
  bool isWhitePiece(Piece piece) const;
  bool isBlackPiece(Piece piece) const;
  void printPiece(int piece) const;
private:
  bool canCastle( CastleType type ) const;
  bool checkDiagnol(int col1, int rank1, int col2, int rank2) const;
  bool checkStraightLines(int col1, int rank1, int col2, int rank2) const;
  bool movePawn(int col1, int rank1, int col2, int rank2);
  bool moveKnight(int col1, int rank1, int col2, int rank2);
  bool moveBishop(int col1, int rank1, int col2, int rank2);
  bool moveRook(int col1, int rank1, int col2, int rank2);
  bool moveQueen(int col1, int rank1, int col2, int rank2);
  bool moveKing(int col1, int rank1, int col2, int rank2);
  bool canMoveRook(int col1, int rank1, int col2, int rank2) const;
  bool canMoveQueen(int col1, int rank1, int col2, int rank2) const;
  bool canMoveBishop(int col1, int rank1, int col2, int rank2) const;
  bool checkPieceOkayToMove(int col1, int rank1, int col2, int rank2) const;
  
  struct Move {
    PieceType piece_;
    int from[2];
    int to[2];
    bool castleKS_;
    bool castleQS_;
    Color whoseMove_;
    bool isCapture_;
    bool isCheck_;
  };

  bool whiteToMove_;
  bool whiteKingHasMoved_;
  bool whiteKRookHasMoved_;
  bool whiteQRookHasMoved_;
  bool blackKingHasMoved_;
  bool blackKRookHasMoved_;
  bool blackQRookHasMoved_;
  int movesSincePawnMove_;
  std::vector<bool> whitePawnsMoved_;
  std::vector<bool> blackPawnsMoved_;

  //std::vector<Position> listOfPositions_;
  std::vector<Move> moves_;
  Piece board_[BOARD_SIZE][BOARD_SIZE];
};

#endif
