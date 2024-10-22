#pragma once

class Scene;

class SceneMgr : public Singleton<SceneMgr>
{
	friend class Singleton<SceneMgr>;
	
protected:
	std::vector<Scene*> scenes;

	SceneIds startScene = SceneIds::Dev1;
	SceneIds currentScene;

	SceneMgr() = default;
	virtual ~SceneMgr() = default;

	SceneMgr(const SceneMgr&) = delete;
	SceneMgr& operator=(const SceneMgr&) = delete;

public:
	void Init();
	void RElease();

	SceneIds GetCurrentScene() const { return currentScene; }
	void ChangeScene(SceneIds id);

	void Update(float dt);
	void Draw(sf::RenderWindow& window);
};

