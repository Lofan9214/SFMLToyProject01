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

	const std::string& GetName() const { return name; }
	void SetName(const std::string& n) { name = n; }

	bool IsActive() const { return active; }
	void SetActive(bool a) { active = a; }

	sf::Vector2f GetPosition() const { return position; }
	virtual void setPosition(const sf::Vector2f& pos) { position = pos; }

	sf::Vector2f GetOrigin() const { return origin; }
	virtual void setOrigin(Origins preset);
	virtual void setOrigin(const sf::Vector2f& newOrigin)
	{
		origin = newOrigin;
		originPreset = Origins::Custom;
	}

	virtual void Init();
	virtual void Release();

	virtual void reset();

	virtual void Update(float dt);
	virtual void draw(sf::RenderWindow& window);
};

