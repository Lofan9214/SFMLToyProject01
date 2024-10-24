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
	for (int i = 0; i < 30; ++i)
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

	ResourceMgr<sf::Texture>::Instance().load("graphics/background2.png");
	ResourceMgr<sf::Texture>::Instance().load("graphics/Player2.png");
	for (std::list<GameObject*>::iterator it = gameObjects.begin(); it != gameObjects.end(); ++it)
	{
		auto ptr = dynamic_cast<PlayerGo*>(*it);
		if (ptr != nullptr)
		{
			ptr->setOrigin(Origins::BC);
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
	respawntime += dt;
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
		for (std::list<GameObject*>::iterator it = gameObjects.begin(); it != gameObjects.end(); ++it)
		{
			auto plaptr = dynamic_cast<PlayerGo*>(*it);
			if (plaptr != nullptr && plaptr->isActive() == true)
			{
				int bulcount = 0;
				for (std::list<GameObject*>::iterator it2 = gameObjects.begin(); it2 != gameObjects.end(); ++it2)
				{
					auto bulptr = dynamic_cast<BulletGo*> (*it2);
					if (bulptr != nullptr && bulptr->isActive() == false)
					{
						bulptr->fire(Framework::Instance().getWindow(), plaptr->getMuzzlePos());
						if (++bulcount > 2)
						{
							break;
						}
					}
				}
				break;
			}
		}
	}

#pragma region 충돌 체크
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
						time -= upscore * 15;
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




#pragma endregion 충돌 체크
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


	if (InputMgr::isKeyDown(sf::Keyboard::Space)
		&& Framework::Instance().getTimeScale() == 0)
	{
		SceneMgr::Instance().changeScene(SceneIds::Dev1);
	}
}

void SceneDev2::draw(sf::RenderWindow& window)
{
	Scene::draw(window);
	window.draw(timebar);
}
