#include "Button.h"

Button::Button(SDL_Rect& buttonRect_, renderTexture& buttonTexture_)
{
    buttonRect = buttonRect_;
    buttonTexture = buttonTexture_;
}
void Button::setPos(int x_, int y_)
{
    buttonRect.x = x_;
    buttonRect.y = y_;
}

bool Button::handleEvent( SDL_Event* e)
{
    if (e->type == SDL_MOUSEBUTTONDOWN)
    {
        int x,y;
        SDL_GetMouseState(&x, &y);
        bool inside = true;
        if (x < buttonRect.x)
        {
            inside = false;
        }
        if (y < buttonRect.y )
        {
            inside = false;
        }
        if (y > (buttonRect.y + buttonRect.h))
        {
            inside = false;
        }
        if (x > (buttonRect.x + buttonRect.w))
        {
            inside = false;
        }
        return inside;
    }
    return false;
}
void Button::render(SDL_Renderer* gRenderer)
{
    buttonTexture.renderBkg(gRenderer,buttonRect);
}