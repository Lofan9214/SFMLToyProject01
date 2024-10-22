#include "stdafx.h"
#include "TextGo.h"

TextGo::TextGo(const std::string& iFontId, const std::string& iName)
	:strFontId(iFontId), GameObject(iName)
{
}

void TextGo::SetOrigin(Origins iPreset)
{
	originPreset = iPreset;
	origin = Utilities::setOrigin(sftxtText,iPreset);
}

void TextGo::SetOrigin(const sf::Vector2f& iOrigin)
{
}

void TextGo::SetPosition(const sf::Vector2f& iPos)
{
}

void TextGo::Reset()
{
}

void TextGo::setString(const std::string& newText)
{
}
