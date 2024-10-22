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
		obj->init();
	}
}

void Scene::Release()
{
	for (auto obj : gameObjects)
	{
		obj->release();
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
		if (!obj->isActive())
		{
			continue;
		}
		obj->update(dt);
	}
}

void Scene::draw(sf::RenderWindow& window)
{
	for (auto obj : gameObjects)
	{
		if (!obj->isActive())
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
		if (obj->getName() == name)
		{
			return obj;
		}
	}
	return nullptr;
}
