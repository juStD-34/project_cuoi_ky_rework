#include "init.h"


bool init(SDL_Window*& gWindow, SDL_Renderer*& gRenderer)
{
    bool success = true;

    if (SDL_Init (SDL_INIT_VIDEO) < 0)
    {
        std::cout<<"SDL couldn't init "<<SDL_GetError();
        success = false;
    }
    else
    {
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"1"))
        {
            std::cout<<"Linear texture filtering not enable!";
        }
        gWindow = SDL_CreateWindow("Ball game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
        if (gWindow == NULL)
        {
            std::cout<<"Window coudn't create "<<SDL_GetError();
            success = false;
        }
        else
        {
            gRenderer = SDL_CreateRenderer (gWindow, -1, SDL_RENDERER_ACCELERATED| SDL_RENDERER_PRESENTVSYNC
            );
            if (gRenderer == NULL)
            {
                std::cout<<"Renderer could not be created! "<<SDL_GetError();
                success = false;
            }
            else
            {
                SDL_SetRenderDrawColor(gRenderer,BLUE.r, BLUE.g, BLUE.b, BLUE.a);

                int imgFlags = IMG_INIT_PNG;
                if ( ! (IMG_Init(imgFlags) & imgFlags) )
                {
                    std::cout<<"SDL_image couldn't init! "<<IMG_GetError();
                    success = false;
                }

                if (TTF_Init() == -1)
                {
                    std::cout<<"SDL_ttf could not to init"<<TTF_GetError();
                    success = false;
                }

                if ( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048) <0)
                {
                    std::cout<<"SDL mixer could not init "<<Mix_GetError();
                    success = false;
                }
            }
        }
    }
    return success;
}

bool loadMedia(renderTexture& rendedTexture, SDL_Renderer* & gRenderer,const std::string& path)
{
    bool success = true;

    if (rendedTexture.loadFromFile(path, gRenderer) == false)
    {
        success = false;
        std::cout<<"Failed to load "<<path<<"texture";
    } 
    return success;
}

bool loadFontMedia(renderTexture& rendTexture, SDL_Renderer* & gRenderer, std::string& textString, TTF_Font* & font)
{
    bool success= true;

    font = TTF_OpenFont(FONT_NAME.c_str(), FONT_SIZE);
    if (font == NULL)
    {
        std::cout<<"Failed to load font !"<<TTF_GetError();
        success = false;
    }else
    {
        if (rendTexture.loadFromRenderedText(textString,gRenderer,font,BLACK) == false)
        {
            std::cout<<"Failed to render text texture!";
            success = false;
        }
    }

    return success;

}

bool loadMusicMedia(Mix_Music*& bkgMusic, Mix_Chunk*& ballSound)
{
    bool success = true;
    bkgMusic = Mix_LoadMUS(BKG_SOUND.c_str());
    ballSound = Mix_LoadWAV(BALL_DROP.c_str());
    if (bkgMusic == NULL)
    {
        std::cout<<"Failed to load back ground music";
        success = false;
    }
    if (ballSound == NULL)
    {
        std::cout<<"Failed to load ball sound";
        success = false;
    }
    return success;
}
void close (renderTexture& ballTexture,renderTexture& arrowTexture ,renderTexture& holeTexture, SDL_Window*& gWindow, SDL_Renderer*& gRenderer, TTF_Font* font)
{
    ballTexture.free();
    holeTexture.free();
    arrowTexture.free();
    TTF_CloseFont(font);
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow( gWindow);
    font = NULL;
    gRenderer = NULL;
    gWindow = NULL;

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}