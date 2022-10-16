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

char pcs[7]={' ','p','r','n','b','q','k'};
class Box{
    public:
    int x;
    int y;
    Box(){
      x=-1;
      y=-1;
    }
    Box(int x,int y){
        this->x=x;
        this->y=y;
    }
    bool operator ==(Box a){
      if((this->x==a.x)&&(this->y==a.y)){
        return 1;
        
      }
      return 0;

    }
    void display(){
      std::cout << x <<","<<y<<std::endl;
    }
    bool is_valid(){
      if(x<0||y<0){
        return 0;
      }
      return 1;
    }
    void setNull(){

    } 

};
class ChessPiece{
    int rank;
    int color;
    Box position;
    Box moves[64];
    bool castling;
    friend class Board;
    friend class Engine;
    public:

      int totalmoves;

      ChessPiece(){
        this->rank=0;
        this->color=10;
        this->castling=false;
      };
      void set_castling(bool cast){
        this->castling=cast;

      }
      void set_color(int color){
        this->color=color;
      }
      void display_string(){
        if(this->rank==0){
          std::cout<<"  ";
        }else{
        std::cout<<(char((pcs[this->rank]-32)+(this->color*32)))<<" ";

        }
        
      }
      void set_rank(int rank){
        this->rank=rank;
      }
      void setPosition(int x,int y){
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
      void promoteTo(int rank){
        this->rank=rank+1;

      }
     


};


