#include "stdafx.h"
#include "TextGo.h"

TextGo::TextGo(const std::string& iFontId, const std::string& iName)
	:strFontId(iFontId), GameObject(iName)
{
}

void TextGo::setOrigin(Origins iPreset)
{
	originPreset = iPreset;
	origin = Utilities::setOrigin(txtText,iPreset);
}

void TextGo::setOrigin(const sf::Vector2f& iOrigin)
{
	originPreset = Origins::Custom;
	origin = iOrigin;
	txtText.setOrigin(iOrigin);
}

void TextGo::setPosition(const sf::Vector2f& iPos)
{
	position = iPos;
	setOrigin(originPreset);
	txtText.setPosition(iPos);
}

void TextGo::init()
{
	GameObject::init();
}

void TextGo::release()
{
	GameObject::release();
}

void TextGo::reset()
{
	txtText.setFont(ResourceMgr<sf::Font>::Instance().get(strFontId));
	txtText.setCharacterSize(50);
	
	if (originPreset != Origins::Custom)
	{
		setOrigin(originPreset);
	}
}

void TextGo::update(float dt)
{
	GameObject::update(dt);
}

void TextGo::draw(sf::RenderWindow& window)
{
	GameObject::draw(window);
	window.draw(txtText);
}

void TextGo::setString(const std::string& newText)
{
	txtText.setString(newText);
	if (originPreset != Origins::Custom)
	{
		setOrigin(originPreset);
	}
}
