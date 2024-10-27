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

	if (position.x <  -100
		|| position.x > Framework::Instance().getWindow().getSize().x + 100
		|| position.y <  -100
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
	sprite.setScale(0.5f, 0.5f);
}

void BulletGo::fire(sf::RenderWindow& window, const sf::Vector2f& playerpos)
{
	auto mousepos = InputMgr::getMousePosition(window);
	float angle = atan2f(mousepos.y - playerpos.y, mousepos.x - playerpos.x) + Utilities::randFloat(-Utilities::pi * 0.01f, Utilities::pi * 0.01f);
	float spd = difficulty * 150 + 1500 + Utilities::randFloat(-40.f, 40.f);
	Velocity.x = -spd / tanf(angle);
	Velocity.y = -spd;
	position = playerpos;
	active = true;
}

int BulletGo::checkHit(std::list<DuckGo*> aliveDuck)
{
	int score = 0;
	for (auto itDuck : aliveDuck)
	{
		if (Utilities::isColliding(getRect(), itDuck->getRect()))
		{
			active = false;
			position.x = -1000;
			position.y = -1000;
			sprite.setPosition(position);

			score = itDuck->hit();
			itDuck->playSoundDuckDie("sound/chicken5.wav");
		}
		if (active == false)
		{
			break;
		}
	}
	return score;
}
