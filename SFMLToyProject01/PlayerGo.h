#pragma once
class PlayerGo
{
protected:
	sf::Sprite gun;
	std::string guntextureid;
	std::string bullettexturid;
	//std::vector<BulletGo> bullets;

public:
	PlayerGo();
	virtual ~PlayerGo() = default;
	PlayerGo(std::string playerid, std::string gunid, std::string name);

	void init() override;
	void reset() override;
	void update(float dt) override;
	void draw(sf::RenderWindow& window) override;

};

