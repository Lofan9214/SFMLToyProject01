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

	PlayerGo* playerptr = nullptr;
	std::vector<DuckGo*> vecDuck;
	std::vector<BulletGo*> vecBullet;
	for (std::list<GameObject*>::iterator it = gameObjects.begin(); it != gameObjects.end(); ++it)
	{
		auto dyncastplayer = dynamic_cast<PlayerGo*> (*it);
		if (dyncastplayer != nullptr)
		{
			playerptr = dyncastplayer;
			continue;
		}
		auto dyncastDuck = dynamic_cast<DuckGo*> (*it);
		if (dyncastDuck != nullptr)
		{
			vecDuck.push_back(dyncastDuck);
			continue;
		}
		auto dyncastBullet = dynamic_cast<BulletGo*> (*it);
		if (dyncastBullet != nullptr)
		{
			vecBullet.push_back(dyncastBullet);
			continue;
		}
	}

	if (Framework::Instance().getTimeScale() != 0)
	{
		if (InputMgr::isKeyPressing(sf::Keyboard::D)
			&& playerptr != nullptr && playerptr->isActive() == true)
		{
			playerptr->playerMove(400);
		}
		if (InputMgr::isKeyPressing(sf::Keyboard::A)
			&& playerptr != nullptr && playerptr->isActive() == true)
		{
			playerptr->playerMove(-400);
		}
		if ((InputMgr::isKeyUp(sf::Keyboard::D) || InputMgr::isKeyUp(sf::Keyboard::A))
			&& playerptr != nullptr && playerptr->isActive() == true)
		{
			playerptr->playerMove(0);
		}
	}

	respawntime += dt;
	reloadtime += dt;
	time += 192.0f * dt;
	if (respawntime > 5.f)
	{
		respawntime = 0.f;
		for (auto itduck : vecDuck)
		{
			if (itduck->isActive() == false)
			{
				itduck->spawn(true);
			}
		}
	}

	if (InputMgr::isMouseButtonDown(sf::Mouse::Left))
	{
		if (playerptr != nullptr && vecBullet.size() > 2 && reloadtime > 0.5f)
		{
			std::vector<BulletGo*> remainBullet;
			for (auto itBullet : vecBullet)
			{
				if (itBullet->isActive()==false)
				{
					remainBullet.push_back(itBullet);
				}
			}
			if (remainBullet.size() > 2)
			{
				reloadtime = 0.f;
				for (int i = 0;i < 3;++i)
				{
					remainBullet[i]->fire(Framework::Instance().getWindow(), playerptr->getMuzzlePos());
				}
			}
		}
	}

#pragma region 面倒 眉农
	for (std::list<GameObject*>::iterator it = gameObjects.begin(); it != gameObjects.end(); ++it)
	{
		std::vector<BulletGo*> curBullet;
		std::vector<DuckGo*> liveDuck;
		for (auto itBullet : vecBullet)
		{
			if (itBullet->isActive()==true)
			{
				curBullet.push_back(itBullet);
			}
		}
		for (auto itDuck : vecDuck)
		{
			if (itDuck->isActive() == true)
			{
				liveDuck.push_back(itDuck);
			}
		}
		bool hit = false;
		for (auto itBullet : curBullet)
		{
			for (auto itDuck : liveDuck)
			{
				if (itDuck->isAlive() == false
					|| itBullet->isActive() == false)
				{
					break;
				}
				if (Utilities::isColliding(itBullet->getRect(), itDuck->getRect()))
				{
					itBullet->hit();
					int upscore = itDuck->hit();
					score += upscore;
					time -= upscore * 20;
					if (time < 0)
					{
						time = 0;
					}
					hit = true;
					break;
				}
			}
			if (hit)
			{
				break;
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
		for (auto itDuck : vecDuck)
		{
			itDuck->setDifficulty(score / 100);
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
