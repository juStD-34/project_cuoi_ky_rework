#include "renderTexture.h"


SDL_Color WHITE = {255 , 255 , 255, 255},
          BLACK = {0, 0, 0, 255},
          GREEN = {0, 255, 0, 255},
          RED = {255, 0, 0, 255},
          BLUE = {0, 0, 255, 255}
          ;

renderTexture::renderTexture()
{
    width = 0;
    height =0;

    mTexture = NULL;
}

renderTexture::~renderTexture()
{
    free();
}

bool renderTexture::loadFromFile(std::string path, SDL_Renderer* gRenderer)
{
    free();

    SDL_Texture* newTexture = NULL;

    SDL_Surface* loadedSurface = IMG_Load (path.c_str());
    if (loadedSurface == NULL)
    {
        std::cout<<"Unable to load image! "<<IMG_GetError();
    }else
    {   
        SDL_SetColorKey (loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format,0, 0xFF, 0xFF));
        newTexture = SDL_CreateTextureFromSurface (gRenderer, loadedSurface);
        if (newTexture == NULL)
        {
            std::cout<<"Unable to create texture from surface "<<SDL_GetError();

        }else
        {
            width = loadedSurface->w;
            height = loadedSurface->h;
        }
        SDL_FreeSurface (loadedSurface);
    }   

    mTexture = newTexture;
    return mTexture != NULL;
}

void renderTexture::free()
{
    if (mTexture != NULL)
    {
        SDL_DestroyTexture(mTexture);

        mTexture = NULL;
        width = 0;
        height =0;
    }
}

void renderTexture::setColor(SDL_Color color)
{
    SDL_SetTextureColorMod(mTexture, color.r, color.g, color.b);
    SDL_SetTextureAlphaMod(mTexture, color.a);
}

void renderTexture::setBlendMode (SDL_BlendMode blending)
{
    SDL_SetTextureBlendMode (mTexture,blending);
}

void renderTexture::render(SDL_Renderer*& gRenderer,int& x, int& y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
    SDL_Rect renderRect = {x,y, width, height};
    if (clip != NULL)
    {
        renderRect.w = clip->w;
        renderRect.h =clip->h;
    }

    SDL_RenderCopyEx(gRenderer, mTexture,clip, &renderRect, angle, center, flip);
}

void renderTexture::renderBkg( SDL_Renderer* gRenderer, SDL_Rect& L_W_Rect)
{
    SDL_RenderCopy(gRenderer, mTexture, NULL,&L_W_Rect);

}