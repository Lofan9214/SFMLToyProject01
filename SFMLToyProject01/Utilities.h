#pragma once
class Utilities
{
public:
#pragma region 오리진 관련
	static sf::Vector2f setOrigin(sf::Sprite& obj, Origins preset);
	static sf::Vector2f setOrigin(sf::Text& obj, Origins preset);
#pragma endregion 오리진 관련

#pragma region 충돌 체크
	static int calcCollide(std::list<GameObject*> listGo);

#pragma endregion 충돌 체크

};