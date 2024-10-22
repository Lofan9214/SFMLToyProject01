#include "stdafx.h"
#include "SceneDev2.h"
#include "SpriteGo.h"

SceneDev2::SceneDev2()
	: Scene(SceneIds::Dev2)
{
}

void SceneDev2::Init()
{
	std::cout << "SceneDev2::Init()" << std::endl;

	AddGo(new SpriteGo("graphics/player.png"));

	Scene::Init();
}

void SceneDev2::Enter()
{
	std::cout << "SceneDev2::Enter()" << std::endl;
	
	ResourceMgr<sf::Text>::Instance().Load("graphics/player.png");

	Scene::Enter();
}

void SceneDev2::Exit()
{
	std::cout << "SceneDev1::Enter()" << std::endl;

	Scene::Exit();

	ResourceMgr<sf::Text>::Instance().Load("graphics/background.png");
}

void SceneDev2::Update(float dt)
{
	Scene::Update(dt);

	if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		SceneMgr::Instance().ChangeScene(SceneIds::Dev2);
	}
}

void SceneDev2::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
