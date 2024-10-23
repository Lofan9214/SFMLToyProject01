#pragma once
class Scene
{
protected:
	const SceneIds id;
	std::list<GameObject*> gameObjects;

	Scene(const Scene&) = delete;
	Scene& operator=(const Scene&) = delete;
public:
	Scene(SceneIds id);
	virtual ~Scene() = default;


	virtual void init();
	virtual void Release();

	virtual void enter();
	virtual void exit();
	
	virtual void update(float dt);
	virtual void draw(sf::RenderWindow& window);
	
	virtual GameObject* AddGo(GameObject* obj);
	virtual void RemoveGo(GameObject* obj);
	virtual GameObject* FindGo(const std::string& name);
};

