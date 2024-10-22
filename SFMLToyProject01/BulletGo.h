#pragma once
class BulletGo : public SpriteGo
{
protected:
	sf::Vector2f Velocity;
	float rotation;

public:
	BulletGo() = default;
	virtual ~BulletGo() = default;
	BulletGo(std::string texid, std::string name);



	void init() override;
	void update(float dt) override;
	void reset() override;
	void fire(sf::RenderWindow& window, const sf::Vector2f& playerpos);
};

