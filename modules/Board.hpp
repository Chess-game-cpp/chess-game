#pragma once
#include "Pieces.hpp"
#include <math.h>
#include <iostream>
#include <string>
ChessPiece get_piece(char a)
{
    // Create Chess Peice from the Character
    ChessPiece temp;
    if (a < 97)
    {
        // White(1) for upperc◘ase
        temp.set_color(0);
        // converting to Lowercase
        a += 32;
    }
    else
    {
        // Black(0) for Lowercase
        temp.set_color(1);
    }
    switch (a)
    {
    case 'p':
        // pawn
        temp.set_rank(1);
        break;
    case 'r':
        // rook
        temp.set_rank(2);
        temp.set_castling(true);
        break;
    case 'n':
        // knight
        temp.set_rank(3);
        break;
    case 'b':
        // bishop
        temp.set_rank(4);
        break;
    case 'q':
        // queen
        temp.set_rank(5);
        break;
    case 'k':
        // king
        temp.set_rank(6);
        temp.set_castling(true);
        break;

    default:
        break;
    }

    return temp;
}
// Board Class here
class Board
{
    ChessPiece chessBoard[8][8]; // Array for Board
    ChessPiece captured[2][16];  // Array for Captured Pices
    bool castling[2][2];         // Available Castling
    int currentTurn;
    friend class ChessPiece;
    Box enpasant; // enpasant available box
    friend class GameScreen;

public:
    Board()
    {
        // parse_fen("8/PPPPPPPP/8/4k3/8/8/PPPPPPPP/R3K2R w KQkq -");
        parse_fen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq -");
        // parse_fen("rnbqkbnr/pppppppp/8/8/8/8/pPPPPPPP/1NBQKBNR w KQkq -");
        // parse_fen("rnbqkbnr/1ppppppp/p7/4P3/8/8/PPPP1PPP/RNBQKBNR b kqKQ -");
        // parse_fen("rnbqkbnr/1ppppppp/p2r4/4P3/8/8/P4PPP/R3KBNR w kqKQ -");
        // parse_fen("rnbqkbnr/1ppppppp/8/p7/8/4PQ2/PPPP1PPP/RNB1KBNR b");
    }
    void parse_fen(std::string fen)
    {
        // parse fen string to add pieces to board
        int x = 0;
        int y = 0;
        int i = 0;
        // chess Pieces
        while (fen[i] != ' ')
        {
            if (fen[i] == '/')
            {
                x += 1;
                y = 0;
            }
            else if ((fen[i] - 48) > 0 && (fen[i] - 48) < 9)
            {
                y += (fen[i] - 48);
            }
            else
            {
                chessBoard[x][y] = get_piece(fen[i]);
                chessBoard[x][y].setPosition(x, y);

                y += 1;
            }
            i += 1;
        }
        // turn
        i += 1;
        if (fen[i] == 'w')
        {
            currentTurn = 0;
        }
        else if (fen[i] == 'b')
        {
            currentTurn = 1;
        }
        i += 2;
        // castling
        castling[0][0] = false;
        castling[0][1] = false;
        castling[1][0] = false;
        castling[1][1] = false;
        while (fen[i] != ' ')
        {
            switch (fen[i])
            {
            case 'k':
                // King side White
                castling[1][0] = true;
                break;
            case 'K':
                // King Side black
                castling[0][0] = true;
                break;
            case 'Q':
                // Queen side white
                castling[0][1] = true;
                break;
            case 'q':
                // Queen side black
                castling[1][1] = true;
                break;
            default:
                break;
            }

            i += 1;
        }
        // enpasant
        i += 1;
        if (fen[i] == '-')
        {
            // no enpasant possible
        }
        else
        {
            enpasant.y = fen[i] - 97;
            enpasant.x = 56 - fen[i + 1];
        }
    }
    void print_board()
    {
        // function to print chess piece array in console
        std::cout << std::endl
                  << std::endl;
        int i, j;
        std::cout << "  0 1 2 3 4 5 6 7" << std::endl;
        for (i = 0; i < 8; i++)
        {
            std::cout << i << " ";
            for (j = 0; j < 8; j++)
            {
                chessBoard[i][j].display_string();
            }
            std::cout << std::endl;
        }
    }
    int get_turn()
    {
        // function to get currentTurn
        return this->currentTurn;
    }
    void switch_turn()
    {
        // function to switch turn
        this->currentTurn = !this->currentTurn;
    }
    int capture_insertIndex(int color)
    {
        // get total number of captured piece
        for (int i = 0; i < 16; i++)
        {
            if (captured[color][i].rank == 0)
            {
                return i;
            }
        }
        return 15;
    }
    Box get_king_position(int color)
    {
        // function to get current position of King of color 0 or 1
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if ((chessBoard[i][j].rank == 6) && (chessBoard[i][j].color == color))
                {
                    return chessBoard[i][j].position;
                }
            }
        }
        return Box();
    }
    ChessPiece &get_chesspiece(int x, int y)
    {
        // get reference to a chesspiece in position x,y
        return chessBoard[x][y];
    }
    int move_piece(ChessPiece pc, Box b, bool legal = true)
    {
        // update chess board by moving the piece if possible
        int displacement = sqrt(pow((pc.position.x - b.x), 2) + pow((pc.position.y - b.y), 2));
        if (legal)
        {
            int isLegal = 0;
            // check if the move is legal
            for (int i = 0; i < pc.totalmoves; i++)
            {
                if (pc.moves[i] == b)
                {
                    isLegal = 1;
                    break;
                }
            }

            if (!isLegal)
                return 2; // if move is illegal return 2
        }
        ChessPiece capturedpiece = chessBoard[b.x][b.y];
        if (capturedpiece.rank > 0)
        {
            // add to captured piece array
            captured[!pc.color][this->capture_insertIndex(!pc.color)] = capturedpiece;
        }

        // if king is moved castling is not possible
        if (pc.rank == 6)
        {
            castling[currentTurn][0] = false;
            castling[currentTurn][1] = false;
        }
        // if rook is moved castling not possible at that side
        if (pc.rank == 2 && pc.position == Box(0, currentTurn * 7))
        {
            castling[currentTurn][1] = false;
        }
        // if rook is moved castling not possible at that side
        if (pc.rank == 2 && pc.position == Box(7, currentTurn * 7))
        {
            castling[currentTurn][0] = false;
        }
        //remove captured piece in enpasant
        if ((this->enpasant.is_valid()) && (pc.rank == 1) && (b == this->enpasant))
        {
            captured[!pc.color][this->capture_insertIndex(!pc.color)] = chessBoard[pc.position.x][b.y];

            chessBoard[pc.position.x][b.y] = ChessPiece();
        }
        // for castling: King moves two positons
        if (displacement == 2 && pc.rank == 6)
        {
            if (pc.position.y > b.y)
            {
                //updating positon of castled rook
                chessBoard[b.x][b.y + 1] = chessBoard[!this->currentTurn * 7][0];
                chessBoard[b.x][b.y + 1].position = Box(b.x, b.y + 1);
                chessBoard[!this->currentTurn * 7][0] = ChessPiece();
            }
            else
            {
                //updating positon of castled rook
                chessBoard[b.x][b.y - 1] = chessBoard[!this->currentTurn * 7][7];
                chessBoard[b.x][b.y - 1].position = Box(b.x, b.y - 1);
                chessBoard[!this->currentTurn * 7][7] = ChessPiece();
            }
            //removing castling available
            castling[this->currentTurn][0] = false;
            castling[this->currentTurn][1] = false;
        }
        //removing chess piece from the previous position
        chessBoard[pc.position.x][pc.position.y] = ChessPiece();
        //updating the position of chesspiece
        pc.position = b;
        //adding to board array
        chessBoard[b.x][b.y] = pc;
        this->enpasant = Box();

        //another player can capture by enpasant
        if (displacement == 2 && pc.rank == 1)
        {
            this->enpasant = Box(b.x + 1 + (-2 * this->currentTurn), b.y);
        }
        if (legal)
        {
            //return if next player will be in checkmate after the move

            return this->check_checkmate(!pc.color);
        }
        else
        {
            //return if current  player will be in checkmate after the move
            return this->check_checkmate(pc.color);
        }
    }
    bool check_checkmate(int player)
    {
        // check if player is in check
        Box king = this->get_king_position(player);
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if (chessBoard[i][j].color != player)
                {
                    chessBoard[i][j].generatepseudoMoves(*this);
                    for (int k = 0; k < chessBoard[i][j].totalmoves; k++)
                    {
                        if (chessBoard[i][j].moves[k] == king)
                        { // check if generated moves for another player captures the king

                            return 1;
                        }
                    }
                }
            }
        }

        return 0;
    }
    void generateMoves()
    {
        // calcultae legal move for every piece of current turn player
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if (this->chessBoard[i][j].color == this->currentTurn)
                {

                    this->chessBoard[i][j].generateLegalMoves(*this);
                }
            }
        }
    }
    int countMoves()
    {
        // count Number of moves possible for current turn player
        int moves = 0;
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if (this->chessBoard[i][j].color == this->currentTurn)
                {

                    moves += chessBoard[i][j].totalmoves;
                }
            }
        }
        return moves;
    }
    bool ifRowBlank(int x, int r1, int r2)
    {
        // check if any piece exist between r1 and r2 column in xth row
        for (int i = r1; i < r2 + 1; i++)
        {
            if (chessBoard[x][i].rank != 0)
            {
                return 0;
            }
        }
        return 1;
    }
};
