#pragma once
#include <iostream>
#include <SDL.h>
#include <time.h>
#include <conio.h>
#include "renderTexture.h"
class Hole
{
private:
    int posX, posY;
    void randomPosition(const int& SCREEN_WIDTH, const int& SCREEN_HEIGHT)
    {
        srand(time(NULL));
        posX = rand()% (SCREEN_WIDTH - HOLE_WIDTH/2 -10 +1) +10;
        posY = rand()% (SCREEN_HEIGHT - HOLE_HEIGHT/2 -10 +1) +10 ;
    }
public:

    const int HOLE_WIDTH = 20;
    const int HOLE_HEIGHT = 20;

    Hole(const int& SCREEN_WIDTH, const int& SCREEN_HEIGHT)
    {
        randomPosition(SCREEN_WIDTH, SCREEN_HEIGHT);
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
    void resetHole(const int& SCREEN_WIDTH, const int& SCREEN_HEIGHT)
    {
        randomPosition(SCREEN_WIDTH,SCREEN_HEIGHT);
    }
};