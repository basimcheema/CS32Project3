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

void Actor::getFrozen() {

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

	if (freeze_state > 0) {
		freeze_state--;
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

void Player::getFrozen() {
	freeze_state = 50;
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
	if (getWorld()->playerIsHere(getX(), getY())) {
		getWorld()->attackPlayer();
		return true;
	}
	return false;
}


//GOODIE IMPLEMENTATION
Goodie::Goodie(int id, int x, int y, StudentWorld* home) : Actor(id, x, y, none, home) {

}
void Goodie::doSomething() {
	if (getWorld()->playerIsHere(getX(), getY())) {
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

//ENEMY IMPLEMENTATION
Enemy::Enemy(int id, int x, int y, int dir, StudentWorld* home) : Actor(id, x, y, dir, home) {
	tick_num = 0;
}

int Enemy::getTick() {
	return tick_num;
}

void Enemy::setTick(int num) {
	tick_num = num;
}

void Enemy::incTick() {
	tick_num++;
}

void Enemy::changeDir() {
	if (getDirection() == right) {
		setDirection(left);
	}
	else if (getDirection() == left) {
		setDirection(right);
	}
}

void Enemy::getAttacked() {

}

//KOOPA IMPLEMENTATION
Koopa::Koopa(int x, int y, StudentWorld* home) : Enemy(IID_KOOPA, x, y, randInt(1, 2) % 2 ? right : left, home) {
	freeze_timer = 0;
}

void Koopa::doSomething() {
	incTick();
	if (!isAlive())
		return;
	if (getWorld()->playerIsHere(getX(), getY()) && freeze_timer == 0) {
		freeze_timer = 50;
		attack();
	}
	if (freeze_timer > 0) {
		freeze_timer--;
	}
	if (getTick() == 10) {
		move();
		setTick(0);
	}
}

bool Koopa::attack() {
	getWorld()->freezePlayer();
	return true;
}

void Koopa::move() {
	int nextX, nextY;
	getPositionInThisDirection(getDirection(), 1, nextX, nextY);
	if (getWorld()->hasClimbable(getDirection() == right ? getX() + 1 : getX() - 1, getY() - 1) || getWorld()->hasFloor(getDirection() == right ? getX() + 1 : getX() - 1, getY() - 1)) {
		moveTo(nextX, nextY);
	}
	else {
		changeDir();
		return;
	}
}

void Koopa::getAttacked() {
	setDead();
	getWorld()->playSound(SOUND_ENEMY_DIE);
	getWorld()->increaseScore(100);
	if (randInt(1, 3) == 1)
		getWorld()->addActor(new ExtraLifeGoodie(getX(), getY(), getWorld()));
}
