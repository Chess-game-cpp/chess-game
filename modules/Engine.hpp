/// Chess Game Handler Class Here
/*
GAMESTATE
0-ENDED
1-RUNNING
2-SELECTION
3-pawn Promotion
*/
#include "Board.hpp"
#include "Moves.hpp"

class Engine
{
    Board b;
    int gameState;
    bool check;
    bool castling;
    Box rookPosition;
    ChessPiece currentPiece;
    Box currentMove;

public:
    int get_gameState()
    {
        return gameState;
    }
    Board *get_board()
    {
        return &b;
    }
    Box *get_rookPositon()
    {
        return &rookPosition;
    }
    bool is_castling()
    {
        return castling;
    }

    bool is_checkmate()
    {
        return check;
    }
    ChessPiece *get_currentChecePiece()
    {
        return &currentPiece;
    }
    Box *get_currentMove()
    {
        return &currentMove;
    }

    Engine()
    {
        gameState = 1;
        check = 0;
        castling = false;
        b.generateMoves();
    }
    void set_playing(){
        gameState=1;
    }
    void display_state()
    {

        if (b.get_turn() == 0)
        {
            std::cout << "White's Turn" << std ::endl;
        }
        else
        {
            std::cout << "Black's Turn" << std ::endl;
        }
        if (this->check == 1)
        {
            std::cout << "CHECKMATE!!!!" << std ::endl;
        }
        b.generateMoves();
        if (b.countMoves() == 0)
        {

            this->gameState = 0;
            if (this->check)
            {
                if (b.get_turn() == 0)
                {
                    std::cout << "BLACK WINS!!";
                }
                else
                {
                    std::cout << "WHITE WINS!!";
                }
            }
            else
            {
                std::cout << "STALEMATE";
            }
        }
    }

    // }
    void promote_pawn(int prom)
    {
        std::cout << (b.get_chesspiece(currentMove.x, currentMove.y)).rank<<std::endl;

        (b.get_chesspiece(currentMove.x, currentMove.y)).promoteTo(prom);
        std::cout << (b.get_chesspiece(currentMove.x, currentMove.y)).rank<<std::endl;
        b.switch_turn();
        this->gameState = 1;
        display_state();
    }
    void piece_move(int x, int y,bool switche=true)
    {

        castling = false;
        bool available;
        Box current;
        ChessPiece &pice = currentPiece;

        if ((x >= 0 && x < 8) && (y >= 0 && y < 8))
        {
            current = Box(x, y);
            available = false;
            for (int i = 0; i < pice.totalmoves; i++)
            {
                if (current == pice.moves[i])
                {
                    available = true;
                    break;
                }
            }
            if (available)
            {
                currentMove = Box(x, y);
                this->check = b.move_piece(pice, current);
                castling = true;
                if (pice.rank == 6 && sqrt(pow((pice.position.x - current.x), 2) + pow((pice.position.y - current.y), 2)) == 2)
                {
                    // castling is true/
                    castling = true;
                    rookPosition.x = !b.get_turn() * 7;
                    if (pice.position.y > current.y)
                    {

                        rookPosition.y = 0;
                    }
                    else
                    {
                        rookPosition.y = 7;
                    }
                }
                if (pice.rank == 1 && (current.x == 0 | current.x == 7))
                {
                    std::cout << "PROMOTE PAwN:" << std::endl
                              << "1.Rook 2.Knight 3.Bishop 4.Queen" << std::endl;

                    this->gameState = 3;
                    return;
                }

                // break;
            }
            else
            {
                std::cout << "INVALID MOVES" << std ::endl;
                if(switche)
                piece_selection(y, x);
                //    this->gameState=1;
                return;
            }
        }

        b.switch_turn();

        this->gameState = 1;
        display_state();
    }
    void piece_selection(int y, int x)
    {
        this->gameState = 2;
        ChessPiece pice;
        currentPiece = ChessPiece();
        if ((x >= 0 && x < 8) && (y >= 0 && y < 8))
        {
            pice = b.get_chesspiece(x, y);
            if ((pice.rank > 0) && (pice.color == b.get_turn()))
            {
                if (pice.totalmoves == 0)
                {
                    std ::cout << "No Move Available" << std::endl;
                    this->gameState = 1;
                }
                else
                {

                    currentPiece = pice;
                    std ::cout << "Available Moves:" << pice.totalmoves << std::endl;

                    for (int i = 0; i < pice.totalmoves; i++)
                    {
                        pice.moves[i].display();
                    }
                }
            }
            else
            {
                this->gameState = 1;
            }
        }
        else
        {
            std::cout << "INVALID SELECTION" << std ::endl;
            this->gameState = 1;
        }
    }
};