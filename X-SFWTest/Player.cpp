#include "Player.h"

#include "sfwdraw.h"

Player::Player()
{
	position = { 0,0 };
}


Player::~Player()
{
}

void Player::draw()
{
	sfw::drawCircle(position.x, position.y, 10, 12, WHITE);
}

void Player::update()
{
	velocity = velocity + acceleration * sfw::getDeltaTime();
	position += velocity * sfw::getDeltaTime();
}
