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
	auto wx = Framework::Instance().getWindow().getSize().x;
	auto wy = Framework::Instance().getWindow().getSize().y;

	if (position.x <  - 100
		|| position.x > Framework::Instance().getWindow().getSize().x + 100
		|| position.y <  - 100
		|| position.y > Framework::Instance().getWindow().getSize().y + 100)
	{
		Velocity.x = 0;
		Velocity.y = 0;
		active = false;
	}
	SpriteGo::update(dt);
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
	Velocity.x = 800 * cosf(angle);
	Velocity.y = 800 * sinf(angle);
	position = playerpos;
	active = true;
}

int BulletGo::hit()
{
	active = false;
	position.x = -1000;
	position.y = -1000;
	return 0;
}
