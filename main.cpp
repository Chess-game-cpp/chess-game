#include <iostream>
#include <SDL2/SDL.h>
// #include <SDL2/SDL.h>
class Window{
    std::string title;
    int width=800;
    int height=600;
    int closed=false;
       SDL_Event ev;
    public:
    Window(const std::string &title,int width,int height);
    ~Window();
    bool init();
    SDL_Window * window=nullptr;
    bool isClosed() const{return closed;}
    SDL_Surface * surface=nullptr;    
    SDL_Renderer * render=NULL;
    SDL_Texture * texture=NULL;
    void create_rectangle(int x, int y, SDL_Renderer * &r){

          SDL_Rect rect;
    rect.x = x*92;
    rect.y = y*92;
    rect.w = 92;
    rect.h = 92;
    if((x+y)%2==1){
        //even =black
    SDL_SetRenderDrawColor(r, 0, 0, 0,255);
    }else{
    SDL_SetRenderDrawColor(r, 255, 255, 255,255);
        //odd = white
    }
    // SDL_SetRenderDrawColor(r, 0, 255, 255,255);
    SDL_RenderFillRect(r, &rect);//create_rect
   
    }


 
};
Window::Window(const std::string &title,int width,int height){
/
    this->title=title;
    this->width=width;
    this->height=height;
    if(!init()){
        closed=true;
    }
      render=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
      for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){

      create_rectangle(i,j,render);
        }
      }
   SDL_RenderPresent(render);
     while (1)
    {
        if(SDL_PollEvent(&ev)!=0){
            if(ev.type==SDL_QUIT){
                break;
            }
        }}
}
bool Window::init(){
  if( SDL_Init(SDL_INIT_VIDEO)!=0){
    std::cout << "Failed";
    return 0;
  }
  window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height,SDL_WINDOW_RESIZABLE);
  if(window==nullptr){
        std::cout << "Failed to create Window.\n";
        return 0;
    }
    return 1;

}
Window::~Window(){
    SDL_DestroyWindow(window);
    
    SDL_Quit();

}



int main(int argv, char** args){
    Window w("Hello",736,736);
    
    


    return 0;
}