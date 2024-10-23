#include "stdafx.h"
#include "DuckGo.h"

DuckGo::DuckGo(std::string texId, std::string name)
	:SpriteGo(texId, name)
{
}

void DuckGo::init()
{
	fly();
	position.x = Utilities::randInt(100, 1800);
	position.y = Utilities::randInt(100, 400);
}

void DuckGo::update(float dt)
{
	position += velocity * dt;

	if (position.x < (-200) || position.x>(Framework::Instance().getWindow().getSize().x + 200)
		|| position.y < (-200) || position.y>(Framework::Instance().getWindow().getSize().y + 200))
	{
		fly();
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
	fly();
	position.x = Utilities::randInt(100, 1800);
	position.y = Utilities::randInt(100, 400);
}

void DuckGo::release()
{
	SpriteGo::release();
}

void DuckGo::fly()
{
	score = 10;
	active = true;
	float angle;
	float speed = Utilities::randFloat(200.f, 300.f);
	if (Utilities::randInt(0, 1) == 1)
	{
		angle = Utilities::randFloat(-Utilities::pi * 0.05f, Utilities::pi * 0.05f);
		position.x = -100;
	}
	else
	{
		angle = Utilities::randFloat(Utilities::pi * 0.95f, Utilities::pi * 1.05f);
		position.x = 1920 + 100;
	}
	position.y = Utilities::randInt(100, 400);
	velocity.x = speed * cosf(angle);
	velocity.y = speed * sinf(angle);
}

int DuckGo::hit()
{
	active = false;
	return score;
}
