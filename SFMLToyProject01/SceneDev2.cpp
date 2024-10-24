#include "stdafx.h"
#include "SceneDev2.h"
#include "SpriteGo.h"
#include "PlayerGo.h"
#include "BulletGo.h"
#include "DuckGo.h"
#include "TextGo.h"

SceneDev2::SceneDev2()
	: Scene(SceneIds::Dev2), gameOver(nullptr)
{
}

void SceneDev2::init()
{
	GameObject* obj;
	std::cout << "SceneDev2::Init()" << std::endl;

	AddGo(new SpriteGo("graphics/background2.png"));
	for (int i = 0; i < 15; ++i)
	{
		obj = AddGo(new BulletGo("graphics/Bullet.png", "bullet"));
		obj->setOrigin(Origins::MC);
	}
	AddGo(new PlayerGo("graphics/Player2.png", "player"));
	for (int i = 0; i < 7; ++i)
	{
		obj = AddGo(new DuckGo("graphics/duckAll.png", "duck"));
		obj->setOrigin(Origins::MC);
	}

	obj = AddGo(new TextGo("fonts/KOMIKAP_.ttf", "Scoreboard"));
	obj->setPosition({ 10.f, 10.f });

	obj = AddGo(new TextGo("fonts/KOMIKAP_.ttf", "GameOver"));
	obj->setActive(false);
	obj->setOrigin(Origins::MC);
	obj->setPosition({ Framework::Instance().getWindow().getSize().x * 0.5f,
		Framework::Instance().getWindow().getSize().y * 0.5f });
	gameOver = dynamic_cast<TextGo*>(obj);
	Scene::init();
}

void SceneDev2::enter()
{
	std::cout << "SceneDev2::Enter()" << std::endl;

	Framework::Instance().setTimeScale(1.0);
	time = 0.f;
	score = 0;
	reloadtime = 0;
	respawntime = 0.f;

	ResourceMgr<sf::Texture>::Instance().load("graphics/background2.png");
	ResourceMgr<sf::Texture>::Instance().load("graphics/Player2.png");
	for (std::list<GameObject*>::iterator it = gameObjects.begin(); it != gameObjects.end(); ++it)
	{
		auto ptr = dynamic_cast<PlayerGo*>(*it);
		if (ptr != nullptr)
		{
			ptr->setOrigin({ 100.f,300.f });
			ptr->setPosition({ 1920 / 2, 1080 });
		}
	}
	ResourceMgr<sf::Texture>::Instance().load("graphics/Bullet.png");
	ResourceMgr<sf::Texture>::Instance().load("graphics/duckAll.png");
	ResourceMgr<sf::Font>::Instance().load("fonts/KOMIKAP_.ttf");

	timebar.setFillColor(sf::Color::Red);
	timebar.setSize({ Framework::Instance().getWindow().getSize().x + 0.f , 10.f });

	if (gameOver != nullptr)
	{
		gameOver->setActive(false);
	}

	Scene::enter();
}

void SceneDev2::exit()
{
	std::cout << "SceneDev1::Enter()" << std::endl;

	Scene::exit();

	ResourceMgr<sf::Texture>::Instance().unload("graphics/background2.png");
	ResourceMgr<sf::Texture>::Instance().unload("graphics/Player2.png");
	ResourceMgr<sf::Texture>::Instance().unload("graphics/Bullet.png");
	ResourceMgr<sf::Texture>::Instance().unload("graphics/duckAll.png");
	ResourceMgr<sf::Font>::Instance().unload("fonts/KOMIKAP_.ttf");
}

void SceneDev2::update(float dt)
{
	if (InputMgr::isKeyDown(sf::Keyboard::Space)
		&& Framework::Instance().getTimeScale() == 0)
	{
		SceneMgr::Instance().changeScene(SceneIds::Dev1);
		return;
	}

	if (InputMgr::isKeyPressing(sf::Keyboard::D)
		&& Framework::Instance().getTimeScale() != 0)
	{
		for (std::list<GameObject*>::iterator it1 = gameObjects.begin(); it1 != gameObjects.end(); ++it1)
		{
			auto ptr1 = dynamic_cast<PlayerGo*> (*it1);
			if (ptr1 != nullptr && ptr1->isActive() == true)
			{
				ptr1->playerMove(400);
			}
		}
	}

	if (InputMgr::isKeyPressing(sf::Keyboard::A)
		&& Framework::Instance().getTimeScale() != 0)
	{
		for (std::list<GameObject*>::iterator it1 = gameObjects.begin(); it1 != gameObjects.end(); ++it1)
		{
			auto ptr1 = dynamic_cast<PlayerGo*> (*it1);
			if (ptr1 != nullptr && ptr1->isActive() == true)
			{
				ptr1->playerMove(-400);
			}
		}
	}

	if (InputMgr::isKeyUp(sf::Keyboard::D)
		&& Framework::Instance().getTimeScale() != 0)
	{
		for (std::list<GameObject*>::iterator it1 = gameObjects.begin(); it1 != gameObjects.end(); ++it1)
		{
			auto ptr1 = dynamic_cast<PlayerGo*> (*it1);
			if (ptr1 != nullptr && ptr1->isActive() == true)
			{
				ptr1->playerMove(0);
			}
		}
	}

	if (InputMgr::isKeyUp(sf::Keyboard::A)
		&& Framework::Instance().getTimeScale() != 0)
	{
		for (std::list<GameObject*>::iterator it1 = gameObjects.begin(); it1 != gameObjects.end(); ++it1)
		{
			auto ptr1 = dynamic_cast<PlayerGo*> (*it1);
			if (ptr1 != nullptr && ptr1->isActive() == true)
			{
				ptr1->playerMove(0);
			}
		}
	}

	

	respawntime += dt;
	reloadtime += dt;
	time += 192.0f * dt;
	if (respawntime > 5.f)
	{
		respawntime = 0.f;
		for (std::list<GameObject*>::iterator it2 = gameObjects.begin(); it2 != gameObjects.end(); ++it2)
		{
			auto ptr2 = dynamic_cast<DuckGo*> (*it2);
			if (ptr2 != nullptr && ptr2->isActive() == false)
			{
				ptr2->spawn(true);
			}
		}
	}

	if (InputMgr::isMouseButtonDown(sf::Mouse::Left))
	{
		PlayerGo* playptr = nullptr;
		std::vector<BulletGo*> vecBul;
		for (std::list<GameObject*>::iterator it = gameObjects.begin(); it != gameObjects.end(); ++it)
		{
			auto asplaptr = dynamic_cast<PlayerGo*>(*it);
			auto bulptr = dynamic_cast<BulletGo*> (*it);
			if (asplaptr != nullptr && asplaptr->isActive() == true)
			{
				playptr = asplaptr;
			}
			if (bulptr != nullptr && bulptr->isActive() == false)
			{
				vecBul.push_back(bulptr);
			}
		}
		if (playptr != nullptr && vecBul.size() > 2 && reloadtime > 0.5f)
		{
			reloadtime = 0.f;
			for (int i = 0;i < 3;++i)
			{
				vecBul[i]->fire(Framework::Instance().getWindow(), playptr->getMuzzlePos());
			}
		}
	}

#pragma region 面倒 眉农
	for (std::list<GameObject*>::iterator it = gameObjects.begin(); it != gameObjects.end(); ++it)
	{
		auto bulptr = dynamic_cast<BulletGo*>(*it);
		if (bulptr != nullptr && bulptr->isActive() == true)
		{
			for (std::list<GameObject*>::iterator it2 = gameObjects.begin(); it2 != gameObjects.end(); ++it2)
			{
				auto ducptr = dynamic_cast<DuckGo*> (*it2);
				if (ducptr != nullptr && ducptr->isAlive() == true)
				{
					if (Utilities::isColliding(bulptr->getRect(), ducptr->getRect()))
					{
						bulptr->hit();
						int upscore = ducptr->hit();
						score += upscore;
						time -= upscore * 20;
						if (time < 0)
						{
							time = 0;
						}
						break;
					}
				}
			}
		}
		auto txtptr = dynamic_cast<TextGo*>(*it);
		if (txtptr != nullptr && txtptr->getName() == "Scoreboard")
		{
			txtptr->setString("Score : " + std::to_string(score));
		}
	}
#pragma endregion 面倒 眉农


	if (score % 100 == 0)
	{
		for (std::list<GameObject*>::iterator it2 = gameObjects.begin(); it2 != gameObjects.end(); ++it2)
		{
			auto ducptr = dynamic_cast<DuckGo*> (*it2);
			if (ducptr != nullptr)
			{
				ducptr->setDifficulty(score / 100);
			}
		}
	}


	timebar.setSize({ Framework::Instance().getWindow().getSize().x - time, 10.f });
	if (Framework::Instance().getWindow().getSize().x < time)
	{
		if (gameOver != nullptr)
		{
			gameOver->setActive(true);
			gameOver->setString("Game Over! score: " + std::to_string(score) + "\npress Space to go Main screen");
		}
		Framework::Instance().setTimeScale(0.0);
	}
	Scene::update(dt);
}

void SceneDev2::draw(sf::RenderWindow& window)
{
	Scene::draw(window);
	window.draw(timebar);
}
