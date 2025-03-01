#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Level.h"
#include<vector>
#include <string>

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp
class Actor;
class StudentWorld : public GameWorld
{
public:
  StudentWorld(std::string assetPath);
  ~StudentWorld();
  virtual int init();
  virtual int move();
  virtual void cleanUp();
  bool playerIsHere(int x, int y);
  bool hasFloor(int x, int y);
  bool hasClimbable(int x, int y);
  bool attackActorAt(int x, int y);
  int getBurps();
  void attackPlayer();
  void incBurps();
  void decBurps();
  void freezePlayer();
  void addActor(Actor* newActor);
private:
	Actor* getPlayer();
	Level* lev;
	std::vector <Actor*> actors;
	int burps;
};

#endif // STUDENTWORLD_H_
