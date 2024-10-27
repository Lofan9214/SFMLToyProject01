#pragma once
#include "DuckGo.h"

class BulletGo : public SpriteGo
{
protected:
	sf::Vector2f Velocity;
	int difficulty = 0;

	BulletGo(const BulletGo&) = delete;
	BulletGo& operator=(const BulletGo&) = delete;

public:
	//BulletGo() = default;
	virtual ~BulletGo() = default;
	BulletGo(std::string texid, std::string name);

	void setDifficulty(int dif) { difficulty = dif; }

	void init() override;
	void update(float dt) override;
	void reset() override;
	void fire(sf::RenderWindow& window, const sf::Vector2f& playerpos);

	int checkHit(std::list<DuckGo*> aliveDuck);
};

