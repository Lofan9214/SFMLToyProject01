#pragma once
#include "GameObject.h"

class Utilities
{
public:
#pragma region ������ ����
	static sf::Vector2f setOrigin(sf::Drawable& obj, Origins preset);
#pragma endregion ������ ����

#pragma region �浹 üũ
	static bool isColliding(const sf::FloatRect& bullet,const sf::FloatRect& duck);

#pragma endregion �浹 üũ

#pragma region ���� �Լ�
	static int randInt(int start, int end);
	static float randFloat(float start, float end);
#pragma endregion ���� �Լ�

#pragma region ���� ����
	static const float pi;
	static float rad2deg(const float rad);
	static float deg2rad(const float deg);
	static float absrad(const float rad);
#pragma endregion ���� ����
};