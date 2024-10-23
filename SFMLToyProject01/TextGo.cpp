#include "stdafx.h"
#include "TextGo.h"

TextGo::TextGo(const std::string& iFontId, const std::string& iName)
	:strFontId(iFontId), GameObject(iName)
{
}

void TextGo::setOrigin(Origins iPreset)
{
	originPreset = iPreset;
	origin = Utilities::setOrigin(sftxtText,iPreset);
}

void TextGo::setOrigin(const sf::Vector2f& iOrigin)
{
}

void TextGo::setPosition(const sf::Vector2f& iPos)
{
}

void TextGo::reset()
{
}

void TextGo::setString(const std::string& newText)
{
}
