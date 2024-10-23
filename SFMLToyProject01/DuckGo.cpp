#include "stdafx.h"
#include "DuckGo.h"

DuckGo::DuckGo(std::string texId, std::string name)
	:SpriteGo(texId, name)
{
}

bool DuckGo::isAlive() const
{
	return bAlive;
}

void DuckGo::init()
{
	spawn();
}

void DuckGo::update(float dt)
{
	position += velocity * dt;

	if (position.x < (-200) || position.x>(Framework::Instance().getWindow().getSize().x + 200)
		|| position.y < (-200) || position.y>(Framework::Instance().getWindow().getSize().y + 200))
	{
		spawn(true);
	}
	SpriteGo::update(dt);
}

void DuckGo::draw(sf::RenderWindow& window)
{
	SpriteGo::draw(window);
}

void DuckGo::reset()
{
	SpriteGo::reset();
	active = true;
	spawn();
}

void DuckGo::release()
{
	SpriteGo::release();
}

void DuckGo::spawn(bool respawn)
{
	score = 10;
	active = true;
	bAlive = true;
	float angle;
	float speed = Utilities::randFloat(400.f, 600.f);
	if (Utilities::randInt(0, 1) == 1)
	{
		angle = Utilities::randFloat(-Utilities::pi * 0.03f, Utilities::pi * 0.03f);
		position.x = -100;
	}
	else
	{
		angle = Utilities::randFloat(Utilities::pi * 0.97f, Utilities::pi * 1.03f);
		position.x = 1920 + 100;
	}
	if (!respawn)
	{
		position.x = Utilities::randInt(100, 1800);
	}
	position.y = Utilities::randInt(100, 400);
	velocity.x = speed * cosf(angle);
	velocity.y = speed * sinf(angle);
}

int DuckGo::hit()
{
	active = false;
	bAlive = false;
	position.x = -1000.f;
	sprite.setPosition(position);
	return score;
}
