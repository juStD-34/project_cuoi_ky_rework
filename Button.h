#pragma
#include <iostream>
#include <SDL.h>
#include "renderTexture.h"
class Button
{
private:
    SDL_Rect buttonRect;
    renderTexture buttonTexture;
public:
    Button(/* args */){};
    
    Button(SDL_Rect& buttonRect_, renderTexture& buttonTexture_);
    void setPos(int _x, int _y);

    bool handleEvent (SDL_Event* e);

    void render(SDL_Renderer* gRenderer);
};