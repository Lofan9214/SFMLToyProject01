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

void GameObject::Init()
{
}

void GameObject::Release()
{
}

void GameObject::reset()
{
}

void GameObject::Update(float dt)
{
}

void GameObject::draw(sf::RenderWindow& window)
{
}
