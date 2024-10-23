#pragma once
class TextGo
	: public GameObject
{
protected:
	sf::Text txtText;
	std::string strFontId;

	TextGo(const TextGo&) = delete;
	TextGo& operator=(const TextGo&) = delete;

public:

	TextGo() = default;
	virtual ~TextGo() = default;

	TextGo(const std::string& iFontId, const std::string& iName = "");

	void setOrigin(Origins iPreset) override;
	void setOrigin(const sf::Vector2f& iOrigin) override;

	void setPosition(const sf::Vector2f& iPos) override;

	void reset() override;
	void draw(sf::RenderWindow& window) override;

	void setString(const std::string& newText);
};

