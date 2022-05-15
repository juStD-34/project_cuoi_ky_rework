#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "ball.h"
#include <time.h>
#include <cstdlib>
using namespace std;

SDL_Color WHITE = {255 , 255 , 255, 255},
          BLACK = {0, 0, 0, 255},
          GREEN = {0, 255, 0, 255},
          RED = {255, 0, 0, 255},
          BLUE = {0, 0, 255, 255},
          SANDY_BROWN = {244,164, 96, 255}
          ;
const std::string INPUT_BALL = "ball4.png",
                  INPUT_ARROW = "arrow2.png",
                  INPUT_HOLE = "hole.png",
                  WIN_BKG = "win background.png",
                  LOSE_BKG = "lose background.png",
                  RESTART_BUTTON_STR = "restart_button.png",
                  QUIT_BUTTON_STR = "quit_button.png",
                  START_BUTTON_STR = "start_button.png";
std::string FONT_NAME = "Monique-RegularRound20.otf";
const int SCREEN_WIDTH = 680,
          SCREEN_HEIGHT = 480,
          L_W_WIDTH = 200,
          L_W_HEIGHT = 200,
          RES_BUTTON_WIDTH = 100,
          RES_BUTTON_HEIGHT = 60,
          QUIT_BUTTON_WIDTH = 100,
          QUIT_BUTTON_HEIGHT = 60,
          START_BUTTON_WIDTH = 350,
          START_BUTTON_HEIGHT = 200,
          FONT_SIZE = 16;
int HIGHSCR_X = 0, HIGHTSCR_Y = 0,
    SCORE_X = 300, SCORE_Y = 0,
    COUNT_PLAY_X = 600, COUNT_PLAY_Y = 0;

SDL_Rect L_W_Rect ={SCREEN_WIDTH/2 - L_W_WIDTH/2 , SCREEN_HEIGHT/2 - L_W_HEIGHT/2 -140, L_W_WIDTH, L_W_HEIGHT};
SDL_Rect RESTART_BUTTON_RECT = {SCREEN_WIDTH/2 - RES_BUTTON_WIDTH/2, SCREEN_HEIGHT - RES_BUTTON_HEIGHT/2 - 200, RES_BUTTON_WIDTH, RES_BUTTON_HEIGHT};
SDL_Rect QUIT_BUTTON_RECT = {SCREEN_WIDTH/2 - QUIT_BUTTON_WIDTH/2, SCREEN_HEIGHT - QUIT_BUTTON_HEIGHT/2 - 100, QUIT_BUTTON_WIDTH, QUIT_BUTTON_HEIGHT};
SDL_Rect START_BUTTON_RECT = {SCREEN_WIDTH/2 - START_BUTTON_WIDTH/2, SCREEN_HEIGHT/2 - RES_BUTTON_HEIGHT/2 -100, START_BUTTON_WIDTH, START_BUTTON_HEIGHT};

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
bool loadFontMedia(renderTexture& rendTexture, SDL_Renderer* & gRenderer, std::string& textString, TTF_Font* & font);
void close (renderTexture& ballTexture, renderTexture& arrowTexture , renderTexture& holeTexture,  SDL_Window*& gWindow, SDL_Renderer*& gRenderer, TTF_Font* font);


int main(int argc, char* argv[])
{
    int highestScore = 0;
    SDL_Window* gWindow = NULL;
    SDL_Renderer* gRenderer = NULL;
    renderTexture ballTexture, arrowTexture, holeTexture, loseTexture, winTexture;
    renderTexture restartTexture, quitTexture, startTexture;
    renderTexture highScoreTexture, scoreTexture, countPlayTexture;
    TTF_Font* font = NULL;
    Hole hole ;
    if (!init(gWindow,gRenderer))
    {
        std::cout<<"Failed to init"<<std::endl;
    }else
    {
        if (!loadMedia(ballTexture,gRenderer,INPUT_BALL) || !loadMedia(arrowTexture,gRenderer,INPUT_ARROW)||!loadMedia(holeTexture,gRenderer, INPUT_HOLE)|| 
            !loadMedia(loseTexture,gRenderer,LOSE_BKG) || !loadMedia(winTexture, gRenderer, WIN_BKG)||
            !loadMedia(restartTexture,gRenderer,RESTART_BUTTON_STR)|| !loadMedia(quitTexture,gRenderer, QUIT_BUTTON_STR),
            !loadMedia(startTexture,gRenderer,START_BUTTON_STR))
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
            Button startButton(START_BUTTON_RECT,startTexture);
            bool start = false;
            while (quit == false)
            {
                while (SDL_PollEvent( &e) !=0)
                {
                    if (e.type == SDL_QUIT)
                    {
                        quit = true;
                    }
                    else
                    if (ball.isLose == false && ball.isWin == false && start == true) ball.handleEvent(e);
                    else
                    if ((ball.isWin == true || ball.isLose == true )&& restartButton.handleEvent(&e) == 1)
                    {
                        if (ball.score > highestScore) highestScore = ball.score;
                        ball.resetBall(SCREEN_WIDTH,SCREEN_HEIGHT);
                        hole.resetHole();
                        break;
                    }
                    else
                    if (( ball.isLose == true || ball.isWin == true) && quitButton.handleEvent(&e) == true)
                    {
                        quit = true;
                        break;
                    }
                    else
                    if (start == false && startButton.handleEvent(&e) == true)
                    {
                        start = true;
                    }
                }
                
                SDL_Point p = hole.getPos();
                if (ball.isLose == false && ball.isWin == false && start == true) ball.move(SCREEN_WIDTH, SCREEN_HEIGHT,p.x, p.y);

                SDL_SetRenderDrawColor(gRenderer, WHITE.r, WHITE.g, WHITE.b, WHITE.a);
                SDL_RenderClear( gRenderer);
                if (start == true)
                {
                    std::string highScoreSTR ="HIGH SCORE : " + std::to_string(highestScore);
                    std::string scoreSTR = "SCORE : " + std::to_string(ball.score);
                    std::string countPlaySTR ="TURN : " + std::to_string(ball.countPlay);
                    if (!loadFontMedia(highScoreTexture, gRenderer, highScoreSTR, font) || 
                        !loadFontMedia(scoreTexture, gRenderer, scoreSTR, font) ||
                        !loadFontMedia(countPlayTexture,gRenderer,countPlaySTR,font))
                    {
                        std::cout<<"Failed to load text texture"<<std::endl;
                    }else 
                    {
                        highScoreTexture.render(gRenderer, HIGHSCR_X, HIGHTSCR_Y);
                        scoreTexture.render(gRenderer, SCORE_X, SCORE_Y);
                        countPlayTexture.render(gRenderer, COUNT_PLAY_X, COUNT_PLAY_Y);
                    }
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
                }else
                    startButton.render(gRenderer);
                SDL_RenderPresent( gRenderer);
            }
        }
    }

    close(ballTexture, arrowTexture,holeTexture ,gWindow, gRenderer, font);
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