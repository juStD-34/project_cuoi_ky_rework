#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "src/Ball.h"
#include <SDL_mixer.h>
#include <time.h>
#include <cstdlib>
#include "src/hole.h"
using namespace std;


SDL_Color WHITE = {255 , 255 , 255, 255},
          BLACK = {0, 0, 0, 255},
          GREEN = {0, 255, 0, 255},
          RED = {255, 0, 0, 255},
          BLUE = {0, 0, 255, 255},
          SANDY_BROWN = {244,164, 96, 255}
          ;

const int SCREEN_WIDTH = 680,
          SCREEN_HEIGHT = 480,
          L_W_WIDTH = 150,
          L_W_HEIGHT = 150,
          RES_BUTTON_WIDTH = 100,
          RES_BUTTON_HEIGHT = 60,
          QUIT_BUTTON_WIDTH = 100,
          QUIT_BUTTON_HEIGHT = 60,
          START_BUTTON_WIDTH = 250,
          START_BUTTON_HEIGHT = 80,
          MUSIC_BUTTON_WIDTH = 30,
          MUSIC_BUTTON_HEIGHT = 30,
          HOW_PLAY_BUTTON_W = 250,
          HOW_PLAY_BUTTON_H = 80,
          HOW_PLAY_SCREEN_W = 330,
          HOW_PLAY_SCREEN_H = 440,
          FONT_SIZE = 16;

int HIGHSCR_X = 0, HIGHTSCR_Y = 0,
    SCORE_X = 250, SCORE_Y = 0,
    COUNT_PLAY_X = 500, COUNT_PLAY_Y = 0,
    HOW_PLAY_SCREEN_X = SCREEN_WIDTH/2 - HOW_PLAY_SCREEN_W/2, HOW_PLAY_SCREEN_Y= 20,
    MUSIC_BUTTON_X = 650, MUSIC_BUTTON_Y  = 0;

SDL_Rect L_W_Rect = {SCREEN_WIDTH/2 - L_W_WIDTH/2 , SCREEN_HEIGHT/2 - L_W_HEIGHT/2 -140, L_W_WIDTH, L_W_HEIGHT};
SDL_Rect RESTART_BUTTON_RECT = {SCREEN_WIDTH/2 - RES_BUTTON_WIDTH/2, SCREEN_HEIGHT - RES_BUTTON_HEIGHT/2 - 200, RES_BUTTON_WIDTH, RES_BUTTON_HEIGHT};
SDL_Rect QUIT_BUTTON_RECT = {SCREEN_WIDTH/2 - QUIT_BUTTON_WIDTH/2, SCREEN_HEIGHT - QUIT_BUTTON_HEIGHT/2 - 100, QUIT_BUTTON_WIDTH, QUIT_BUTTON_HEIGHT};
SDL_Rect START_BUTTON_RECT = {SCREEN_WIDTH/2 - START_BUTTON_WIDTH/2, SCREEN_HEIGHT/2 - RES_BUTTON_HEIGHT/2 -100, START_BUTTON_WIDTH, START_BUTTON_HEIGHT};
SDL_Rect HOW_PLAY_BUTTON_RECT = { SCREEN_WIDTH/2 - HOW_PLAY_BUTTON_W/2 , SCREEN_HEIGHT/2 - HOW_PLAY_BUTTON_H/2 +100 , HOW_PLAY_BUTTON_W, HOW_PLAY_BUTTON_H};
SDL_Rect HOW_PLAY_SCREEN_RECT = {HOW_PLAY_SCREEN_X, HOW_PLAY_SCREEN_Y, HOW_PLAY_SCREEN_W, HOW_PLAY_SCREEN_H};
SDL_Rect MUSIC_BUTTON_RECT  = {MUSIC_BUTTON_X, MUSIC_BUTTON_Y, MUSIC_BUTTON_WIDTH, MUSIC_BUTTON_HEIGHT};

const std::string INPUT_BALL = "image/ball4.png",
                  INPUT_ARROW = "image/arrow2.png",
                  INPUT_HOLE = "image/hole.png",
                  WIN_BKG = "image/win background.png",
                  LOSE_BKG = "image/lose background.png",
                  RESTART_BUTTON_STR = "image/restart_button.png",
                  QUIT_BUTTON_STR = "image/quit_button.png",
                  START_BUTTON_STR = "image/start_button(1).png",
                  HOW_PLAY_STR = "image/how_play_button.png",
                  MUSIC_BUTTON_STR = "image/music button.png",
                  MUTE_BUTTON_STR = "image/music_mute.png",
                  HOW_PLAY_SCREEN_STR = "image/how to play screen.png",
                  BKG_SOUND = "bkg_sound.wav",
                  BALL_DROP = "ball_drop.wav";
std::string FONT_NAME = "Monique-RegularRound20.otf";



int main(int argc, char* argv[])
{
    int highestScore = 0;
    SDL_Window* gWindow = NULL;
    SDL_Renderer* gRenderer = NULL;
    bool howPlayCheck = false;
    renderTexture ballTexture, arrowTexture, holeTexture, loseTexture, winTexture;
    renderTexture restartTexture, quitTexture, startTexture, howPlayTexture, howPlayScreen, musicTexture, muteTexture;
    renderTexture highScoreTexture, scoreTexture, countPlayTexture;
    TTF_Font* font = NULL;
    Hole hole(SCREEN_WIDTH,SCREEN_HEIGHT) ;
    Mix_Music* bkgSound = NULL;
    Mix_Chunk* ballSound = NULL;
    if (!init(gWindow,gRenderer, SCREEN_HEIGHT, SCREEN_WIDTH, WHITE))
    {
        std::cout<<"Failed to init"<<std::endl;
    }else
    {
        if (!loadMedia(ballTexture,gRenderer,INPUT_BALL) || !loadMedia(arrowTexture,gRenderer,INPUT_ARROW)||!loadMedia(holeTexture,gRenderer, INPUT_HOLE)|| 
            !loadMedia(loseTexture,gRenderer,LOSE_BKG) || !loadMedia(winTexture, gRenderer, WIN_BKG)||
            !loadMedia(restartTexture,gRenderer,RESTART_BUTTON_STR)|| !loadMedia(quitTexture,gRenderer, QUIT_BUTTON_STR)||
            !loadMedia(startTexture,gRenderer,START_BUTTON_STR)|| !loadMedia(howPlayTexture, gRenderer, HOW_PLAY_STR)||
            !loadMedia(musicTexture, gRenderer, MUSIC_BUTTON_STR)||!loadMedia(muteTexture, gRenderer, MUTE_BUTTON_STR)||
            !loadMedia(howPlayScreen,gRenderer,HOW_PLAY_SCREEN_STR)||
            !loadMusicMedia(bkgSound, ballSound, BKG_SOUND, BALL_DROP))
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
            Button howPlayButton(HOW_PLAY_BUTTON_RECT, howPlayTexture);
            Button musicButton (MUSIC_BUTTON_RECT, musicTexture);
            Button muteButton (MUSIC_BUTTON_RECT, muteTexture);
            bool start = false;
            bool music = true;
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
                        hole.resetHole(SCREEN_WIDTH, SCREEN_HEIGHT);
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

                    if (music == true && musicButton.handleEvent(&e) == true)
                    {
                        music = false;
                    }
                    else if (music == false && muteButton.handleEvent(&e) == true)
                    {
                        music = true;
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
                    if (!loadFontMedia(highScoreTexture, gRenderer, highScoreSTR, font, FONT_NAME, FONT_SIZE, BLACK) || 
                        !loadFontMedia(scoreTexture, gRenderer, scoreSTR, font, FONT_NAME, FONT_SIZE, BLACK) ||
                        !loadFontMedia(countPlayTexture,gRenderer,countPlaySTR,font, FONT_NAME, FONT_SIZE, BLACK))
                    {
                        std::cout<<"Failed to load text texture"<<std::endl;
                    }
                    else 
                    {
                        highScoreTexture.render(gRenderer, HIGHSCR_X, HIGHTSCR_Y);
                        scoreTexture.render(gRenderer, SCORE_X, SCORE_Y);
                        countPlayTexture.render(gRenderer, COUNT_PLAY_X, COUNT_PLAY_Y);
                    }

                    if (music == true) 
                    {
                        musicButton.render(gRenderer);
                        if (Mix_PausedMusic() == 1)
                        {
                            Mix_ResumeMusic();
                        }
                    }else
                    {
                        muteButton.render(gRenderer);
                        Mix_PauseMusic();
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

    close(ballTexture, arrowTexture,holeTexture ,gWindow, gRenderer, font, bkgSound, ballSound);
    return 0;
}

