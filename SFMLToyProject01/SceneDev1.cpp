#include "stdafx.h"
#include "SceneDev1.h"
#include "SpriteGo.h"


SceneDev1::SceneDev1()
	: Scene(SceneIds::Dev1)
{
}

void SceneDev1::Init()
{
	std::cout << "SceneDev1::Init()" << std::endl;

	GameObject* obj = AddGo(new SpriteGo("graphics/background.png"));
	obj->SetOrigin(Origins::MC);
	obj->SetPosition({ 1920 / 2, 1080 / 2 });
	Scene::Init();
}

void SceneDev1::Enter()
{
	std::cout << "SceneDev1::Enter()" << std::endl;

	ResourceMgr<sf::Text>::Instance().Load("graphics/background.png");

	Scene::Enter();
}

void SceneDev1::Exit()
{
	std::cout << "SceneDev1::Enter()" << std::endl;

	Scene::Exit();

	ResourceMgr<sf::Text>::Instance().Load("graphics/background.png");

}

void SceneDev1::Update(float dt)
{
	Scene::Update(dt);

	if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		SceneMgr::Instance().ChangeScene(SceneIds::Dev2);
	}
}

void SceneDev1::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
