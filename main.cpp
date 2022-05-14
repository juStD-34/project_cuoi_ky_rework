#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "ball.h"
#include <time.h>
#include <cstdlib>
using namespace std;

const std::string INPUT_BALL = "ball.bmp",
                  INPUT_ARROW = "arrow2.png",
                  INPUT_HOLE = "hole.bmp",
                  WIN_BKG = "win background.png",
                  LOSE_BKG = "lose background.png",
                  RESTART_BUTTON_STR = "restart_button.png",
                  QUIT_BUTTON_STR = "quit_button.png";
const int SCREEN_WIDTH = 680,
          SCREEN_HEIGHT = 480,
          L_W_WIDTH = 200,
          L_W_HEIGHT = 200,
          RES_BUTTON_WIDTH = 100,
          RES_BUTTON_HEIGHT = 60,
          QUIT_BUTTON_WIDTH = 100,
          QUIT_BUTTON_HEIGHT = 60;

SDL_Rect L_W_Rect ={SCREEN_WIDTH/2 - L_W_WIDTH/2 , SCREEN_HEIGHT/2 - L_W_HEIGHT/2 -140, L_W_WIDTH, L_W_HEIGHT};
SDL_Rect RESTART_BUTTON_RECT = {SCREEN_WIDTH/2 - RES_BUTTON_WIDTH/2, SCREEN_HEIGHT - RES_BUTTON_HEIGHT/2 - 200, RES_BUTTON_WIDTH, RES_BUTTON_HEIGHT};
SDL_Rect QUIT_BUTTON_RECT = {SCREEN_WIDTH/2 - QUIT_BUTTON_WIDTH/2, SCREEN_HEIGHT - QUIT_BUTTON_HEIGHT/2 - 100, QUIT_BUTTON_WIDTH, QUIT_BUTTON_HEIGHT};
class Hole
{
private:
    int posX, posY;
    void randomPosition()
    {
        srand(time(NULL));
        posX = rand()% (SCREEN_WIDTH - HOLE_WIDTH/2);
        posY = rand()% (SCREEN_HEIGHT - HOLE_HEIGHT/2);
    }
public:

    const int HOLE_WIDTH = 20;
    const int HOLE_HEIGHT = 20;

    Hole()
    {
        randomPosition();
    }

    ~Hole(){};
    void render(renderTexture& gHoleTexture, SDL_Renderer*& gRenderer)
    {
        gHoleTexture.render(gRenderer, posX, posY);
    }

    SDL_Point getPos()
    {
        SDL_Point p;
        p.x = posX;
        p.y = posY;
        return p;
    }
    void resetHole()
    {
        randomPosition();
    }
};

bool init(SDL_Window*& gWindow, SDL_Renderer*& gRenderer);
bool loadMedia(renderTexture& rendedTexture, SDL_Renderer* & gRenderer, const std::string& path);
void close (renderTexture& ballTexture, renderTexture& arrowTexture , renderTexture& holeTexture,  SDL_Window*& gWindow, SDL_Renderer*& gRenderer);


int main(int argc, char* argv[])
{
    SDL_Window* gWindow = NULL;
    SDL_Renderer* gRenderer = NULL;
    renderTexture ballTexture, arrowTexture, holeTexture, loseTexture, winTexture;
    renderTexture restartTexture, quitTexture;
    Hole hole ;
    if (!init(gWindow,gRenderer))
    {
        std::cout<<"Failed to init"<<std::endl;
    }else
    {
        if (!loadMedia(ballTexture,gRenderer,INPUT_BALL) || !loadMedia(arrowTexture,gRenderer,INPUT_ARROW)||!loadMedia(holeTexture,gRenderer, INPUT_HOLE)|| 
            !loadMedia(loseTexture,gRenderer,LOSE_BKG) || !loadMedia(winTexture, gRenderer, WIN_BKG)||
            !loadMedia(restartTexture,gRenderer,RESTART_BUTTON_STR)|| !loadMedia(quitTexture,gRenderer, QUIT_BUTTON_STR) )
        {
            std::cout<<"Failed to load media"<<std::endl;
        }
        else
        {
            bool quit = false;

            SDL_Event e;

            Ball ball(SCREEN_WIDTH,SCREEN_HEIGHT);
            Button restartButton(RESTART_BUTTON_RECT,restartTexture);
            Button quitButton(QUIT_BUTTON_RECT,quitTexture);
            while (quit == false)
            {
                
                while (SDL_PollEvent( &e) !=0)
                {
                    if (e.type == SDL_QUIT)
                    {
                        quit = true;
                    }

                    ball.handleEvent(e);

                    if ((ball.isWin == true || ball.isLose == true)&& restartButton.handleEvent(&e) == true)
                    {
                        std::cout<<1;
                        ball.resetBall(SCREEN_WIDTH,SCREEN_HEIGHT);
                        hole.resetHole();
                        break;
                    }
                    if ((ball.isWin == true || ball.isLose == true) && quitButton.handleEvent(&e) == true)
                    {
                        quit = true;
                        break;
                    }
                }
                
                SDL_Point p = hole.getPos();
                if (ball.isLose == false && ball.isWin == false) ball.move(SCREEN_WIDTH, SCREEN_HEIGHT,p.x, p.y);

                SDL_SetRenderDrawColor(gRenderer, 0XFF, 0xFF,0xFF, 0xFF);
                SDL_RenderClear( gRenderer);

                hole.render(holeTexture, gRenderer);
                ball.render(ballTexture, gRenderer, arrowTexture);
                if (ball.isWin == true) 
                {
                    winTexture.renderBkg(gRenderer, L_W_Rect);
                    restartButton.render(gRenderer);
                    quitButton.render(gRenderer);
                    //restartTexture.renderBkg(gRenderer, RESTART_BUTTON_RECT);
                }
                if (ball.isLose == true) 
                {
                    loseTexture.renderBkg(gRenderer, L_W_Rect);
                    restartButton.render(gRenderer);
                    quitButton.render(gRenderer);
                }

                SDL_RenderPresent( gRenderer);
            }
        }
    }

    close(ballTexture, arrowTexture,holeTexture ,gWindow, gRenderer);
    return 0;
}

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
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

                int imgFlags = IMG_INIT_PNG;
                if ( ! (IMG_Init(imgFlags) & imgFlags) )
                {
                    std::cout<<"SDL_image couldn't init! "<<IMG_GetError();
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

void close (renderTexture& ballTexture,renderTexture& arrowTexture ,renderTexture& holeTexture, SDL_Window*& gWindow, SDL_Renderer*& gRenderer)
{
    ballTexture.free();
    holeTexture.free();
    arrowTexture.free();
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow( gWindow);
    gRenderer = NULL;
    gWindow = NULL;

    IMG_Quit();
    SDL_Quit();
}