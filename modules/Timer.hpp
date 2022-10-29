#include <SDL2/SDL.h>
#include <iostream>
class Timer
{
    int time1;
    int time2;
    bool active;
    SDL_TimerID id;


public:
    Timer(){
        active=false;
    }
    bool is_active(){
        return active;
    }
    void set_timer(int time)
    {
        if(time<=0) return;
        active=true;
        time1 = time2 = time;

    }
    int get_time(int player)
    {
        if (player == 0)
        {
            return time1;
        }
        else if (player == 1)
        {
            return time2;
        }
        return 0;
    }
    int adjust_time(int player)
    {
        int &time = player ? time2 : time1;
        time -= TIMER;
        if (time == 0)
        {

            return 2;
        }
        if (time % 1000 == 0)
        {
            return 1;
        }

        return 0;
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
