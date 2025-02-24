#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

class StudentWorld;

class Actor : public GraphObject {
public:
	Actor(int id, int x, int y, int dir, StudentWorld* home);
	virtual void doSomething();
	StudentWorld* getWorld();
	bool isAlive();
	void setDead();
	virtual bool isBarrier();
	virtual void attemptMoveTo(int x, int y);
private:
	StudentWorld* world;
	bool alive;
};

class Player : public Actor {
public:
	Player(int x, int y, StudentWorld* home);
	void doSomething();
private:
	void jump();
	int numBurps;
	int numLives;
	int jump_state;
};

class Floor : public Actor {
public:
	Floor(int x, int y, StudentWorld* home);
	bool isBarrier();
private:
};

#endif // ACTOR_H_
