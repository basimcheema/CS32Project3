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
	virtual bool attemptMoveTo(int x, int y);
	virtual bool isBarrier();
	virtual bool isClimbable();
	virtual bool gravity();
	virtual bool attack();
	virtual bool isPlayer();
	virtual void getAttacked();
private:
	StudentWorld* world;
	bool alive;
};


class Player : public Actor {
public:
	Player(int x, int y, StudentWorld* home);
	void doSomething();
	bool isPlayer();
	void getAttacked();
private:
	void jump();
	int jump_state;
};

class Stationary : public Actor {
public:
	Stationary(int id, int x, int y, StudentWorld* home);
	virtual void doSomething();
	virtual bool isBarrier();
	virtual bool isClimbable();
private:


};

class Floor : public Stationary {
public:
	Floor(int x, int y, StudentWorld* home);
	bool isBarrier();
private:
};

class Ladder : public Stationary {
public:
	Ladder(int x, int y, StudentWorld* home);
	bool isClimbable();
private:
};

class Bonfire : public Stationary {
public:
	Bonfire(int x, int y, StudentWorld* home);
	void doSomething();
	bool attack();
private:
};



class Goodie : public Actor {
public:
	Goodie(int id, int x, int y, StudentWorld* home);
	virtual void doSomething();
	virtual void getPickedUp();
private:

};

class ExtraLifeGoodie : public Goodie {
public:
	ExtraLifeGoodie(int x, int y, StudentWorld* home);
	void getPickedUp();
private:
};

class GarlicGoodie : public Goodie {
public:
	GarlicGoodie(int x, int y, StudentWorld* home);
	void getPickedUp();
private:
};



class Enemy : public Actor {
public:
	Enemy(int id, int x, int y, StudentWorld* home);
	virtual void getAttacked();
	virtual bool attack();
private:
};
#endif // ACTOR_H_
