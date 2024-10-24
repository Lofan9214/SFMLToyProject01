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
	wing += dt;
	flytime += dt;

	if ((int)pattern > 1)
	{
		displacement.y = displacementAmplitude * sinf(displacementPeriod * flytime);
	}
	if ((int)pattern > 2)
	{
		displacement.x = displacementAmplitude * cosf(displacementPeriod * flytime);
	}
	if (pattern == movingPattern::totalyrandom)
	{
		displacement.x += displacementAmplitude * sinf(displacementPeriod) * dt;
		displacement.y += displacementAmplitude * cosf(displacementPeriod) * dt;
	}


	if (wing > 0.5)
	{
		sf::IntRect intrec = sprite.getTextureRect();
		if (bAlive)
		{
			if (intrec.left > 0)
			{
				intrec.left = 0;
			}
			else
			{
				intrec.left += intrec.width;
			}
			if (pattern == movingPattern::totalyrandom)
			{
				displacementAmplitude = Utilities::randFloat(100.f, 200.f);
				displacementPeriod = Utilities::randFloat(0.f, 2.f * Utilities::pi);
			}
		}
		else
		{
			active = false;
			intrec.top = 0;
			position.x = -1000.f;
		}
		sprite.setTextureRect(intrec);
		wing = 0;
	}

	if ((position.x < (-200) || position.x>(Framework::Instance().getWindow().getSize().x + 200)
		|| position.y < (-200) || position.y>(Framework::Instance().getWindow().getSize().y + 200))
		&& bAlive)
	{
		spawn(true);
	}

	sprite.setPosition(position + displacement);
	//SpriteGo::update(dt);
}

void DuckGo::draw(sf::RenderWindow& window)
{
	SpriteGo::draw(window);
}

void DuckGo::reset()
{
	SpriteGo::reset();
	sf::IntRect frame = sf::IntRect(0, 0, 140, 95);
	sprite.setTextureRect(frame);
	active = true;
	wing = Utilities::randFloat(0.f, 0.5f);

	spawn();
}

void DuckGo::release()
{
	SpriteGo::release();
}

void DuckGo::spawn(bool respawn)
{
	score = 0;
	flytime = 0.f;
	float speed;
	active = true;
	bAlive = true;
	displacementAmplitude = Utilities::randFloat(100.f, 200.f);
	displacementPeriod = Utilities::randFloat(1.5f, 4.f);
	displacement = { 0,0 };
	pattern = (movingPattern)Utilities::randInt(0, 3);

	wing = Utilities::randFloat(0.f, 0.5f);
	if (Utilities::randInt(0, 100) > 95 - difficulty)
	{
		score = 20;
		speed = difficulty * 100 + Utilities::randFloat(1100.f, 1300.f);
		sprite.setColor(sf::Color(255, 255, 100, 255));
	}
	else
	{
		score = 10;
		speed = difficulty * 100 + Utilities::randFloat(600.f, 800.f);
		sprite.setColor(sf::Color::White);
	}
	float angle;
	if (Utilities::randInt(0, 1) == 1)
	{
		angle = Utilities::randFloat(-Utilities::pi * 0.03f, Utilities::pi * 0.03f);
		position.x = -200;
		sprite.setScale(-0.8f, 0.8f);
	}
	else
	{
		angle = Utilities::randFloat(Utilities::pi * 0.97f, Utilities::pi * 1.03f);
		position.x = 1920 + 200;
		sprite.setScale(0.8f, 0.8f);
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
	bAlive = false;
	wing = 0;
	sf::IntRect intrec = sprite.getTextureRect();
	intrec.top += intrec.height;
	intrec.left = 0;
	sprite.setTextureRect(intrec);
	velocity.x = 0;
	velocity.y = 300;


	return score;
}
