#pragma once
class SpriteGo : public GameObject
{
protected:
	sf::Sprite sprite;
	std::string textureId;

	SpriteGo(const SpriteGo&) = delete;
	SpriteGo& operator=(const SpriteGo&) = delete;
public:
	SpriteGo(const std::string& texId, const std::string& name = "");
	~SpriteGo() = default;


	void setOrigin(Origins preset);
	void setOrigin(const sf::Vector2f& newOrigin);
	
	
	void reset() override;
	void setPosition(const sf::Vector2f& pos) override;
	void draw(sf::RenderWindow& window) override;


};

