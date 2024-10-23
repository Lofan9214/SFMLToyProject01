#include "stdafx.h"
#include "PlayerGo.h"

PlayerGo::PlayerGo(std::string playerid, std::string name)
	: SpriteGo(playerid, name)
{
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
	}
}

void PlayerGo::draw(sf::RenderWindow& window)
{
	SpriteGo::draw(window);
}
