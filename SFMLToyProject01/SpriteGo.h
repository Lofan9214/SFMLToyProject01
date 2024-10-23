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

	void setPosition(const sf::Vector2f& pos) override;
	void setOrigin(Origins preset) override;
	void setOrigin(const sf::Vector2f& newOrigin) override;
	

	sf::FloatRect getRect();

	void init() override;
	void release() override;
	void update(float dt) override;
	void reset() override;
	void draw(sf::RenderWindow& window) override;


};

