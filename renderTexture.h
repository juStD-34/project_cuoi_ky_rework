#pragma
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

class renderTexture
{
private:
    int width ;
    int height;

    SDL_Texture* mTexture;
public:
    renderTexture(/* args */);
    ~renderTexture();

    bool loadFromFile (std::string path, SDL_Renderer* gRenderer);

    void free();

    void setColor (SDL_Color color);

    void setBlendMode(SDL_BlendMode blending);

    void render(SDL_Renderer*& gRenderer, int& x, int& y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

    int getWidth();
    int getHeight();

    void renderBkg(SDL_Renderer* gRenderer, SDL_Rect& L_W_Rect);
};

