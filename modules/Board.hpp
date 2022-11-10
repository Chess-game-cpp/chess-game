#pragma once
#include "Pieces.hpp"
#include <math.h>
#include <iostream>
#include <string>

ChessPiece get_piece(char a)
{
    int color, rank;
    bool castling = false;

    // Create Chess Peice from the Character

    if (a < 97)
    {
        // White(1) for upperc◘ase
        color = 0;
        // converting to Lowercase
        a += 32;
    }
    else
    {
        // Black(0) for Lowercase
        color = 1;
    }
    switch (a)
    {
    case 'p':
        // pawn
        rank = 1;
        break;
    case 'r':
        // rook
        rank = 2;
        castling = true;
        break;
    case 'n':
        // knight
        rank = 3;
        break;
    case 'b':
        // bishop
        rank = 4;
        break;
    case 'q':
        // queen
        rank = 5;
        break;
    case 'k':
        // king
        rank = 6;
        castling = true;
        break;

    default:
        break;
    }

    return ChessPiece(rank, color, castling);
}
// Board Class here
class Board
{
    ChessPiece chessBoard[8][8]; // Array for Board
    ChessPiece captured[2][16];  // Array for Captured Pices
    bool castling[2][2];         // Available Castling
    int currentTurn;
    Box enpasant;            // enpasant available box
    int gameState;           // track gameState
    bool is_castling_move;   // is last move castling
    bool is_captured;       //if piece was captured
    Box rookPosition;        // castled rook if castling
    ChessPiece currentPiece; // selected checkpiece
    Box currentMove[2];         // last move
    
    friend class ChessPiece;

public:
    Board()
    {

        // parse_fen("8/PPPPPPPP/8/4k3/8/8/PPPPPPPP/R3K2R w KQkq -");
        // parse_fen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq -");
        // parse_fen("rnbqkbnr/pppppppp/8/8/8/8/pPPPPPPP/1NBQKBNR w KQkq -");
        // parse_fen("rnbqkbnr/1ppppppp/p7/4P3/8/8/PPPP1PPP/RNBQKBNR b kqKQ -");
        // parse_fen("rnbqkbnr/1ppppppp/p2r4/4P3/8/8/P4PPP/R3KBNR w kqKQ -");
        // parse_fen("rnbqkbnr/1ppppppp/8/p7/8/4PQ2/PPPP1PPP/RNB1KBNR b");
    }
    void init_game(std::string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq -")
    {
     
        enpasant=Box();
        gameState = 1;
        is_castling_move = false;
        parse_fen(fen);
        switch_turn();
        update_state();
    }
     std::string get_fen()
    {
        std::string fn = "";
        for (int x = 0; x < 8; x++)
        {
            int blank = 0;
            for (int y = 0; y < 8; y++)
            {
                if (chessBoard[x][y].rank != 0)
                {
                    if (blank > 0)
                    {
                        fn += char(blank + 48);
                    }
                    fn += char(pcs[chessBoard[x][y].rank] - (!chessBoard[x][y].color * 32));
                    blank = 0;
                }
                else
                {
                    blank += 1;
                }
            }
            if (blank > 0)
            {
                fn += char(blank + 48);
            }
            if (x != 7)
            {
                fn += "/";
            }
        }
        fn += (get_turn() ? " b " : " w ");
        bool castl = false;
        if (castling[0][1])
        {
            castl = true;
            fn += 'K';
        }
        if (castling[0][0])
        {
            castl = true;
            fn += 'Q';
        }
        if (castling[1][1])
        {
            castl = true;
            fn += 'k';
        }
        if (castling[1][0])
        {
            castl = true;
            fn += 'q';
        }
        fn += castl ? " " : "- ";
        if (enpasant.is_valid())
        {
            fn += char(enpasant.y + 97);
            fn += char(((8-enpasant.x) + 48));
        }
        else
        {
            fn += "-";
        }
        return fn;
    }
   
    int get_gameState()
    {
        return gameState;
    }

    Box *get_rookPositon()
    {
        return &rookPosition;
    }
    bool is_castling()
    {
        return is_castling_move;
    }

    bool is_checkmate()
    {
        return check_checkmate(currentTurn);
    }
    ChessPiece *get_currentChessPiece()
    {
        return &currentPiece;
    }
    Box *get_currentMove()
    {
        return currentMove;
    }
    ChessPiece *get_captured(int player)
    {

        return captured[player];
    }
    bool is_capture_move(){
        return is_captured;
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

    void times_up()
    {
        this->gameState = 4;
        update_state();
    }
    void promote_pawn(int prom)
    {
        // function to promote the pawn
        (get_chesspiece(currentMove[0].x, currentMove[0].y)).set_rank(prom); // pawn promotion function
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
            pice = get_chesspiece(x, y);
            // check if selected box is not blank and piece belong to current player
            if ((pice.rank > 0) && (pice.color == currentTurn))
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
    void piece_move(int x, int y, bool switche = true)
    {
        // function to move piece in the board
        is_castling_move = false;
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
                currentMove[0] = Box(x, y);
                currentMove[1] = pice.position;
                handle_move(pice, current); // move piece in board

                if (pice.rank == 6 && sqrt(pow((pice.position.x - current.x), 2) + pow((pice.position.y - current.y), 2)) == 2)
                {
                    // castling is true/
                    is_castling_move = true;
                    // store castled rook position
                    rookPosition.x = !currentTurn * 7;
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

private:
    void update_state()
    {
        /*
        switches turn
        updates game state
        checks if checkmate or stalemate
        */

        // times up
        switch_turn();
        if (this->gameState == 4)
        {
            if (currentTurn == 0)
            {
                std::cout << "WHITE WINS!!";
            }
            else
            {
                std::cout << "BLACK WINS!!";
            }

            return;
        }
        this->gameState = 1;

        if (currentTurn == 0)
        {
            // std::cout << "White's Turn" << std ::endl;
        }
        else
        {
            // std::cout << "Black's Turn" << std ::endl;
        }
        if (check_checkmate(currentTurn) == 1)
        {
            std::cout << "CHECKMATE!!!!" << std ::endl;
        }
        generateMoves();
        if (countMoves() == 0)
        {

            this->gameState = 0;
            if (check_checkmate(currentTurn) == 1)
            {
                if (currentTurn == 0)
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
    void parse_fen(std::string fen)
    {
        //clean board
        for(int x=0;x<8;x++){
         for(int y=0;y<8;y++){
            chessBoard[x][y].set_rank(0);
        }       
        }
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
                castling[1][1] = true;
                break;
            case 'K':
                // King Side black
                castling[0][1] = true;
                break;
            case 'Q':
                // Queen side white
                castling[0][0] = true;
                break;
            case 'q':
                // Queen side black
                castling[1][0] = true;
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

    int handle_move(ChessPiece pc, Box b, bool legal = true)
    {   
        is_captured=false;
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
            is_captured=true;
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
        // remove captured piece in enpasant
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
                // updating positon of castled rook
                chessBoard[b.x][b.y + 1] = chessBoard[!this->currentTurn * 7][0];
                chessBoard[b.x][b.y + 1].position = Box(b.x, b.y + 1);
                chessBoard[!this->currentTurn * 7][0] = ChessPiece();
            }
            else
            {
                // updating positon of castled rook
                chessBoard[b.x][b.y - 1] = chessBoard[!this->currentTurn * 7][7];
                chessBoard[b.x][b.y - 1].position = Box(b.x, b.y - 1);
                chessBoard[!this->currentTurn * 7][7] = ChessPiece();
            }
            // removing castling available
            castling[this->currentTurn][0] = false;
            castling[this->currentTurn][1] = false;
        }
        // removing chess piece from the previous position
        chessBoard[pc.position.x][pc.position.y] = ChessPiece();
        // updating the position of chesspiece
        pc.position = b;
        // adding to board array
        chessBoard[b.x][b.y] = pc;
        this->enpasant = Box();

        // another player can capture by enpasant
        if (displacement == 2 && pc.rank == 1)
        {
            this->enpasant = Box(b.x + 1 + (-2 * this->currentTurn), b.y);
        }
        if (legal)
        {
            // return if next player will be in checkmate after the move

            return this->check_checkmate(!pc.color);
        }
        else
        {
            // return if current  player will be in checkmate after the move
            return this->check_checkmate(pc.color);
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
    void generateMoves();
    public:
    bool check_checkmate(int);
    
    int depth_test(int desired,int depth=0){
      
        if(depth==desired){
            return 0;
        }
        
        int total=0;
        if(depth==desired-1){

        return countMoves();
        }
        //depth analysis
        for(int x=0;x<8;x++){

            for(int y=0;y<8;y++){
                if(chessBoard[x][y].rank!=0 && chessBoard[x][y].color==currentTurn)
                {
                    if(chessBoard[x][y].totalmoves==0) continue;
                    for(int i=0;i<chessBoard[x][y].totalmoves;i++){
                        std::string fen=get_fen();
                        handle_move(chessBoard[x][y],chessBoard[x][y].moves[i]);
                    
                        update_state();
                       if(get_gameState()==0) {
                        continue;
                       };
                        Board *b=new Board();
                        b->init_game(get_fen());
                        total+=b->depth_test(desired,depth+1);
                      
                        delete b;
                        init_game(fen);
                    }
                }
                
            }
        }
        return total;
    }
};
