#include "stdafx.h"
#include "Scene.h"

Scene::Scene(SceneIds id)
	:id(id)
{
}

void Scene::Init()
{
	for (auto obj : gameObjects)
	{
		obj->Init();
	}
}

void Scene::Release()
{
	for (auto obj : gameObjects)
	{
		obj->Release();
		delete obj;
	}
	gameObjects.clear();
}

void Scene::Enter()
{
	for (auto obj : gameObjects)
	{
		obj->Reset();
	}
}

void Scene::Exit()
{
}

void Scene::Update(float dt)
{
	for (auto obj : gameObjects)
	{
		if (!obj->IsActive())
		{
			continue;
		}
		obj->Update(dt);
	}
}

void Scene::Draw(sf::RenderWindow& window)
{
	for (auto obj : gameObjects)
	{
		if (!obj->IsActive())
		{
			continue;
		}
		obj->Draw(window);
	}
}

GameObject* Scene::AddGo(GameObject* obj)
{
	if (std::find(gameObjects.begin(), gameObjects.end(), obj) == gameObjects.end())
	{
		gameObjects.push_back(obj);
	}
	return obj;
}

void Scene::RemoveGo(GameObject* obj)
{
	gameObjects.remove(obj);
}

GameObject* Scene::FindGo(const std::string& name)
{
	for (auto obj : gameObjects)
	{
		if (obj->GetName() == name)
		{
			return obj;
		}
	}
	return nullptr;
}
