#include "stdafx.h"
#include "SceneDev2.h"
#include "SpriteGo.h"

SceneDev2::SceneDev2()
	: Scene(SceneIds::Dev2)
{
}

void SceneDev2::init()
{
	std::cout << "SceneDev2::Init()" << std::endl;

	AddGo(new SpriteGo("graphics/player.png"));

	Scene::init();
}

void SceneDev2::enter()
{
	std::cout << "SceneDev2::Enter()" << std::endl;
	
	ResourceMgr<sf::Texture>::Instance().load("graphics/player.png");

	Scene::enter();
}

void SceneDev2::exit()
{
	std::cout << "SceneDev1::Enter()" << std::endl;

	Scene::exit();

	ResourceMgr<sf::Texture>::Instance().unload("graphics/background.png");
}

void SceneDev2::update(float dt)
{
	Scene::update(dt);

	if (InputMgr::isKeyDown(sf::Keyboard::Space))
	{
		SceneMgr::Instance().changeScene(SceneIds::Dev1);
	}
}

void SceneDev2::draw(sf::RenderWindow& window)
{
	Scene::draw(window);
}
