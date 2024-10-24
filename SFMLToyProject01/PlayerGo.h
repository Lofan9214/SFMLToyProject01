#pragma once
class PlayerGo : public SpriteGo
{
protected:
	float playerspeed = 0.f;
	sf::Sound gunsound;
public:
	PlayerGo() = default;
	virtual ~PlayerGo() = default;
	PlayerGo(std::string playerid, std::string name);

	sf::Vector2f getMuzzlePos() const;
	void playGunsound(std::string soundId);

	float playerMove(float speed);

	void init() override;
	void reset() override;
	void update(float dt) override;
	void draw(sf::RenderWindow& window) override;

};

