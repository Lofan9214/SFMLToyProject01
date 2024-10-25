#include "stdafx.h"
#include "SceneDev1.h"
#include "SpriteGo.h"
#include "TextGo.h"


SceneDev1::SceneDev1()
	: Scene(SceneIds::Dev1)
{
}

void SceneDev1::init()
{
	std::cout << "SceneDev1::Init()" << std::endl;

	GameObject* obj = AddGo(new SpriteGo("graphics/underbackground.png"));
		
	obj = AddGo(new SpriteGo("graphics/background2.png"));
	obj->setOrigin(Origins::BL);
	obj->setPosition({ 0, 1080});

	obj = AddGo(new SpriteGo("graphics/Title.png", "title"));
	obj->setOrigin(Origins::MC);
	obj->setPosition({ 1920 / 2, 1080 / 3 -100.f });
	Scene::init();

	obj = AddGo(new TextGo("fonts/KOMIKAP_.ttf", "startclick"));
	obj->setOrigin(Origins::MC);
	obj->setPosition({ 1920 / 2, 1080 / 2 + 350.f });
}

void SceneDev1::enter()
{
	std::cout << "SceneDev1::Enter()" << std::endl;

	ResourceMgr<sf::Texture>::Instance().load("graphics/underbackground.png");
	ResourceMgr<sf::Texture>::Instance().load("graphics/background2.png");
	ResourceMgr<sf::Texture>::Instance().load("graphics/Title.png");
	ResourceMgr<sf::Font>::Instance().load("fonts/KOMIKAP_.ttf");

	Scene::enter();
}

void SceneDev1::exit()
{
	std::cout << "SceneDev1::Enter()" << std::endl;

	Scene::exit();

	ResourceMgr<sf::Texture>::Instance().unload("graphics/underbackground.png");
	ResourceMgr<sf::Texture>::Instance().unload("graphics/background2.png");
	ResourceMgr<sf::Texture>::Instance().unload("graphics/Title.png");
	ResourceMgr<sf::Font>::Instance().unload("fonts/KOMIKAP_.ttf");

}

void SceneDev1::update(float dt)
{
	if (InputMgr::isMouseButtonDown(sf::Mouse::Left))
	{
		SceneMgr::Instance().changeScene(SceneIds::Dev2);
		return;
	}

	Scene::update(dt);

	float min;
	float diff;
	
	for (std::list<GameObject*>::iterator it = gameObjects.begin(); it != gameObjects.end(); ++it)
	{
		auto ptr2 = dynamic_cast<SpriteGo*> (*it);
		if (ptr2 != nullptr && ptr2->getName() == "title")
		{
			min = 1.2f;
			diff = 0.3f;

			ptr2->setScale({ min + diff * sinf(5.0f*Framework::Instance().getRealTime()), min + diff * sinf(5.0f * Framework::Instance().getRealTime()) });
		}
	}
	for (std::list<GameObject*>::iterator it = gameObjects.begin(); it != gameObjects.end(); ++it)
	{
		auto txtptr = dynamic_cast<TextGo*>(*it);
		if (txtptr != nullptr && txtptr->getName() == "startclick")
		{
			txtptr->setString("Press Click");
		}
	}
	
}

void SceneDev1::draw(sf::RenderWindow& window)
{
	Scene::draw(window);
}
