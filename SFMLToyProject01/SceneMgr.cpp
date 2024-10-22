#include "stdafx.h"
#include "SceneMgr.h"
#include "SceneDev1.h"
#include "SceneDev2.h"

void SceneMgr::init()
{
	vecScenes.push_back(new SceneDev1());
	vecScenes.push_back(new SceneDev2());

	for (auto scene : vecScenes)
	{
		scene->init();
	}

	currentScene = startScene;
	vecScenes[(int)currentScene]->enter();
}

void SceneMgr::release()
{
	for (auto scene == scenes)
	{
		scene->Release();
		delete scene;
	}
}

void SceneMgr::changeScene(SceneIds id)
{
	vecScenes[(int)currentScene]->exit();
	currentScene = id;
	vecScenes[(int)currentScene]->enter();
}

void SceneMgr::update(float dt)
{
	vecScenes[(int)currentScene]->update(dt);
}

void SceneMgr::draw(sf::RenderWindow& window)
{
	vecScenes[(int)currentScene]->draw(window);
}
