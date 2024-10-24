#include "stdafx.h"
#include "SceneDev1.h"
#include "SpriteGo.h"


SceneDev1::SceneDev1()
	: Scene(SceneIds::Dev1)
{
}

void SceneDev1::init()
{
	std::cout << "SceneDev1::Init()" << std::endl;

	GameObject* obj = AddGo(new SpriteGo("graphics/background2.png"));
	obj->setOrigin(Origins::MC);
	obj->setPosition({ 1920 / 2, 1080 / 2 });
	Scene::init();
}

void SceneDev1::enter()
{
	std::cout << "SceneDev1::Enter()" << std::endl;

	ResourceMgr<sf::Texture>::Instance().load("graphics/background2.png");

	Scene::enter();
}

void SceneDev1::exit()
{
	std::cout << "SceneDev1::Enter()" << std::endl;

	Scene::exit();

	ResourceMgr<sf::Texture>::Instance().unload("graphics/background2.png");

}

void SceneDev1::update(float dt)
{
	Scene::update(dt);

	if (InputMgr::isMouseButtonDown(sf::Mouse::Left))
	{
		SceneMgr::Instance().changeScene(SceneIds::Dev2);
	}

	//acttime += dt;
	//if (acttime > 5.f)
	//{
	//	acttime = 0.f;
	//	for (std::list<GameObject*>::iterator it = gameObjects.begin(); it != gameObjects.end(); ++it)
	//	{
	//		auto ptr2 = dynamic_cast<SpriteGo*> (*it);
	//		if (ptr2 != nullptr && ptr2->getName() == "graphics/title.png")
	//		{
	//
	//		}
	//	}
	//}
	
}

void SceneDev1::draw(sf::RenderWindow& window)
{
	Scene::draw(window);
}
