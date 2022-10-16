//Board Class here
#pragma once
#include "Pieces.hpp"
#include <math.h>
#include <iostream>
#include <string>
ChessPiece get_piece(char a){
    ChessPiece temp;
    if(a<97){
        temp.set_color(0);
        a+=32;
    }else{
        
        temp.set_color(1);
    }
    switch (a)
    {
    case 'p':
        temp.set_rank(1);
        break;
    case 'r':
        temp.set_rank(2);
        temp.set_castling(true);
        break;
    case 'n':
        temp.set_rank(3);
        break;
    case 'b':
        temp.set_rank(4);
        break;
    case 'q':
        temp.set_rank(5);
        break;
    case 'k':
        temp.set_rank(6);
        temp.set_castling(true);
        break;
    
    default:
        break;
    }
    // temp.display_string();
    return temp;

}
class Board{
    ChessPiece chessBoard[8][8];
    ChessPiece captured[2][16];
    bool castling[2][2];
     int currentTurn;
     friend class ChessPiece;
     Box enpasant;
    // friend class Engine;
    public:
      Board(){
        // parse_fen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq -");
        // parse_fen("rnbqkbnr/1ppppppp/p7/4P3/8/8/PPPP1PPP/RNBQKBNR b kqKQ -");
        parse_fen("rnbqkbnr/1ppppppp/p2r4/4P3/8/8/P4PPP/R3KBNR w kqKQ -");
        // parse_fen("rnbqkbnr/1ppppppp/8/p7/8/4PQ2/PPPP1PPP/RNB1KBNR b");
      }
      void parse_fen(std:: string fen){
        int x=0;
        int y=0;
        int i=0;
        //chess Pieces
        while(fen[i]!=' '){
            if(fen[i]=='/'){
                x+=1;
                y=0;
            }
            else if((fen[i]-48)>0 && (fen[i]-48)<9){
                y+=(fen[i]-48);
                
            }
            else{
                // std::cout << x <<" "<<y ;
                chessBoard[x][y]=get_piece(fen[i]);
                chessBoard[x][y].setPosition(x,y);
                
                y+=1;
            }
            i+=1;
        }
        //turn
        i+=1;
        if(fen[i]=='w'){
            currentTurn=0;
        }else if(fen[i]=='b'){
            currentTurn=1;

        }
        i+=2;
        //castling
        castling[0][0]=false;
        castling[0][1]=false;
        castling[1][0]=false;
        castling[1][1]=false;
        while(fen[i]!=' '){
            switch( fen[i]){
                case 'k':
                    castling[1][0]=true;
                    break;
                case 'K':
                    castling[0][0]=true;
                    break;
                case 'Q':
                    castling[0][1]=true;
                    break;
                case 'q':
                    castling[1][1]=true;
                    break;
                default:
                break;
            }

            i+=1;
        }
        //enpasant
        i+=1;
        if(fen[i]=='-'){

        }
        else{
        enpasant.y=fen[i]-97;
        enpasant.x=56-fen[i+1];

        }

        


      }
      void print_board(){
           std:: cout<<std::endl<<std::endl;
        int i,j;
        std::cout<<"  0 1 2 3 4 5 6 7"<< std::endl;
        for(i=0;i<8;i++){
            std::cout <<i <<" ";
            for( j=0;j<8;j++){
                chessBoard[i][j].display_string();
            }          
            std:: cout << std::endl;
        }        
      }
      int get_turn(){
       return this->currentTurn;
      }
      void switch_turn(){
        this->currentTurn=!this->currentTurn;
      }
      int capture_insertIndex(int color){
        for(int i=0;i<16;i++){
            if(captured[color][i].rank==0){
                return i;
            }
        }
        return 15;
      }
      Box get_king_position(int color){
        for(int i=0;i<8;i++){
            for(int j=0;j<8;j++){
                    if((chessBoard[i][j].rank==6)&&(chessBoard[i][j].color==color)){
                        return chessBoard[i][j].position;
                    }
            }            
            
        }
        return Box();
      }
      ChessPiece get_chesspiece(int x,int y){
        return chessBoard[x][y];

      }
      int move_piece(ChessPiece pc,Box b,bool legal=true){

        int displacement=sqrt(pow((pc.position.x-b.x),2)+pow((pc.position.y-b.y),2));
        if(legal){
        int isLegal=0;
            for(int i=0;i<pc.totalmoves;i++){
                if(pc.moves[i]==b){
                    isLegal=1;
                    break;
                }
            }
        
            if(!isLegal) return 2;
        }
        ChessPiece capturedpiece=chessBoard[b.x][b.y];
        if(capturedpiece.rank>0){
            captured[!pc.color][this->capture_insertIndex(!pc.color)]=capturedpiece;
                        
        }
        
       
            
            if(pc.rank==6){
                castling[currentTurn][0]=false;
                castling[currentTurn][1]=false;

            }
            if(pc.rank==2 && pc.position==Box(0,currentTurn*7)){
                castling[currentTurn][1]=false;

            }
            if(pc.rank==2 && pc.position==Box(7,currentTurn*7)){
                castling[currentTurn][0]=false;

            }
           if((this->enpasant.is_valid())&&(pc.rank==1)&&(b==this->enpasant)){
                
            chessBoard[pc.position.x][b.y]=ChessPiece();   
        
           }
         //for castling
          if(displacement==2 && pc.rank==6){
            if(pc.position.y>b.y){
            chessBoard[b.x][b.y+1]=chessBoard[!this->currentTurn*7][0];
            chessBoard[b.x][b.y+1].position=Box(b.x,b.y+1);
            chessBoard[!this->currentTurn*7][0]=ChessPiece();
            
            }
            else{
            chessBoard[b.x][b.y-1]=chessBoard[!this->currentTurn*7][7];
            chessBoard[b.x][b.y-1].position=Box(b.x,b.y-1);
            chessBoard[!this->currentTurn*7][7]=ChessPiece();
                
            }
            castling[this->currentTurn][0]=false;
            castling[this->currentTurn][1]=false;
        }
        chessBoard[pc.position.x][pc.position.y]=ChessPiece ();        
        pc.position=b;
        chessBoard[b.x][b.y]=pc;
         this->enpasant=Box();
           
            if(displacement==2 && pc.rank==1){
                this->enpasant=Box(b.x+1+(-2*this->currentTurn),b.y);

            }
      
        if(legal){
          
          return this->check_checkmate(!pc.color);

        }
        else{
          return this->check_checkmate(pc.color);

        }
      



      }
      bool check_checkmate(int player){

        Box king=this->get_king_position(player);
         for(int i=0;i<8;i++){
            for(int j=0;j<8;j++){
                if(chessBoard[i][j].color!=player){
                    chessBoard[i][j].generatepseudoMoves(*this);
                 for(int k=0;k<chessBoard[i][j].totalmoves;k++){
                    if(chessBoard[i][j].moves[k]==king){
                     
                        return 1;
                    }
                 }   
                }
            }            
            
        }
        
        return 0;
      }
      void generateMoves(){
       for(int i=0;i<8;i++){
            for(int j=0;j<8;j++){
                if(this->chessBoard[i][j].color==this->currentTurn){

                   this->chessBoard[i][j].generateLegalMoves(*this);
                }
            }    
      }
      }
      int countMoves(){
        int moves=0;
       for(int i=0;i<8;i++){
            for(int j=0;j<8;j++){
                if(this->chessBoard[i][j].color==this->currentTurn){
                    
                  moves+=chessBoard[i][j].totalmoves;
                }
            }    

      }
      return moves;
      }
      bool ifRowBlank(int x,int r1,int r2){
        for(int i=r1;i<r2+1;i++){
            if(chessBoard[x][i].rank!=0){
                return 0;
                
            }
        }
        return 1;

      }
};
