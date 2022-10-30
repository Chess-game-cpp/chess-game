#pragma once
void ChessPiece ::knight(int ix, int iy, Board &b)
{
  /*moves of knight(L movement)
  ix->x-change in board
  iy->y-change in board
  */
  if (this->rank != 3)
    return;
  
  int x = this->position.x + ix;
  int y = this->position.y + iy;

  //check if box exist in board
  if (x >= 0 && x < 8 && y >= 0 && y < 8)
  {
    //check if selected box is blank or not blocked by own piece
    if (b.chessBoard[x][y].rank == 0 || (b.chessBoard[x][y].rank != 0 && b.chessBoard[x][y].color != this->color))
    {
      //add move 
      moves[totalmoves] = Box(x, y);
      totalmoves += 1;
    }
  }
}
void ChessPiece ::rook(int ix, int iy, Board &b)
{
  /*moves for rook (Straight Movement)
  ix=0 ->move in y-direction 
  iy=0 ->move in x direction
  */
  //check if rook or queen
  if (this->rank != 2 && this->rank != 5)
    return;
  int x = this->position.x;
  int y = this->position.y;
  //while not edge of the board is encountered
  while ((iy == 0 && x != int(((ix + 1) * 7) / 2)) || (ix == 0 && y != int(((iy + 1) * 7) / 2)))
  {
    //incrementing step
    x += ix;
    y += iy;
     //check if selected box is blank or not blocked by own piece
    if (b.chessBoard[x][y].rank == 0 || (b.chessBoard[x][y].rank != 0 && b.chessBoard[x][y].color != this->color))
    {
      moves[totalmoves] = Box(x, y);
      totalmoves += 1;
      //if blocked by opposite piece can be captured but further path is blocked
      if (b.chessBoard[x][y].rank != 0 && b.chessBoard[x][y].color != this->color)
        break;
    }
    else
    {
      //if blocked by own piece cannot proceed
      break;
    }
  }
}

void ChessPiece ::bishop(int ix, int iy, Board &b)
{
  /*
  move for bishop(Diagonal Movement)

  */
 //check if bishop or queen
  if (this->rank != 4 && this->rank != 5)
    return;
  int x = this->position.x;
  int y = this->position.y;
  //loop until edge of board is encounterd
  while (x != int(((ix + 1) * 7) / 2) && y != int(((iy + 1) * 7) / 2))
  {
    x += ix;
    y += iy;
    //check if selected box is blank or not blocked by own piece
    if (b.chessBoard[x][y].rank == 0 || (b.chessBoard[x][y].rank != 0 && b.chessBoard[x][y].color != this->color))
    {
      moves[totalmoves] = Box(x, y);
      totalmoves += 1;
      //if blocked by opposite piece can be captured but further path is blocked
      if (b.chessBoard[x][y].rank != 0 && b.chessBoard[x][y].color != this->color)
        break;
    }
    else
    {  //if blocked by own piece cannot proceed
      break;
    }
  }
}
void ChessPiece ::generatepseudoMoves(Board &b)
{
  /*Generate all possible moves for current player without accounting king capture(checkmate) by another player*/
  totalmoves = 0;
  int x, y;

  switch (this->rank)
  {
  case 1:
    // no move possible for pawn once reach the extreme end [pawn Promotion is done] 
    if (this->position.x == 0 || this->position.x == 7)
    {
      break;
    }
    // pawn

    // forward movement for pawn
    x = this->position.x - 1 + (2 * this->color);
    y = this->position.y;
    //check if forward box is blocked by another piece
    if (b.chessBoard[x][y].rank == 0)
    {
      moves[totalmoves] = Box(x, y);
      totalmoves += 1;
      //two move forward for pawn at starting position only
      if (this->position.x == (6 - (this->color * 5)))
      {
        x = this->position.x - 2 + (4 * this->color);
        y = this->position.y;
            //check if forward box is blocked by another piece
        if (b.chessBoard[x][y].rank == 0)
        {
          moves[totalmoves] = Box(x, y);
          totalmoves += 1;
        }
      }
    }

    // left Capture
    x = this->position.x - 1 + (2 * this->color);
    y = this->position.y - 1;
    if (y >= 0)
    {
     //checking if piece of opponent in the one step up diagonal box or enpasant capture is possible  
      if ((b.chessBoard[x][y].rank != 0 && b.chessBoard[x][y].color != this->color) || b.enpasant == Box(x, y))
      {
        moves[totalmoves] = Box(x, y);
        totalmoves += 1;
      }
    }
    //right Capture
    y = this->position.y + 1;
    if (y <= 7)
    {
//checking if piece of opponent in the one step up diagonal box or enpasant capture is possible
      if ((b.chessBoard[x][y].rank != 0 && b.chessBoard[x][y].color != this->color) || b.enpasant == Box(x, y))
      {
        moves[totalmoves] = Box(x, y);
        totalmoves += 1;
      }
    }
    break;
  case 2:
    // rook

    // up movement
    this->rook(1, 0, b);

    // down movement
    this->rook(-1, 0, b);

    // left movement
    this->rook(0, -1, b);

    // right movement
    this->rook(0, 1, b);
    break;
  case 3:
    // knight
    // 2forward left
    this->knight(2, -1, b);
    // 2forward right
    this->knight(2, 1, b);
    // 2backward right
    this->knight(-2, -1, b);
    // 2backward left
    this->knight(-2, 1, b);
    // 2right forward
    this->knight(1, 2, b);
    // 2right backward
    this->knight(-1, 2, b);
    // 2left forward
    this->knight(1, -2, b);
    // 2left backward
    this->knight(-1, -2, b);

    break;
  case 4:
    // bishop

    // forward right
    this->bishop(1, 1, b);
    // forward left
    this->bishop(1, -1, b);
    // backward right
    this->bishop(-1, 1, b);
    // backward left
    this->bishop(-1, -1, b);

    break;
  case 5:
    // queen
    // up movement
    this->rook(1, 0, b);

    // down movement
    this->rook(-1, 0, b);

    // left movement
    this->rook(0, -1, b);

    // right movement
    this->rook(0, 1, b);
    // forward right
    this->bishop(1, 1, b);
    // forward left
    this->bishop(1, -1, b);
    // backward right
    this->bishop(-1, 1, b);
    // backward left
    this->bishop(-1, -1, b);

    break;
  case 6:
    // king
    //loop to generate all possible movements of the king
    for (int i = 0; i < 3; i++)
    {
      for (int j = 0; j < 3; j++)
      {
        x = this->position.x - 1 + i;
        y = this->position.y - 1 + j;
        //if x,y is in board
        if (x >= 0 && x < 8 && y >= 0 && y < 8)
        {
          //check if selected board is not blocked by own piece
          if (b.chessBoard[x][y].rank == 0 || (b.chessBoard[x][y].rank != 0 && b.chessBoard[x][y].color != this->color))
          {
            moves[totalmoves] = Box(x, y);
            totalmoves += 1;
          }
        }
      }
    }
    // castling
    //Queen Side Castling
    if ((b.castling[b.currentTurn][1]) && (b.ifRowBlank(!b.currentTurn * 7, 1, 3)))
    {
      this->moves[totalmoves] = Box(this->position.x, this->position.y - 2);
      totalmoves += 1;
    }

    //King Side Castling
    if ((b.castling[b.currentTurn][0]) && (b.ifRowBlank(!b.currentTurn * 7, 5, 6)))
    {

      this->moves[totalmoves] = Box(this->position.x, this->position.y + 2);
      totalmoves += 1;
    }

    break;
  default:
    break;
  }
}
void ChessPiece ::removeMoves(int pos)
{
  //remove moves at pos index in moves array
  this->totalmoves -= 1;
  this->moves[pos] = this->moves[this->totalmoves];
}
void ChessPiece ::generateLegalMoves(Board &b)
{
  int displacement;
  Board temp;
   

  this->generatepseudoMoves(b);//generate pseudo moves
  for (int k = 0; k < this->totalmoves; k++)
  {
    temp = b;

    if (temp.handle_move(*this, this->moves[k], false))
    {
      //if the move will lead to check then remove the move
      this->removeMoves(k);
      k -= 1;
    }
    else if (this->rank == 6)
    {
      //castle throught the check
       displacement=abs(this->position.y-moves[k].y);
      
       //if castling move
       if(displacement==2){
        //castling not possible while king is in check
      
  
        if(!b.check_checkmate(this->color)){
        for(int i=0;i<k;i++){
          //castling is legal (i.e not through check)
          if(moves[i]==Box(moves[k].x,(moves[k].y>this->position.y)?5:3)){
            displacement=0;
            break;
          }
        }
        }
  
        if(displacement!=0){
          //if castling through check remove move
          this->removeMoves(k);
          k-=1;
        }
       }
    }
  }
}
