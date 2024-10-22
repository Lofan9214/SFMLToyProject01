#include "stdafx.h"
#include "PlayerGo.h"

PlayerGo::PlayerGo(std::string playerid, std::string gunid, std::string bulletid, std::string name)
	: GameObject(name), guntextureid(gunid) 
{
}

void PlayerGo::init()
{
}

void PlayerGo::reset()
{
}

void PlayerGo::update(float dt)
{
}

void PlayerGo::draw(sf::RenderWindow& window)
{
}
