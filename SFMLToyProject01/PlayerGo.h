#pragma once
class PlayerGo : public SpriteGo
{
protected:
public:
	PlayerGo() = default;
	virtual ~PlayerGo() = default;
	PlayerGo(std::string playerid, std::string name);

	sf::Vector2f getMuzzlePos() const;

	void init() override;
	void reset() override;
	void update(float dt) override;
	void draw(sf::RenderWindow& window) override;

};

