#pragma once
#include "Button.h"
#include <iostream>
#include <SDL_mixer.h>

const std::string INPUT_BALL = "image/ball4.png",
                  INPUT_ARROW = "image/arrow2.png",
                  INPUT_HOLE = "image/hole.png",
                  WIN_BKG = "image/win background.png",
                  LOSE_BKG = "image/lose background.png",
                  RESTART_BUTTON_STR = "image/restart_button.png",
                  QUIT_BUTTON_STR = "image/quit_button.png",
                  START_BUTTON_STR = "image/start_button(1).png",
                  HOW_PLAY_STR = "image/how_play_button.png",
                  HOW_PLAY_SCREEN_STR = "image/how to play screen.png",
                  BKG_SOUND = "bkg_sound.wav",
                  BALL_DROP = "ball_drop.wav";
std::string FONT_NAME = "Monique-RegularRound20.otf";

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
          HOW_PLAY_BUTTON_W = 250,
          HOW_PLAY_BUTTON_H = 80,
          HOW_PLAY_SCREEN_W = 330,
          HOW_PLAY_SCREEN_H = 440,
          FONT_SIZE = 16;

int HIGHSCR_X = 0, HIGHTSCR_Y = 0,
    SCORE_X = 300, SCORE_Y = 0,
    COUNT_PLAY_X = 600, COUNT_PLAY_Y = 0,
    HOW_PLAY_SCREEN_X = SCREEN_WIDTH/2 - HOW_PLAY_SCREEN_W/2, HOW_PLAY_SCREEN_Y= 20;

SDL_Rect L_W_Rect = {SCREEN_WIDTH/2 - L_W_WIDTH/2 , SCREEN_HEIGHT/2 - L_W_HEIGHT/2 -140, L_W_WIDTH, L_W_HEIGHT};
SDL_Rect RESTART_BUTTON_RECT = {SCREEN_WIDTH/2 - RES_BUTTON_WIDTH/2, SCREEN_HEIGHT - RES_BUTTON_HEIGHT/2 - 200, RES_BUTTON_WIDTH, RES_BUTTON_HEIGHT};
SDL_Rect QUIT_BUTTON_RECT = {SCREEN_WIDTH/2 - QUIT_BUTTON_WIDTH/2, SCREEN_HEIGHT - QUIT_BUTTON_HEIGHT/2 - 100, QUIT_BUTTON_WIDTH, QUIT_BUTTON_HEIGHT};
SDL_Rect START_BUTTON_RECT = {SCREEN_WIDTH/2 - START_BUTTON_WIDTH/2, SCREEN_HEIGHT/2 - RES_BUTTON_HEIGHT/2 -100, START_BUTTON_WIDTH, START_BUTTON_HEIGHT};
SDL_Rect HOW_PLAY_BUTTON_RECT = { SCREEN_WIDTH/2 - HOW_PLAY_BUTTON_W/2 , SCREEN_HEIGHT/2 - HOW_PLAY_BUTTON_H/2 +100 , HOW_PLAY_BUTTON_W, HOW_PLAY_BUTTON_H};
SDL_Rect HOW_PLAY_SCREEN_RECT = {HOW_PLAY_SCREEN_X, HOW_PLAY_SCREEN_Y, HOW_PLAY_SCREEN_W, HOW_PLAY_SCREEN_H};


bool init(SDL_Window*& gWindow, SDL_Renderer*& gRenderer);

bool loadMedia(renderTexture& rendedTexture, SDL_Renderer* & gRenderer, const std::string& path);

bool loadFontMedia(renderTexture& rendTexture, SDL_Renderer* & gRenderer, std::string& textString, TTF_Font* & font);

bool loadMusicMedia(Mix_Music*& bkgMusic, Mix_Chunk*& ballSound);

void close (renderTexture& ballTexture, renderTexture& arrowTexture , renderTexture& holeTexture,  SDL_Window*& gWindow, SDL_Renderer*& gRenderer, TTF_Font* font);
