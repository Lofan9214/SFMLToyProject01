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
	float spd = difficulty * 150 +1500 + Utilities::randFloat(-20.f, 20.f);
	float aspectratio = 1.f;
		//(float)Framework::Instance().getWindow().getSize().x / Framework::Instance().getWindow().getSize().y;
	Velocity.x = spd * cosf(angle)* aspectratio;
	Velocity.y = spd * sinf(angle);
	position = playerpos;
	active = true;
}

int BulletGo::hit()
{
	active = false;
	position.x = -1000;
	position.y = -1000;
	sprite.setPosition(position);
	return 0;
}
