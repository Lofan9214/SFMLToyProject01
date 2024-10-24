#include "stdafx.h"
#include "PlayerGo.h"

PlayerGo::PlayerGo(std::string playerid, std::string name)
	: SpriteGo(playerid, name)
{
}

sf::Vector2f PlayerGo::getMuzzlePos() const
{
	sf::Vector2f pos = sprite.getPosition();
	float rot = Utilities::deg2rad(sprite.getRotation() - 90.f);
	float play = sprite.getOrigin().y;

	pos.x += play * cosf(rot);
	pos.y += play * sinf(rot);

	return pos;
}

float PlayerGo::playerMove(float speed)
{
	playerspeed = speed;
	return playerspeed;
}

void PlayerGo::init()
{
}

void PlayerGo::reset()
{
	SpriteGo::reset();
}

void PlayerGo::update(float dt)
{
	if (dt != 0)
	{

		auto mousepos = InputMgr::getMousePosition(Framework::Instance().getWindow());
		float radi = atan2f(mousepos.y - position.y, mousepos.x - position.x);
		float degr = Utilities::rad2deg(radi) + 90;

		sprite.setRotation(degr);

		sf::Vector2f pos2 = sprite.getPosition();
		pos2.x += playerspeed * dt;
		sprite.setPosition(pos2);
		if (sprite.getPosition().x >= Framework::Instance().getWindow().getSize().x
			|| sprite.getPosition().x <= 0.f)
		{
			pos2.x -= playerspeed * dt;
			playerspeed = 0;
			sprite.setPosition(pos2);
		}
	}

}

void PlayerGo::draw(sf::RenderWindow& window)
{
	SpriteGo::draw(window);
}
