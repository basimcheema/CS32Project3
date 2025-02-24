#include "StudentWorld.h"
#include "GameConstants.h"
#include "Actor.h"
#include <string>
using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
    return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h, and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath)
{
}

int StudentWorld::init()
{
    lev = new Level(assetPath());
    Level::LoadResult result = lev->loadLevel("level00.txt");
    if (result == Level::load_fail_file_not_found)
        return GWSTATUS_PLAYER_WON;
    else if (result == Level::load_fail_bad_format)
        return GWSTATUS_LEVEL_ERROR;
    else if (result == Level::load_success)
    {
        cerr << "Successfully loaded level\n";
        Level::MazeEntry me;
        for (int y = 0; y < VIEW_HEIGHT; y++) {
            for (int x = 0; x < VIEW_WIDTH; x++) {
                me = lev->getContentsOf(x, y); // x=5, y=10
                switch (me)
                {
                case Level::floor:
                    cerr << x << "," << y << " is a Floor\n";
                    actors.push_back(new Floor(x, y, this));
                    break;
                case Level::ladder:
                    cerr << x << "," << y << " , 10 is a Ladder\n";
                    break;
                case Level::left_kong:
                    cerr << x << "," << y << " is a left - facing Kong\n";
                    break;
                case Level::right_kong:
                    cerr << x << "," << y << " is a right - facing Kong\n";
                    break;
                case Level::fireball:
                    cerr << x << "," << y << " is a Fireball\n";
                    break;
                case Level::koopa:
                    cerr << x << "," << y << " is a Koopa\n";
                    break;
                case Level::bonfire:
                    cerr << x << "," << y << " is a Bonfire\n";
                    break;
                case Level::extra_life:
                    cerr << x << "," << y << " is an Extra Life Goodie\n";
                    break;
                case Level::garlic:
                    cerr << x << "," << y << " is a Garlic Goodie\n";
                    break;
                case Level::player:
                    cerr << x << "," << y << " is where the Player starts\n";
                    actors.push_back(new Player(x, y, this));
                    break;
                case Level::empty:
                    cerr << x << "," << y << " is empty\n";
                    break;
                }
            }
        }
        return GWSTATUS_CONTINUE_GAME;
    }
}

int StudentWorld::move()
{
    // This code is here merely to allow the game to build, run, and terminate after you type q
    for (int i = 0; i < actors.size(); i++) {
        if (actors[i] != nullptr)
            actors[i]->doSomething();
    }
    setGameStatText("Game will end when you type q");
    
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
    for (int i = 0; i < actors.size(); i++) {
        if (actors[i] != nullptr) {
            delete actors[i];
            actors[i] = nullptr;
        }
    }
    delete lev;
    lev = nullptr;
    setGameStatText("Game will end when you type q");
}

StudentWorld::~StudentWorld() {
    cleanUp();
}

bool StudentWorld::hasFloor(int x, int y) {
    for (int i = 0; i < actors.size(); i++) {
        if (actors[i]->getX() == x && actors[i]->getY() == y && actors[i]->isBarrier()) {
            return true;
        }
    }
    return false;
}
