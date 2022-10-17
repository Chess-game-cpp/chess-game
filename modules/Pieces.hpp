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
//array of chess piece character symbols
char pcs[7]={' ','p','r','n','b','q','k'};
//Box class to represent square
class Box{
    public:
    int x;//xpos
    int y;//y pos
    Box(){
      x=-1;
      y=-1;
    }
    Box(int x,int y){
        this->x=x;
        this->y=y;
    }
    //check if two Box objects have same value
    bool operator ==(Box a){
      if((this->x==a.x)&&(this->y==a.y)){
        return 1;
        
      }
      return 0;

    }
    
    void display(){
      //display value og box
      std::cout << x <<","<<y<<std::endl;
    }
    bool is_valid(){
      //box is valid 
      if(x<0||y<0){
        return 0;
      }
      return 1;
    }
    void setNull(){

    } 

};

//ChessPiece class to represent a chess piece
class ChessPiece{
    int rank;
    int color;
    Box position;
    Box moves[64];//available moves
    bool castling; //castling available?
    friend class Board;
    friend class Engine;
    friend class GameScreen;
    public:

      int totalmoves;//total legal moves

      ChessPiece(){
        //blank chess piece creation
        this->rank=0;
        this->color=10;
        this->castling=false;
      };
      void set_castling(bool cast){
        //set castling
        this->castling=cast;

      }
      void set_color(int color){
        //set color
        this->color=color;
      }
      void display_string(){
        //display char symbol of given chess Piece eg. for black pawn "p" and for white pawn "P"
        if(this->rank==0){
          std::cout<<"  ";
        }else{
        std::cout<<(char((pcs[this->rank]-32)+(this->color*32)))<<" ";

        }
        
      }
      void set_rank(int rank){
        //update the rank
        this->rank=rank;
      }
      void setPosition(int x,int y){
        //update the position
        position.x=x;
        position.y=y;
      }    
      void generateLegalMoves(Board &);
      void generatepseudoMoves(Board &);
      void get_position();
      void move();
      void knight(int,int,Board &);
      void bishop(int,int,Board &);
      void rook(int,int,Board &);
      void removeMoves(int);



};


