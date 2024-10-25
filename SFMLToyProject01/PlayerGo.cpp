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

void PlayerGo::playGunsound(std::string soundId)
{
	gunsound.setBuffer(ResourceMgr<sf::SoundBuffer>::Instance().get(soundId));
	gunsound.play();
}

void PlayerGo::setfireClick(bool fC)
{
	fireClick = fC;
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
	playerspeed = 0;
	SpriteGo::reset();
	sf::IntRect tmp;
	tmp.left = 0;
	tmp.width = sprite.getTexture()->getSize().x /2;
	tmp.top= 0;
	tmp.height = sprite.getTexture()->getSize().y;
	sprite.setTextureRect(tmp);

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
		if (sprite.getPosition().x >= Framework::Instance().getWindow().getSize().x - sprite.getLocalBounds().width / 2
			|| sprite.getPosition().x <= 0.f + sprite.getLocalBounds().width / 2)
		{
			playerspeed = 0;
		}
		else
		{
			pos2.x += playerspeed * dt;
		}
		sprite.setPosition(pos2);

		sf::IntRect intrec = sprite.getTextureRect();
		if (fireClick == true)
		{
			intrec.left = intrec.width;
		}
		else
		{
			intrec.left = 0;
		}
		sprite.setTextureRect(intrec);

	}

}

void PlayerGo::draw(sf::RenderWindow& window)
{
	SpriteGo::draw(window);
}
