/// Chess Game Handler Class Here
// Handle gamestates
/*
GAMESTATES
0-ENDED
1-RUNNING
2-SELECTION
3-pawn Promotion
4-Timer Down
*/
#include "Board.hpp"
#include "Moves.hpp"
class Engine
{
    Board b;                 // board object
    int gameState;           // stores gamestate
    bool check;              // is currently checkmate
    bool castling;           // is current move castling
    Box rookPosition;        // castled rook if castling
    ChessPiece currentPiece; // selected checkpiece
    Box currentMove;         // last move

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

    void set_playing()
    {
        gameState = 1;
    }
    Engine()
    {
        gameState = 1;
        check = 0;
        castling = false;
        b.generateMoves(); // generates abailable moves for current turn player
    }

    void update_state()
    {
        /*
        switches turn
        updates game state
        checks if checkmate or stalemate
        */

       //times up
        if (this->gameState == 4)
        {
            if (b.get_turn() == 0)
            {
                std::cout << "WHITE WINS!!";
            }
            else
            {
                std::cout << "BLACK WINS!!";
            }

            return;
        }
        b.switch_turn();
        this->gameState = 1;
        this->check = b.check_checkmate(b.get_turn());
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
    void times_up()
    {
        this->gameState = 4;
    }
    void promote_pawn(int prom)
    {
        // function to promote the pawn
        (b.get_chesspiece(currentMove.x, currentMove.y)).set_rank(prom); // pawn promotion function
        update_state();
    }
    void piece_move(int x, int y, bool switche = true)
    {
        // function to move piece in the board
        castling = false;
        bool available;
        Box current;
        ChessPiece &pice = currentPiece;

        if ((x >= 0 && x < 8) && (y >= 0 && y < 8))
        {
            current = Box(x, y);
            available = false;
            // checks if current move is legal
            for (int i = 0; i < pice.totalmoves; i++)
            {
                if (current == pice.moves[i])
                {
                    available = true;
                    break;
                }
            }
            // if legal
            if (available)
            {
                currentMove = Box(x, y);
                b.move_piece(pice, current); // move piece in board

                if (pice.rank == 6 && sqrt(pow((pice.position.x - current.x), 2) + pow((pice.position.y - current.y), 2)) == 2)
                {
                    // castling is true/
                    castling = true;
                    // store castled rook position
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
                // check if pawn is to be promoted
                if (pice.rank == 1 && (current.x == 0 | current.x == 7))
                {
                    std::cout << "PROMOTE PAwN:" << std::endl
                              << "1.Rook 2.Knight 3.Bishop 4.Queen" << std::endl;
                    // updates gameState to pawn promotion gameState
                    this->gameState = 3;
                    return;
                }
            }
            else
            {
                // Illegal Move
                std::cout << "INVALID MOVES" << std ::endl;
                this->gameState = 1; // upadte to running gameState
                // select piece at the invalid move position
                if (switche)
                    piece_selection(y, x);
                return;
            }
        }
        update_state();
    }
    void piece_selection(int y, int x)
    {
        // function to select piece
        this->gameState = 2;
        ChessPiece pice;
        currentPiece = ChessPiece();
        // check if valid position in board
        if ((x >= 0 && x < 8) && (y >= 0 && y < 8))
        {
            pice = b.get_chesspiece(x, y);
            // check if selected box is not blank and piece belong to current player
            if ((pice.rank > 0) && (pice.color == b.get_turn()))
            {
                // check if moves is available for selected piece
                if (pice.totalmoves == 0)
                {
                    std ::cout << "No Move Available" << std::endl;
                    this->gameState = 1;
                }
                else
                {
                    // selects current Piece
                    currentPiece = pice;
                    // display available moves in console
                    std ::cout << "Available Moves:" << pice.totalmoves << std::endl;
                    for (int i = 0; i < pice.totalmoves; i++)
                    {
                        pice.moves[i].display();
                    }
                }
            }
            else
            {
                // not valid box selected
                this->gameState = 1;
            }
        }
        else
        {
            // illegal selection
            std::cout << "INVALID SELECTION" << std ::endl;
            this->gameState = 1;
        }
    }
};