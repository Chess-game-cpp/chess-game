#include <SDL2/SDL.h>
#include <iostream>
class Timer
{
    int time1;
    int time2;
    int starttime;
    int current;
    bool active;
    SDL_TimerID id;


public:
    Timer(){
        starttime=0;
        active=false;
    }
    bool is_active(){
        return active;
    }
    void set_timer(int time)
    {
        if(time<=0) return;
        starttime=SDL_GetTicks64();
        active=true;
        time1 = time2 = time;
        current=0;

    }
    int get_time(int player)
    {
        if (player == 0)
        {
            return time1-(current==0?(SDL_GetTicks64()-starttime):0);
        }
        else if (player == 1)
        {
            return time2-(current==1?(SDL_GetTicks64()-starttime):0);
        }
        return 0;
    }
    void switch_timer()
    {
        if(!active) return;
    
    int * time;
    if(current==0){
    
       time=&time1;
    }else{
    
        time=&time2;

    }
    current=!current;
    int currenttime=SDL_GetTicks64();
    *time-=currenttime-starttime;
    starttime=currenttime;
    }
    void set_inactive(){
        active=false;
    }
    SDL_TimerID get_id(){
        return id;
    }
    void set_id(SDL_TimerID id){
        this->id=id;
    }
};
