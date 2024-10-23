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
}

void TextGo::setPosition(const sf::Vector2f& iPos)
{
	position = iPos;
	setOrigin(originPreset);
	txtText.setPosition(iPos);
}

void TextGo::reset()
{
	auto& fontResMgr = ResourceMgr<sf::Font>::Instance();
	txtText.setFont(fontResMgr.get(strFontId));
	if (originPreset != Origins::Custom)
	{
		setOrigin(originPreset);
	}
}

void TextGo::draw(sf::RenderWindow& window)
{
	GameObject::draw(window);
	window.draw(txtText);
}

void TextGo::setString(const std::string& newText)
{
	txtText.setString(newText);

}
