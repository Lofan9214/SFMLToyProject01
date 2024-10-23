#pragma once
class Framework : public Singleton<Framework>
{
	friend Singleton<Framework>;

protected:

	Framework() = default;
	virtual ~Framework() = default;

	Framework(const Framework&) = delete;
	Framework& operator=(const Framework&) = delete;

	sf::RenderWindow window;

	sf::Clock clkClock;
	float fTimeScale = 1.f;

	float fGameTime = 0.f;
	float fGameDeltaTime = 0.f;
	float fRealTime = 0.f;
	float fRealDeltaTime = 0.f;

public:

	float getGameTime() const { return fGameTime; }
	float getGameDeltaTime() const { return fGameDeltaTime; }
	float getRealTime() const { return fRealTime; }
	float getRealDeltaTime() const { return fRealDeltaTime; }

	void setTimeScale(float newTimeScale) { fTimeScale = newTimeScale; }
	float getTimeScale() const { return fTimeScale; }

	sf::RenderWindow& getWindow() { return window; }

	virtual void init(int width, int height, const std::string& name);
	virtual void doThis();
	virtual void release();
};

