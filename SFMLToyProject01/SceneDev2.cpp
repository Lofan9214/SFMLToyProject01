#include "stdafx.h"
#include "SceneDev2.h"
#include "SpriteGo.h"
#include "PlayerGo.h"
#include "BulletGo.h"
#include "DuckGo.h"
#include "TextGo.h"

SceneDev2::SceneDev2()
	: Scene(SceneIds::Dev2)
{
}

void SceneDev2::init()
{
	GameObject* obj;
	std::cout << "SceneDev2::Init()" << std::endl;

	AddGo(new SpriteGo("graphics/background.png"));
	for (int i = 0; i < 10; ++i)
	{
		obj = AddGo(new BulletGo("graphics/Bullet.png", "bullet"));
		obj->setOrigin(Origins::MC);
	}
	AddGo(new PlayerGo("graphics/Head.png", "player"));
	for (int i = 0; i < 10; ++i)
	{
		obj = AddGo(new DuckGo("graphics/duckAll.png", "duck"));
		obj->setOrigin(Origins::MC);
	}

	obj = AddGo(new TextGo("fonts/KOMIKAP_.ttf", "Scoreboard"));
	obj->setPosition({ 10.f, 10.f });

	Scene::init();
}

void SceneDev2::enter()
{
	std::cout << "SceneDev2::Enter()" << std::endl;

	ResourceMgr<sf::Texture>::Instance().load("graphics/background.png");
	ResourceMgr<sf::Texture>::Instance().load("graphics/Head.png");
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

	Scene::enter();
}

void SceneDev2::exit()
{
	std::cout << "SceneDev1::Enter()" << std::endl;

	Scene::exit();

	ResourceMgr<sf::Texture>::Instance().unload("graphics/background.png");
	ResourceMgr<sf::Texture>::Instance().unload("graphics/Head.png");
	ResourceMgr<sf::Texture>::Instance().unload("graphics/Bullet.png");
	ResourceMgr<sf::Texture>::Instance().unload("graphics/duckAll.png");
	ResourceMgr<sf::Font>::Instance().unload("fonts/KOMIKAP_.ttf");
}

void SceneDev2::update(float dt)
{
	respawntime += dt;

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

	if (InputMgr::isKeyDown(sf::Keyboard::Space))
	{
		SceneMgr::Instance().changeScene(SceneIds::Dev1);
	}
	if (InputMgr::isMouseButtonDown(sf::Mouse::Left))
	{
		for (std::list<GameObject*>::iterator it = gameObjects.begin(); it != gameObjects.end(); ++it)
		{
			auto ptr = dynamic_cast<BulletGo*>(*it);
			if (ptr != nullptr && ptr->isActive() == false)
			{

				ptr->fire(Framework::Instance().getWindow(), { 1920 / 2, 1080 });
				break;
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
						score += ducptr->hit();
						break;
					}
				}
			}
		}
		auto txtptr = dynamic_cast<TextGo*>(*it);
		if (txtptr != nullptr)
		{
			txtptr->setString("Score : "+std::to_string(score));
		}
	}

	
#pragma endregion 面倒 眉农

	Scene::update(dt);
}

void SceneDev2::draw(sf::RenderWindow& window)
{
	Scene::draw(window);
}
