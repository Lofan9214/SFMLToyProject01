#include "stdafx.h"

const float Utilities::pi = acosf(-1);

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

int Utilities::calcCollide(const sf::FloatRect& bullet, const sf::FloatRect& duck)
{
	if (bullet.left > (duck.left + duck.width)
		|| bullet.left + bullet.width < duck.left
		|| bullet.top < (duck.top + duck.height)
		|| (bullet.top + bullet.height) > duck.top)
	{
		std::cout << "Ãæµ¹!!" << std::endl;
		return true;
	}
	return false;

	return bullet.intersects(duck);
}

int Utilities::randInt(int start, int end)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(start, end);

	return dis(gen);
}

float Utilities::randFloat(float start, float end)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dis(start, end);

	return dis(gen);
}

float Utilities::rad2deg(const float rad)
{
	return rad * 180 / pi;
}

float Utilities::deg2rad(const float deg)
{
	return deg * pi / 180;
}

float Utilities::absrad(const float rad)
{
	float newrad = rad;
	while (newrad < 0.f)
	{
		newrad += 2 * pi;
	}
	return newrad;
}

