
 class Screen 
{
    public:
    virtual void render()=0;
    virtual void event_handle() = 0;
    Window *win;

};