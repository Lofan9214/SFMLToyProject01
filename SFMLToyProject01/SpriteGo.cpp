#include "stdafx.h"
#include "SpriteGo.h"

SpriteGo::SpriteGo(const std::string& texId, const std::string& name)
	: GameObject(name), textureId(texId)
{
}

void SpriteGo::setOrigin(Origins preset)
{
	originPreset = preset;
	origin = Utilities::setOrigin(sprite, originPreset);
}

void SpriteGo::setOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	sprite.setOrigin(origin);
}

void SpriteGo::setScale(const sf::Vector2f& scalevector)
{
	sprite.setScale(scalevector);
}

sf::FloatRect SpriteGo::getRect()
{
	return sprite.getGlobalBounds();
}

void SpriteGo::init()
{
	GameObject::init();
}

void SpriteGo::release()
{
	GameObject::release();
}

void SpriteGo::update(float dt)
{
	sprite.setPosition(position);
	GameObject::update(dt);
}

void SpriteGo::reset()
{
	sprite.setTexture(ResourceMgr<sf::Texture>::Instance().get(textureId));
	setOrigin(originPreset);
}

void SpriteGo::setPosition(const sf::Vector2f& pos)
{
	GameObject::setPosition(pos);
	sprite.setPosition(pos);
}

void SpriteGo::draw(sf::RenderWindow& window)
{
	GameObject::draw(window);
	window.draw(sprite);
}
