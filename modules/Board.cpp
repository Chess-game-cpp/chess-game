#include "Moves.hpp"

bool Board::check_checkmate(int player)
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
void Board::generateMoves()
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
