#pragma once
class BulletGo : public SpriteGo
{
protected:
	sf::Vector2f Velocity;
	float rotation=0.f;
	int difficulty=0;

public:
	BulletGo() = default;
	virtual ~BulletGo() = default;
	BulletGo(std::string texid, std::string name);

	void setDifficulty(int dif) { difficulty = dif; }

	void init() override;
	void update(float dt) override;
	void reset() override;
	void fire(sf::RenderWindow& window, const sf::Vector2f& playerpos);

	int hit();
};

