#pragma once
class DuckGo 
	: public SpriteGo
{
protected:
	enum class movingPattern
	{
		straight,
	};
	int score;
	movingPattern pattern;
	sf::Vector2f velocity;

	bool bAlive = true;

	DuckGo(const DuckGo&) = delete;
	DuckGo& operator=(const DuckGo&) = delete;

public:
	DuckGo() = default;
	virtual ~DuckGo() = default;
	DuckGo(std::string texId, std::string name);

	bool isAlive() const;

	void init() override;
	void reset() override;
	void release() override;
	void update(float dt) override;
	void draw(sf::RenderWindow& window) override;

	void spawn(bool respawn = false);
	int hit();
};

