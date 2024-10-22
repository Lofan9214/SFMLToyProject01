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

	GameObject* obj = AddGo(new SpriteGo("graphics/background.png"));
	obj->setOrigin(Origins::MC);
	obj->setPosition({ 1920 / 2, 1080 / 2 });
	Scene::init();
}

void SceneDev1::enter()
{
	std::cout << "SceneDev1::Enter()" << std::endl;

	ResourceMgr<sf::Text>::Instance().load("graphics/background.png");

	Scene::enter();
}

void SceneDev1::exit()
{
	std::cout << "SceneDev1::Enter()" << std::endl;

	Scene::exit();

	ResourceMgr<sf::Text>::Instance().load("graphics/background.png");

}

void SceneDev1::update(float dt)
{
	Scene::update(dt);

	if (InputMgr::isKeyDown(sf::Keyboard::Space))
	{
		SceneMgr::Instance().changeScene(SceneIds::Dev2);
	}
}

void SceneDev1::draw(sf::RenderWindow& window)
{
	Scene::draw(window);
}
