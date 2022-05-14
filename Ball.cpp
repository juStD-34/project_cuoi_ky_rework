#include "Ball.h"
#include <cmath>


using namespace std;

Ball::Ball(const int SCREEN_WIDTH, const int SCREEN_HEIGHT)
{
    PosX = SCREEN_WIDTH/2 - BALL_WIDTH/2;
    PosY = SCREEN_HEIGHT/2 - BALL_HEIGHT/2;
    randomPosition(SCREEN_WIDTH,  SCREEN_HEIGHT);
    VelX = 0;
    VelY = 0;

    speed = 0;

    degeree = -90;
    angular = 0;
    countPlay = 0;

    isRolling = false;
    isWin = false;
    isLose = false;
}

Ball::~Ball()
{

}

void Ball::handleEvent( SDL_Event& e )
{
    if (isRolling == false && isWin == false && isLose == false)
	{
        if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
        {
            switch( e.key.keysym.sym )
            {
                case SDLK_LEFT: angular -=1; break;
                case SDLK_RIGHT: angular +=1; break;
            }
        }
        //If a key was released
        else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
        {
            //Adjust the velocity
            switch( e.key.keysym.sym )
            {
                case SDLK_LEFT: angular += 1; break;
                case SDLK_RIGHT: angular -= 1; break;
            }
        }
    }
    if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE && isWin == false)
    {
        isRolling = !isRolling;
        if (isRolling == false)
        {
            degeree = -90;
        }
    }
}

void Ball::move(const int SCREEN_WIDTH, const int SCREEN_HEIGHT, int& holeX, int& holeY)
{
    if (isRolling == false && isWin == false&& isLose == false)
    {
        degeree += angular;
    } else
    {
        speed +=0.8;
        VelX = std::cos(degeree* M_PI / 180) * BALL_VEL;
        VelY = std::sin(degeree* M_PI / 180) * BALL_VEL;

        PosX += VelX;

        if (PosX < 0 )
        {
            degeree = 180 - degeree;
            PosX = 0;
        }
        if (PosX + BALL_WIDTH > SCREEN_WIDTH)
        {
            degeree = 180 - degeree;
            PosX = SCREEN_WIDTH - BALL_WIDTH;
        }
        PosY += VelY;

        if ( PosY < 0 || (PosY + BALL_HEIGHT > SCREEN_HEIGHT))
        {
            degeree = -degeree;
            if (PosY <0) PosY =0;
            if (PosY + BALL_HEIGHT > SCREEN_HEIGHT) PosY = SCREEN_HEIGHT - BALL_HEIGHT;
        }
        if (ballInHole(holeX,holeY) == true)    
        {
            isRolling = false;
            isWin = true;
        }
        if (speed >= 60)
        { 
            isRolling = false;speed =0;countPlay ++;
            if (countPlay >= MAX_PLAY ) isLose = true;
        }
        SDL_Delay(speed);

    }
}

void Ball::render(renderTexture& ballTexture, SDL_Renderer*& gRenderer, renderTexture& gArrow)
{
    if (isWin == false)
    {
        if (isRolling == false)
        {
            SDL_Point center = {0,2};
            int arrowX = PosX + BALL_WIDTH/2;
            int arrowY = PosY + BALL_HEIGHT/2;
            gArrow.render(gRenderer,arrowX ,arrowY , NULL, degeree, &center, SDL_FLIP_NONE);
        }
        ballTexture.render(gRenderer, PosX, PosY);
    }
}

void Ball::resetBall(const int SCREEN_WIDTH, const int SCREEN_HEIGHT)
{
    randomPosition(SCREEN_WIDTH,  SCREEN_HEIGHT);
    VelX = 0;
    VelY = 0;

    speed = 0;

    degeree = -90;
    angular = 0;
    countPlay = 0;

    isRolling = false;
    isWin = false;
    isLose = false;
}

bool Ball::ballInHole(int&  holeX, int& holeY)
{
    if (PosX + BALL_WIDTH/2 > holeX && PosX < holeX && PosY + BALL_HEIGHT/2 > holeY && PosY < holeY)
        return true;
    if (PosX - BALL_WIDTH/2 < holeX && PosX > holeX && PosY + BALL_HEIGHT/2 > holeY && PosY < holeY)
        return true;
    if (PosX + BALL_WIDTH/2 > holeX && PosX < holeX && PosY - BALL_HEIGHT/2 < holeY && PosY > holeY)
        return true;
    if (PosX - BALL_WIDTH/2 < holeX && PosX > holeX && PosY - BALL_HEIGHT/2 < holeY && PosY > holeY)
        return true;
    
    return false;
}