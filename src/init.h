#pragma once
#include "Button.h"
#include <iostream>
#include <SDL_mixer.h>


bool init(SDL_Window*& gWindow, SDL_Renderer*& gRenderer,const int& SCREEN_HEIGHT,const int& SCREEN_WIDTH, SDL_Color color);


bool loadMedia(renderTexture& rendedTexture, SDL_Renderer* & gRenderer, const std::string& path);

bool loadFontMedia(renderTexture& rendTexture, SDL_Renderer* & gRenderer, std::string& textString, TTF_Font* & font);

bool loadFontMedia(renderTexture& rendTexture, SDL_Renderer* & gRenderer, std::string& textString, TTF_Font* & font, std::string& FONT_NAME,const int& FONT_SIZE, SDL_Color color);

bool loadMusicMedia(Mix_Music*& bkgMusic, Mix_Chunk*& ballSound,const  std::string& BKG_SOUND, const std::string& BALL_DROP);

void close (renderTexture& ballTexture, renderTexture& arrowTexture , renderTexture& holeTexture,  SDL_Window*& gWindow, SDL_Renderer*& gRenderer, TTF_Font* font, Mix_Music* bkgSound, Mix_Chunk* ballSound);

