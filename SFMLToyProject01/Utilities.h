#pragma once
class Utilities
{
public:
#pragma region ������ ����
	static sf::Vector2f setOrigin(sf::Sprite& obj, Origins preset);
	static sf::Vector2f setOrigin(sf::Text& obj, Origins preset);
#pragma endregion ������ ����

#pragma region �浹 üũ
	static int calcCollide(std::list<GameObject*> listGo);

#pragma endregion �浹 üũ

};