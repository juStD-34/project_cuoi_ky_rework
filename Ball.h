#pragma

#include <SDL.h>
#include "Button.h"
#include<ctime>
const int MAX_PLAY = 4;
class Ball
{
private:
    int PosX, PosY;

    int VelX,VelY;

    int degeree;
    int angular;
    bool isRolling ;
    void randomPosition(const int SCREEN_WIDTH, const int SCREEN_HEIGHT)
    {
        srand(time(NULL));
        PosX = rand()% (SCREEN_WIDTH - BALL_WIDTH);
        PosY = rand()% (SCREEN_HEIGHT - BALL_HEIGHT);
    }
public:
    bool isWin ;
    bool isLose;
    const int BALL_WIDTH = 20;
    const int BALL_HEIGHT = 20;

    double speed;
    const int BALL_VEL = 10;
    int countPlay;

    Ball(/* args */){};
    Ball(const int SCREEN_WIDTH, const int SCREEN_HEIGHT);
    ~Ball();
    void handleEvent( SDL_Event& e );
    void move(const int SCREEN_WIDTH, const int SCREEN_HEIGHT, int& holeX, int& holeY);
    void render(renderTexture& ballTexture, SDL_Renderer*& gRenderer, renderTexture& gArrow);

    void resetBall(const int SCREEN_WIDTH, const int SCREEN_HEIGHT);
    bool ballInHole(int& holeX, int& holeY);
};

