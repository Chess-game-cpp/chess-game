#pragma once
/*
rank
1-Pawn
2-Rook
3-knight
4-Bishop
5-Queen
6-King
color
0-white
1-black
*/
// array of chess piece character symbols
char pcs[7] = {' ', 'p', 'r', 'n', 'b', 'q', 'k'};


// ChessPiece class to represent a chess piece
class ChessPiece
{
  int rank;
  int color;
  Box position;
  Box moves[64]; // available moves
  bool castling; // castling available?
  friend class Board;

public:
  int totalmoves; // total legal moves

  ChessPiece(int rank = 0, int color = 10, bool castling = false)
  {
    // blank chess piece creation
    this->rank = rank;
    this->color = color;
    this->castling = castling;
  };

  void display_string()
  {
    // display char symbol of given chess Piece eg. for black pawn "p" and for white pawn "P"
    if (this->rank == 0)
    {
      std::cout << "  ";
    }
    else
    {
      std::cout << (char((pcs[this->rank] - 32) + (this->color * 32))) << " ";
    }
  }
  Box get_position()
  {
    return position;
  }
  Box *get_moves()
  {
    return moves;
  }
  int get_rank()
  {
    return rank;
  }
  int get_color()
  {
    return color;
  }

private:
  void set_castling(bool cast)
  {
    // set castling
    this->castling = cast;
  }
  void set_color(int color)
  {
    // set color
    this->color = color;
  }
  void set_rank(int rank)
  {
    // update the rank
    this->rank = rank;
  }
  void setPosition(int x, int y)
  {
    // update the position
    position.x = x;
    position.y = y;
  }
  void generateLegalMoves(Board &);
  void generatepseudoMoves(Board &);
  void knight(int, int, Board &);
  void bishop(int, int, Board &);
  void rook(int, int, Board &);
  void removeMoves(int);
};
