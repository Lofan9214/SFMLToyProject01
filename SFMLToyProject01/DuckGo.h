#pragma once
class DuckGo
	: public SpriteGo
{
protected:
	enum class movingPattern
	{
		straight,
		totalyrandom,
		wave,
		circlic,
	};
	
	int score = 0;
	int difficulty = 0;
	movingPattern pattern;
	sf::Vector2f velocity;
	sf::Vector2f displacement;

	float wing = 0.f;
	float flytime = 0.f;
	float displacementAmplitude = 0.f;
	float displacementPeriod = 0.f;

	float scalex = 0.f;
	float scaley = 0.f;
	float scaleDispAmplitude = 0.f;
	float scaleDispPeriod = 0.f;

	bool bAlive = true;
	
	sf::Sound diesound;

	DuckGo(const DuckGo&) = delete;
	DuckGo& operator=(const DuckGo&) = delete;

public:
	DuckGo() = default;
	virtual ~DuckGo() = default;
	DuckGo(std::string texId, std::string name);

	bool isAlive() const;

	void playSoundDuckDie(std::string duckdie);

	void init() override;
	void reset() override;
	void release() override;
	void update(float dt) override;
	void draw(sf::RenderWindow& window) override;

	void spawn(bool respawn = false);

	void setDifficulty(int dDif) { difficulty = dDif; }
	int hit();
};

