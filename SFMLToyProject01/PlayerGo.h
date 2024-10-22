#pragma once
class PlayerGo : public GameObject
{
protected:
	sf::Sprite gun;
	std::string guntextureid;
	std::string bullettexturid;
	//std::vector<BulletGo> bullets;

public:
	PlayerGo() = default;
	virtual ~PlayerGo() = default;
	PlayerGo(std::string playerid, std::string gunid, std::string bulletid, std::string name);

	void init() override;
	void reset() override;
	void update(float dt) override;
	void draw(sf::RenderWindow& window) override;

};

