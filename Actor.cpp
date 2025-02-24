#include "Actor.h"
#include "GameConstants.h"
#include "StudentWorld.h"
 
// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

//ACTOR IMPLEMENTATION
Actor::Actor(int id, int x, int y, int dir, StudentWorld* home) : GraphObject(id, x, y, dir) {
	 //construct
	alive = true;
	world = home;
}

void Actor::doSomething() {
	//doSomething
	return;
}

StudentWorld* Actor::getWorld() {
	return world;
}

bool Actor::isAlive() {
	return alive;
}

void Actor::setDead() {
	alive = false;
}

bool Actor::isBarrier() {
	return false;
}

void Actor::attemptMoveTo(int x, int y) {
	if (!getWorld()->hasFloor(x, y))
		moveTo(x, y);
}

//PLAYER IMPLEMENTATION
Player::Player(int x, int y, StudentWorld* home) : Actor(IID_PLAYER, x, y, right, home) {
	//construct
	numBurps = 0;
	numLives = 3;
	jump_state = 0;
}

void Player::doSomething()
{
	if (jump_state != 0) {
		jump();
		return;
	}
	int ch;
	if (getWorld()->getKey(ch))
	{
		// user hit a key this tick!
		switch (ch)
		{
		case KEY_PRESS_LEFT:
			//... turn or move left ...
			if (getDirection() == right)
				setDirection(left);
			else
				attemptMoveTo(getX() - 1, getY());
			break;
		case KEY_PRESS_RIGHT:
			//... turn or move right ...
			if (getDirection() == left)
				setDirection(right);
			else
				attemptMoveTo(getX() + 1, getY());
			break;
		case KEY_PRESS_SPACE:
			//... initiate jump ... 
			jump();
			break;
		case KEY_PRESS_TAB:
			//burp if you have burps left ...
			break;
		}
	}
	
}

void Player::jump() {
	int newX, newY;
	switch (jump_state) {
		case 0:
			getPositionInThisDirection(up, 1, newX, newY);
			attemptMoveTo(newX, newY);
			jump_state++;
			break;
		case 1:
		case 2:
		case 3:
			getPositionInThisDirection(getDirection(), 1, newX, newY);
			attemptMoveTo(newX, newY);
			jump_state++;
			break;
		case 4:
			getPositionInThisDirection(down, 1, newX, newY);
			attemptMoveTo(newX, newY);
			jump_state = 0;
			break;
		default:
			break;

	}
}


//FLOOR IMPLEMENTATION
Floor::Floor(int x, int y, StudentWorld* home) : Actor(IID_FLOOR, x, y, none, home) {

}

bool Floor::isBarrier() {
	return true;
}

