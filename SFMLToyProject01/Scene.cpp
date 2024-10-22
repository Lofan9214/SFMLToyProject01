#include "stdafx.h"
#include "Scene.h"

Scene::Scene(SceneIds id)
	:id(id)
{
}

void Scene::init()
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

void Scene::enter()
{
	for (auto obj : gameObjects)
	{
		obj->reset();
	}
}

void Scene::exit()
{
}

void Scene::update(float dt)
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

void Scene::draw(sf::RenderWindow& window)
{
	for (auto obj : gameObjects)
	{
		if (!obj->IsActive())
		{
			continue;
		}
		obj->draw(window);
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
