void ChessPiece :: knight (int ix,int iy,Board &b){
    if(this->rank!=3) return;
    int x=this->position.x+ix;
    int y=this->position.y+iy;
 
    if(x>=0 && x<8 && y>=0 && y<8){
        //exist in board
       if (b.chessBoard[x][y].rank==0||(b.chessBoard[x][y].rank!=0 && b.chessBoard[x][y].color!=this->color)){
    
        moves[totalmoves]=Box(x,y);
      
        totalmoves+=1;
       }
    }
}
void ChessPiece :: rook (int ix,int iy,Board &b){
    if(this->rank!=2 && this->rank!=5) return;
    int x=this->position.x;
    int y=this->position.y;
    while ((iy==0 && x!=int(((ix+1)*7)/2))||(ix==0 && y!=int(((iy+1)*7)/2)))
    {
        x+=ix;
        y+=iy;
        if(b.chessBoard[x][y].rank==0 || ( b.chessBoard[x][y].rank!=0 && b.chessBoard[x][y].color!=this->color)){
              moves[totalmoves]=Box(x,y);
              // moves[totalmoves].display();
        totalmoves+=1;
        if(b.chessBoard[x][y].rank!=0 && b.chessBoard[x][y].color!=this->color)break;
        }
        else{
            break;
        }
    }
    
    
}

void ChessPiece :: bishop (int ix,int iy,Board &b){
    if(this->rank!=4 && this->rank!=5) return;
     int x=this->position.x;
    int y=this->position.y;
    // std::cout<<x;

    while(x!=int(((ix+1)*7)/2) && y!=int(((iy+1)*7)/2)){
        x+=ix;
        y+=iy;
        // std::cout<<x;
        if(b.chessBoard[x][y].rank==0 || ( b.chessBoard[x][y].rank!=0 && b.chessBoard[x][y].color!=this->color)){
 moves[totalmoves]=Box(x,y);
        totalmoves+=1;
        if(b.chessBoard[x][y].rank!=0 && b.chessBoard[x][y].color!=this->color)break;
        }
        else{
            break;
        }
    }

}
void ChessPiece :: generatepseudoMoves(Board &b){
    totalmoves=0;
    int x,y;
  
  switch (this->rank){
    case 1:
        if(this->position.x==0 || this->position.x==7){
            break;
        }
       //pawn  
      
       //forward movement
       x=this->position.x-1+(2*this->color);
       y=this->position.y;
       
       if(b.chessBoard[x][y].rank==0){
        moves[totalmoves]=Box(x,y);
        totalmoves+=1;
              if(this->position.x==(6-(this->color*5))){
        x=this->position.x-2+(4*this->color);
        y=this->position.y;
       if(b.chessBoard[x][y].rank==0){
        moves[totalmoves]=Box(x,y);
        totalmoves+=1;
       }
       }
       }

 

       //left // right
       x=this->position.x-1+(2*this->color);
       y=this->position.y-1;
       if(y>0){
       if((b.chessBoard[x][y].rank!=0 && b.chessBoard[x][y].color!=this->color)||b.enpasant==Box(x,y)){
        moves[totalmoves]=Box(x,y);
        totalmoves+=1;
     
       }
      
       }
       y=this->position.y+1;
       if(y<=7){

       if((b.chessBoard[x][y].rank!=0 && b.chessBoard[x][y].color!=this->color)||b.enpasant==Box(x,y)){
        moves[totalmoves]=Box(x,y);
        totalmoves+=1;
       }
       }
      break;
    case 2:
    //rook
  
  //up movement
this->rook(1,0,b);

  //down movement
this->rook(-1,0,b);
  
  //left movement
this->rook(0,-1,b);
  
  //right movement
this->rook(0,1,b);
      break;
    case 3:
    //knight
    //2forward left
        this->knight(2,-1,b);
    //2forward right
        this->knight(2,1,b);
    //2backward right
        this->knight(-2,-1,b);
    //2backward left
        this->knight(-2,1,b);
    //2right forward
        this->knight(1,2,b);
    //2right backward
        this->knight(-1,2,b);
    //2left forward
        this->knight(1,-2,b);
    //2left backward
        this->knight(-1,-2,b);


    
      break;
    case 4:
    //bishop

    //forward right
        this->bishop(1,1,b);
    //forward left
        this->bishop(1,-1,b);
    //backward right
        this->bishop(-1,1,b);
    //backward left
        this->bishop(-1,-1,b);


      break;
    case 5:
    //queen
      //up movement
this->rook(1,0,b);

  //down movement
this->rook(-1,0,b);
  
  //left movement
this->rook(0,-1,b);
  
  //right movement
this->rook(0,1,b);
    //forward right
        this->bishop(1,1,b);
    //forward left
        this->bishop(1,-1,b);
    //backward right
        this->bishop(-1,1,b);
    //backward left
        this->bishop(-1,-1,b);




      break;
    case 6:
    //king
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            x=this->position.x-1+i;
            y=this->position.y-1+j;
            if(x>=0 && x<8 && y>=0 && y<8){
    if(b.chessBoard[x][y].rank==0||(b.chessBoard[x][y].rank!=0 && b.chessBoard[x][y].color!=this->color) ){
        moves[totalmoves]=Box(x,y);
        totalmoves+=1;
       }
            }
            
        }
    }
    //castling
    if((b.castling[b.currentTurn][1])&&(b.ifRowBlank(!b.currentTurn*7,1,3))){
      this->moves[totalmoves]=Box(this->position.x,this->position.y-2);
      totalmoves+=1;
    }

    if((b.castling[b.currentTurn][0])&&(b.ifRowBlank(!b.currentTurn*7,5,6))){
    
      this->moves[totalmoves]=Box(this->position.x,this->position.y+2);
      totalmoves+=1;

    }

      break;
    default:
      break;
  }  

}
void ChessPiece :: removeMoves(int pos){
  this->totalmoves-=1;
  this->moves[pos]=this->moves[this->totalmoves];
  

}
void ChessPiece :: generateLegalMoves(Board &b){ 
  int displacement;
  Board temp;

 
  this->generatepseudoMoves(b);
  for(int k=0;k<this->totalmoves;k++){
    temp=b;
  
    if(temp.move_piece(*this,this->moves[k],false)){
      // moves[k].display();
      this->removeMoves(k);
      k-=1;

    }
    else if(this->rank==6){
      //  displacement=sqrt(pow((this->position.x-moves[k].x),2)+pow((this->position.y-moves[k].y),2));
    
      //  if(displacement==2){
      //   for(int i=0;i<k;i++){
      //     if(moves[i]==Box(moves[k].x,(0.25*(moves[k].y-2))+3)){
      //       Box(moves[k].x,(0.25*(moves[k].y-2))+3).display();
      //       displacement=0;
      //       break;
      //     }
      //   }
      //   if(displacement!=0){
      //     this->removeMoves(k);
      //     k-=1;
      //   }
      //  }
    }


    
  }
  


}


