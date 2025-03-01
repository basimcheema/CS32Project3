#include "StudentWorld.h"
#include "GameConstants.h"
#include "Actor.h"
#include <string>
//changes
using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
    return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h, and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath)
{
    burps = 0;
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
                    actors.push_back(new Ladder(x, y, this));
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
                    actors.push_back(new Koopa(x, y, this));
                    break;
                case Level::bonfire:
                    cerr << x << "," << y << " is a Bonfire\n";
                    actors.push_back(new Bonfire(x, y, this));
                    break;
                case Level::extra_life:
                    cerr << x << "," << y << " is an Extra Life Goodie\n";
                    actors.push_back(new ExtraLifeGoodie(x, y, this));
                    break;
                case Level::garlic:
                    cerr << x << "," << y << " is a Garlic Goodie\n";
                    actors.push_back(new GarlicGoodie(x, y, this));
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
    if (!getPlayer()->isAlive()) {
        return GWSTATUS_PLAYER_DIED;
    }
    // This code is here merely to allow the game to build, run, and terminate after you type q
    for (int i = 0; i < actors.size(); i++) {
        if (actors[i] != nullptr)
            actors[i]->doSomething();
    }

    if (getPlayer()->isAlive()) {
        for (int i = 0; i < actors.size(); i++) {
            if (!actors[i]->isAlive()) {
                delete actors[i];
                actors[i] = nullptr;
                actors.erase(actors.begin() + i);
            }
        }
    }
    setGameStatText("helpppp");
    
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

    actors.clear();
    
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

bool StudentWorld::hasClimbable(int x, int y) {
    for (int i = 0; i < actors.size(); i++) {
        if (actors[i]->getX() == x && actors[i]->getY() == y && actors[i]->isClimbable()) {
            return true;
        }
    }
    return false;
}

Actor* StudentWorld::getPlayer() {
    for (int i = 0; i < actors.size(); i++) {
        if (actors[i]->isPlayer()) {
            return actors[i];
        }
    }
    return nullptr;
}

int StudentWorld::getBurps() {
    return burps;
}

void StudentWorld::incBurps() {
    burps++;
}

void StudentWorld::decBurps() {
    burps--;
}

bool StudentWorld::attackActorAt(int x, int y) {
    for (int i = 0; i < actors.size(); i++) {
        if (actors[i]->getX() == x && actors[i]->getY() == y) {
            actors[i]->getAttacked();
            return true;
        }
    }
    return false;
}

void StudentWorld::attackPlayer() {
    getPlayer()->getAttacked();
}

bool StudentWorld::playerIsHere(int x, int y) {
    return getPlayer()->getX() == x && getPlayer()->getY() == y;
}

void StudentWorld::freezePlayer() {
    getPlayer()->getFrozen();
}

void StudentWorld::addActor(Actor* newActor) {
    actors.push_back(newActor);
}