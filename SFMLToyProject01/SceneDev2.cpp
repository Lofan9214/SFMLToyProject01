#include "stdafx.h"
#include "SceneDev2.h"
#include "SpriteGo.h"
#include "PlayerGo.h"
#include "BulletGo.h"
#include "DuckGo.h"

SceneDev2::SceneDev2()
	: Scene(SceneIds::Dev2)
{
}

void SceneDev2::init()
{
	std::cout << "SceneDev2::Init()" << std::endl;

	AddGo(new SpriteGo("graphics/background.png"));
	AddGo(new PlayerGo("graphics/Head.png", "player"));
	for (int i = 0; i < 10; ++i)
	{
		AddGo(new BulletGo("graphics/Bullet.png", "bullet"));
	}
	for (int i = 0; i < 1; ++i)
	{
		AddGo(new DuckGo("graphics/duck.png", "duck"));
	}
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
			ptr->setPosition({ 1920 / 2, 1080 /2 });
		}
	}
	ResourceMgr<sf::Texture>::Instance().load("graphics/Bullet.png");
	ResourceMgr<sf::Texture>::Instance().load("graphics/duck.png");

	Scene::enter();
}

void SceneDev2::exit()
{
	std::cout << "SceneDev1::Enter()" << std::endl;

	Scene::exit();

	ResourceMgr<sf::Texture>::Instance().unload("graphics/background.png");
	ResourceMgr<sf::Texture>::Instance().unload("graphics/Head.png");
	ResourceMgr<sf::Texture>::Instance().unload("graphics/Bullet.png");
	ResourceMgr<sf::Texture>::Instance().unload("graphics/duck.png");
}

void SceneDev2::update(float dt)
{
	Scene::update(dt);

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
	for (std::list<GameObject*>::iterator it = gameObjects.begin(); it != gameObjects.end(); ++it)
	{
		auto ptr = dynamic_cast<BulletGo*>(*it);
		if (ptr != nullptr && ptr->isActive() == true)
		{
			for (std::list<GameObject*>::iterator it2 = gameObjects.begin(); it2 != gameObjects.end(); ++it2)
			{
				auto ptr2 = dynamic_cast<DuckGo*> (*it2);
				if (ptr2 != nullptr && ptr2->isActive() == true)
				{
					if (Utilities::calcCollide(ptr->getRect(), ptr2->getRect()))
					{
						ptr2->hit();
					}
				}

			}
		}
	}


}

void SceneDev2::draw(sf::RenderWindow& window)
{
	Scene::draw(window);
}
