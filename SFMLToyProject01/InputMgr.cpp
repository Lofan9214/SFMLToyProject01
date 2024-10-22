#include "stdafx.h"

std::vector<std::bitset<3>> InputMgr::vecInput(sf::Keyboard::KeyCount + sf::Mouse::ButtonCount, 0);

void InputMgr::clear()
{
	for (auto& it : vecInput)
	{
		it[(int)State::Down] = false;
		it[(int)State::Release] = false;
	}
}

void InputMgr::updateEvent(const sf::Event& ev)
{
	int idx = 0;
	bool bLastPressing = false;

	switch (ev.type)
	{
	case sf::Event::KeyPressed:
		if (ev.key.code < 0)
		{
			return;
		}
		idx = ev.key.code;
		if (!vecInput[idx][(int)State::Pressing])
		{
			vecInput[idx][(int)State::Down] = true;
		}
		vecInput[idx][(int)State::Pressing] = true;
		break;
	case sf::Event::KeyReleased:
		if (ev.key.code < 0)
		{
			return;
		}
		idx = ev.key.code;
		vecInput[idx][(int)State::Pressing] = false;
		vecInput[idx][(int)State::Release] = true;
		break;
	case sf::Event::MouseButtonPressed:
		idx = sf::Keyboard::KeyCount + ev.mouseButton.button;
		if (!vecInput[idx][(int)State::Pressing])
		{
			vecInput[idx][(int)State::Down] = true;
		}
		vecInput[idx][(int)State::Pressing] = true;
		break;
	case sf::Event::MouseButtonReleased:
		idx = sf::Keyboard::KeyCount + ev.mouseButton.button;
		vecInput[idx][(int)State::Pressing] = false;
		vecInput[idx][(int)State::Release] = true;
		break;
	}
}

bool InputMgr::isKeyDown(const sf::Keyboard::Key& key)
{
	return vecInput[key][(int)State::Down];
}

bool InputMgr::isKeyPressing(const sf::Keyboard::Key& key)
{
	return vecInput[key][(int)State::Pressing];
}

bool InputMgr::isKeyUp(const sf::Keyboard::Key& key)
{
	return vecInput[key][(int)State::Release];
}

bool InputMgr::isMouseButtonDown(const sf::Mouse::Button& btn)
{
	return vecInput[sf::Keyboard::KeyCount + btn][(int)State::Down];
}

bool InputMgr::isMouseButtonPressing(const sf::Mouse::Button& btn)
{
	return vecInput[sf::Keyboard::KeyCount + btn][(int)State::Pressing];
}

bool InputMgr::isMouseButtonUp(const sf::Mouse::Button& btn)
{
	return vecInput[sf::Keyboard::KeyCount + btn][(int)State::Release];
}

sf::Vector2i InputMgr::getMousePosition(sf::RenderWindow& window)
{
	return sf::Mouse::getPosition(window);
}
