#include "stdafx.h"
#include "SceneDev2.h"
#include "SpriteGo.h"
#include "PlayerGo.h"
#include "BulletGo.h"

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

	Scene::enter();
}

void SceneDev2::exit()
{
	std::cout << "SceneDev1::Enter()" << std::endl;

	Scene::exit();

	ResourceMgr<sf::Texture>::Instance().unload("graphics/background.png");
	ResourceMgr<sf::Texture>::Instance().unload("graphics/Head.png");
	ResourceMgr<sf::Texture>::Instance().unload("graphics/Bullet.png");
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
}

void SceneDev2::draw(sf::RenderWindow& window)
{
	Scene::draw(window);
}
