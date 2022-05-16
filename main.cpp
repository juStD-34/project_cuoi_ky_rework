#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "src/Ball.h"
#include <SDL_mixer.h>
#include <time.h>
#include <cstdlib>
using namespace std;

class Hole
{
private:
    int posX, posY;
    void randomPosition()
    {
        srand(time(NULL));
        posX = rand()% (SCREEN_WIDTH - HOLE_WIDTH/2 -10 +1) +10;
        posY = rand()% (SCREEN_HEIGHT - HOLE_HEIGHT/2 -10 +1) +10 ;
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

int main(int argc, char* argv[])
{
    int highestScore = 0;
    SDL_Window* gWindow = NULL;
    SDL_Renderer* gRenderer = NULL;
    bool howPlayCheck = false;
    renderTexture ballTexture, arrowTexture, holeTexture, loseTexture, winTexture;
    renderTexture restartTexture, quitTexture, startTexture, howPlayTexture, howPlayScreen;
    renderTexture highScoreTexture, scoreTexture, countPlayTexture;
    TTF_Font* font = NULL;
    Hole hole ;
    Mix_Music* bkgSound = NULL;
    Mix_Chunk* ballSound = NULL;
    if (!init(gWindow,gRenderer))
    {
        std::cout<<"Failed to init"<<std::endl;
    }else
    {
        if (!loadMedia(ballTexture,gRenderer,INPUT_BALL) || !loadMedia(arrowTexture,gRenderer,INPUT_ARROW)||!loadMedia(holeTexture,gRenderer, INPUT_HOLE)|| 
            !loadMedia(loseTexture,gRenderer,LOSE_BKG) || !loadMedia(winTexture, gRenderer, WIN_BKG)||
            !loadMedia(restartTexture,gRenderer,RESTART_BUTTON_STR)|| !loadMedia(quitTexture,gRenderer, QUIT_BUTTON_STR),
            !loadMedia(startTexture,gRenderer,START_BUTTON_STR), !loadMedia(howPlayTexture, gRenderer, HOW_PLAY_STR),
            !loadMedia(howPlayScreen,gRenderer,HOW_PLAY_SCREEN_STR),
            !loadMusicMedia(bkgSound, ballSound))
        {
            std::cout<<"Failed to load media"<<std::endl;
        }
        else
        {
            bool quit = false;
            SDL_Event e;
            std::cout<<bkgSound;
            Ball ball(SCREEN_WIDTH,SCREEN_HEIGHT);
            Button restartButton(RESTART_BUTTON_RECT,restartTexture);
            Button quitButton(QUIT_BUTTON_RECT,quitTexture);
            Button startButton(START_BUTTON_RECT,startTexture);
            Button howPlayButton(HOW_PLAY_BUTTON_RECT, howPlayTexture);
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
                        Mix_PlayMusic(bkgSound, -1);
                    }else
                    if (howPlayCheck == false && howPlayButton.handleEvent(&e) == true)
                    {
                        howPlayCheck = true;
                    }
                    if (howPlayCheck == true && e.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
                    {
                        howPlayCheck = false;
                    }
                }
                
                SDL_Point p = hole.getPos();
                if (ball.isLose == false && ball.isWin == false && start == true)
                     ball.move(SCREEN_WIDTH, SCREEN_HEIGHT,p.x, p.y, ballSound);

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
                {
                    if (howPlayCheck == false)
                    {
                        startButton.render(gRenderer);
                        howPlayButton.render(gRenderer);
                    }else
                    {
                        howPlayScreen.renderBkg(gRenderer,HOW_PLAY_SCREEN_RECT);
                        
                    }
                }
                SDL_RenderPresent( gRenderer);
            }
        }
    }

    close(ballTexture, arrowTexture,holeTexture ,gWindow, gRenderer, font);
    return 0;
}
