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
}

void PlayerGo::draw(sf::RenderWindow& window)
{
	SpriteGo::draw(window);
}
