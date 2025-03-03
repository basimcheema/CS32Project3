#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

class StudentWorld;

class Actor : public GraphObject {
public:
	Actor(int id, int x, int y, int dir, StudentWorld* home);
	virtual void doSomething() = 0;
	virtual void getFrozen();
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
	virtual bool isBarrelBurner();
	virtual bool isBurpable();
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
	void getFrozen();
private:
	void jump();
	int jump_state;
	int freeze_state;
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
	bool isBarrelBurner();
private:
};



class Goodie : public Actor {
public:
	Goodie(int id, int x, int y, StudentWorld* home);
	virtual void doSomething();
	virtual void getPickedUp() = 0;
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
	Enemy(int id, int x, int y, int dir, StudentWorld* home);
	virtual void doSomething() = 0;
	virtual bool attack() = 0;
	virtual void getAttacked() = 0;
	virtual bool isBurpable();
	int getTick();
	void setTick(int num);
	void incTick();
	void changeDir();
private:
	int tick_num;
};

class Koopa : public Enemy {
public:
	Koopa(int x, int y, StudentWorld* home);
	void doSomething();
	bool attack();
	void getAttacked();
private:
	void move();
	int freeze_timer;
};

class Fireball : public Enemy {
public:
	Fireball(int x, int y, StudentWorld* home);
	void doSomething();
	bool attack();
	void getAttacked();
private:
	void move();
	int climb_state;

};

class Barrel : public Enemy {
public:
	Barrel(int x, int y, int dir, StudentWorld* home);
	void doSomething();
	void getAttacked();
	bool attack();
private:

};


class Burp : public Actor {
public:
	Burp(int x, int y, int dir, StudentWorld* home);
	void doSomething();
private:
	int ticks;
};


class Kong : public Actor {
public:
	Kong(int x, int y, int dir, StudentWorld* home);
	void doSomething();
private:
	bool flee_state;
	int flee_ticks;
	int barrel_ticks;
};
#endif // ACTOR_H_
