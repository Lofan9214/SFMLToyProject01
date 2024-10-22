#include "stdafx.h"

sf::Vector2f Utilities::setOrigin(sf::Drawable& obj, Origins preset)
{
	sf::Sprite* spritePtr = dynamic_cast<sf::Sprite*>(&obj);
	sf::Text* textPtr = dynamic_cast<sf::Text*>(&obj);
	sf::FloatRect fRect;
	sf::Vector2f v2fOrigin;

	if (spritePtr != nullptr)
	{
		fRect = spritePtr->getLocalBounds();
	}
	else if (textPtr != nullptr)
	{
		fRect = textPtr->getLocalBounds();
	}

	v2fOrigin.x = fRect.left + fRect.width * ((int)preset % 3) * 0.5f;
	v2fOrigin.y = fRect.top + fRect.height * ((int)preset / 3) * 0.5f;

	if (spritePtr != nullptr)
	{
		spritePtr->setOrigin(v2fOrigin);
	}
	else if (textPtr != nullptr)
	{
		textPtr->setOrigin(v2fOrigin);
	}

	return v2fOrigin;
}

//int Utilities::calcCollide(std::list<GameObject*>& listGo)
//{
//
//	return 0;
//}

