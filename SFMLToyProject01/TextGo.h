#pragma once
class TextGo
	: public GameObject
{
protected:
	sf::Text sftxtText;
	std::string strFontId;

	TextGo(const TextGo&) = delete;
	TextGo& operator=(const TextGo&) = delete;

public:

	TextGo() = default;
	virtual ~TextGo() = default;

	TextGo(const std::string& iFontId, const std::string& iName = "");

	void SetOrigin(Origins iPreset) override;
	void SetOrigin(const sf::Vector2f& iOrigin) override;

	void SetPosition(const sf::Vector2f& iPos) override;

	void Reset() override;

	void setString(const std::string& newText);
};

