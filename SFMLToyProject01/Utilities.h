#pragma once
#include "GameObject.h"

class Utilities
{
public:
#pragma region 오리진 관련
	static sf::Vector2f setOrigin(sf::Drawable& obj, Origins preset);
#pragma endregion 오리진 관련

#pragma region 충돌 체크
	static bool isColliding(const sf::FloatRect& bullet,const sf::FloatRect& duck);

#pragma endregion 충돌 체크

#pragma region 랜덤 함수
	static int randInt(int start, int end);
	static float randFloat(float start, float end);
#pragma endregion 랜덤 함수

#pragma region 각도 관련
	static const float pi;
	static float rad2deg(const float rad);
	static float deg2rad(const float deg);
	static float absrad(const float rad);
#pragma endregion 각도 관련
};