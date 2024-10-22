#include "stdafx.h"
#include "BulletGo.h"

BulletGo::BulletGo(std::string texid, std::string name)
	: SpriteGo(texid, name)
{
}

void BulletGo::init()
{
}

void BulletGo::update(float dt)
{
	position += Velocity * dt;
}

void BulletGo::reset()
{
	SpriteGo::reset();
	active = false;
}

void BulletGo::fire(sf::RenderWindow& window, const sf::Vector2f& playerpos)
{
	auto mousepos = InputMgr::getMousePosition(window);
	float angle = atan2f(mousepos.y - playerpos.y, mousepos.x - playerpos.x);
	Velocity.x = 500 * cosf(angle);
	Velocity.y = 500 * sinf(angle);
	position = playerpos;
	active = true;
}
