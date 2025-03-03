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
  bool attackBurpableActorAt(int x, int y);
  int getBurps();
  void attackPlayer();
  void incBurps();
  void setBurps(int num);
  void decBurps();
  void freezePlayer();
  void addActor(Actor* newActor);
  int distanceToPlayerSquared(Actor* actor);
  void setLevelFinished();
  bool hasBarrelBurnerAt(int x, int y);
  
private:
	Actor* getPlayer();
	void setDisplayText();
	std::string generate_stats(int score, int level, int lives, int burps);
	Level* lev;
	std::vector <Actor*> actors;
	int burps;
	bool finished;
};

#endif // STUDENTWORLD_H_
