///Chess Game Handler Class Here
/*
GAMESTATE
0-ENDED
1-RUNNING
2-SELECTION
*/
#include "Board.hpp"
#include "Moves.hpp"

class Engine{
    Board b;
    char gameState;
    char check;
    bool PawnPromotion;
    bool castling;
    Box rookPosition;
    ChessPiece currentPiece;
    Box currentMove;
    
    public:
        Engine(){
            gameState=1;
            check=0;
            PawnPromotion=false;
            castling=false;
      
     

        }   
        // void game_loop(){
        //     while(this->gameState!=0){
        //         if(b.get_turn()==0){
        //             std::cout << "White's Turn" << std :: endl;
        //         }              
        //         else{
        //             std::cout << "Black's Turn" << std :: endl;

        //         }
        //         if(this->check==1){
        //             std::cout << "CHECKMATE!!!!" << std :: endl;
                    
        //         }
        //         b.print_board();
        //         b.generateMoves();
        //         if(b.countMoves()==0){
        //                 this->gameState=0;
        //             if(this->check){
        //                 if(b.get_turn()==0){
        //                     std:: cout << "BLACK WINS!!";
        //                 }
        //                 else{
        //                     std:: cout << "WHITE WINS!!";

        //                 }
        //             }
        //             else{
        //                     std:: cout << "STALEMATE";
        //             }
        //             break;

        //         }

        //         this->piece_selection();
        //         b.switch_turn();



        //     }

        // }
        void promote_pawn(int x,int y,int prom){
            
b.get_chesspiece(x,y).promoteTo(prom);
        }
        void piece_move(int x,int y){
            PawnPromotion=false;
            castling=false;
               bool available;
                Box current;
          
           
      
                     if((x>=0 && x<8)&&(y>=0 && y<8)){      
                        current=Box(x,y);
                        available=false;
                          for(int i=0;i<pice.totalmoves;i++){
                            if(current==pice.moves[i]){
                                available=true;
                                break;
                            }
                        
                   }
                   if(available){
                    this->check=b.move_piece(pice,current);
                    castling=true;
                    if(piece.rank==6 && sqrt(pow((piece.position.x-current.x),2)+pow((piece.position.y-current.y),2))==2){
                        //castling is true/
                        castling=true;
            rookPosition.x=!b.get_turn()*7
                        if(piece.position.y>current.y){

                            rookPosition.y=0
            
            }
            else{
            rookPosition.y=7
            }
                    }
                    if(pice.rank==1 && (current.x==0|current.x==7)){
                        std::cout << "PROMOTE PAwN:"<<std::endl<<"1.Rook 2.Knight 3.Bishop 4.Queen"<<std::endl;
                 
                            
                      PawnPromotion=true;
                        
                        
                        
                    }
                 
                    break;
                   }
                   else{
                       std::cout << "INVALID MOVES" << std :: endl;
                       
                   }
                     


                }
                 currentMove=Box(x,y);  
                    this->gameState=1;         
        }
        void piece_selection(int x,int y){
                this->gameState=2;
                PawnPromotion=false;
                 ChessPiece pice;
            if((x>=0 && x<8)&&(y>=0 && y<8)){         
                 pice= b.get_chesspiece(x,y);
                 if((pice.rank>0)&&(pice.color==b.get_turn())){
                    if(pice.totalmoves==0){
                    std :: cout<<"No Move Available"<<std::endl;
                    this->gameState=1;

                    }else{

                    currentPiece=pice;
                   std :: cout<<"Available Moves:"<<pice.totalmoves<<std::endl;
                   
                   for(int i=0;i<pice.totalmoves;i++){
                        pice.moves[i].display();
                   }
                    }
    



                 }
              
                }
                else{
                    std::cout << "INVALID SELECTION" << std :: endl;
                    this->gameState=1;    
                }
             
                
                
                
            
        }

};