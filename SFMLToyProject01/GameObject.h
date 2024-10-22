#pragma once
class GameObject
{
protected:
	std::string name;

	bool active = true;

	sf::Vector2f position;
	Origins originPreset;
	sf::Vector2f origin;
public:
	GameObject(const std::string& name = "");
	virtual ~GameObject() = default;

	const std::string& getName() const { return name; }
	void setName(const std::string& n) { name = n; }

	bool isActive() const { return active; }
	void setActive(bool a) { active = a; }

	sf::Vector2f getPosition() const { return position; }
	virtual void setPosition(const sf::Vector2f& pos) { position = pos; }

	sf::Vector2f getOrigin() const { return origin; }
	virtual void setOrigin(Origins preset);
	virtual void setOrigin(const sf::Vector2f& newOrigin)
	{
		origin = newOrigin;
		originPreset = Origins::Custom;
	}

	virtual void init();
	virtual void release();

	virtual void reset();

	virtual void update(float dt);
	virtual void draw(sf::RenderWindow& window);
};

