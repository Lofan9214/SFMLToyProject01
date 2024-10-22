#include "stdafx.h"

GameObject::GameObject(const std::string& name)
	: name(name)
{
}

void GameObject::setOrigin(Origins preset)
{
	originPreset = preset;
	origin = { 0.f, 0.f };
}

void GameObject::init()
{
}

void GameObject::release()
{
}

void GameObject::reset()
{
}

void GameObject::update(float dt)
{
}

void GameObject::draw(sf::RenderWindow& window)
{
}
