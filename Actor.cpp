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

bool Actor::isClimbable() {
	return false;
}

bool Actor::attemptMoveTo(int x, int y) {
	if (!getWorld()->hasFloor(x, y)) {
		moveTo(x, y);
		return true;
	}
	return false;
}

bool Actor::gravity() {
	int gX, gY;
	getPositionInThisDirection(down, 1, gX, gY);
	if (getWorld()->hasClimbable(getX(), getY()) || getWorld()->hasFloor(gX, gY) || getWorld()->hasClimbable(gX, gY)) {
		return false;
	}
	moveTo(gX, gY);
	return true;
}

bool Actor::attack() {
	return false;
}

bool Actor::isPlayer() {
	return false;
}

void Actor::getAttacked() {
	return;
}

//PLAYER IMPLEMENTATION
Player::Player(int x, int y, StudentWorld* home) : Actor(IID_PLAYER, x, y, right, home) {
	//construct
	jump_state = 0;
}

void Player::doSomething()
{
	if (!isAlive()) {
		return;
	}

	if (jump_state > 0) {
		jump();
		return;
	}
	if (gravity())
		return;
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
		case KEY_PRESS_UP:
			if (getWorld()->hasClimbable(getX(), getY()))
				attemptMoveTo(getX(), getY() + 1);
			break;
		case KEY_PRESS_DOWN:
			attemptMoveTo(getX(), getY() - 1);
			break;
		case KEY_PRESS_SPACE:
			//... initiate jump ... 
			jump_state = 0;
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
		case -1:
			return;
			break;
		case 0:
			getPositionInThisDirection(up, 1, newX, newY);
			if (!attemptMoveTo(newX, newY) || getWorld()->hasClimbable(newX, newY)) {
				jump_state = -1;
				return;
			}
			jump_state++;
			break;
		case 1:
		case 2:
		case 3:
			getPositionInThisDirection(getDirection(), 1, newX, newY);
			if (!attemptMoveTo(newX, newY) || getWorld()->hasClimbable(newX, newY)) {
				jump_state = -1;
				return;
			}
			jump_state++;
			break;
		case 4:
			getPositionInThisDirection(down, 1, newX, newY);
			if (getWorld()->hasClimbable(newX, newY - 1) || !attemptMoveTo(newX, newY) || getWorld()->hasClimbable(newX, newY)) {
				jump_state = -1;
				return;
			}
			break;
		default:
			break;

	}

}

bool Player::isPlayer() {
	return true;
}

void Player::getAttacked() {
	getWorld()->playSound(SOUND_PLAYER_DIE);
	getWorld()->decLives();
	setDead();

}

//STATIONARY IMPLEMENTATION
Stationary::Stationary(int id, int x, int y, StudentWorld* home) : Actor(id, x, y, none, home) {
	
}

bool Stationary::isBarrier() {
	return false;
}

bool Stationary::isClimbable() {
	return false;
}

void Stationary::doSomething() {
	return;
}

//FLOOR IMPLEMENTATION
Floor::Floor(int x, int y, StudentWorld* home) : Stationary(IID_FLOOR, x, y, home) {

}

bool Floor::isBarrier() {
	return true;
}

//LADDER IMPLEMENTATION
Ladder::Ladder(int x, int y, StudentWorld* home) : Stationary(IID_LADDER, x, y, home) {

}

bool Ladder::isClimbable() {
	return true;
}

//BONFIRE IMPLEMENTATION
Bonfire::Bonfire(int x, int y, StudentWorld* home) : Stationary(IID_BONFIRE, x, y, home) {

}

void Bonfire::doSomething() {
	increaseAnimationNumber();
	attack();
}

bool Bonfire::attack() {
	if (getX() == getWorld()->getPlayer()->getX() && getY() == getWorld()->getPlayer()->getY()) {
		getWorld()->getPlayer()->getAttacked();
		return true;
	}
	else
		return false;
}


//GOODIE IMPLEMENTATION
Goodie::Goodie(int id, int x, int y, StudentWorld* home) : Actor(id, x, y, none, home) {

}
void Goodie::doSomething() {
	if (getWorld()->getPlayer()->getX() == getX() && getWorld()->getPlayer()->getY() == getY()) {
		getPickedUp();
	}
	if (isAlive())
		return;
}
void Goodie::getPickedUp() {
	return;
}

//EXTRA LIFE GOODIE IMPLEMENTATION
ExtraLifeGoodie::ExtraLifeGoodie(int x, int y, StudentWorld* home) : Goodie(IID_EXTRA_LIFE_GOODIE, x, y, home) {

}

void ExtraLifeGoodie::getPickedUp() {
	getWorld()->increaseScore(50);
	setDead();
	getWorld()->playSound(SOUND_GOT_GOODIE);
	getWorld()->incLives();
}

//GARLIC GOODIE IMPLEMENTATION
GarlicGoodie::GarlicGoodie(int x, int y, StudentWorld* home) : Goodie(IID_GARLIC_GOODIE, x, y, home) {

}

void GarlicGoodie::getPickedUp() {
	getWorld()->increaseScore(25);
	setDead();
	getWorld()->playSound(SOUND_GOT_GOODIE);
	for (int i = 0; i < 5; i++) {
		getWorld()->incBurps();
	}
}