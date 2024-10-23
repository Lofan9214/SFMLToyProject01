#pragma once

class Scene;

class SceneMgr : public Singleton<SceneMgr>
{
	friend class Singleton<SceneMgr>;
	
protected:
	std::vector<Scene*> vecScenes;

	SceneIds startScene = SceneIds::Dev2;
	SceneIds currentScene;

	SceneMgr() = default;
	virtual ~SceneMgr() = default;

	SceneMgr(const SceneMgr&) = delete;
	SceneMgr& operator=(const SceneMgr&) = delete;

public:
	void init();
	void release();

	SceneIds getCurrentScene() const { return currentScene; }
	void changeScene(SceneIds id);

	void update(float dt);
	void draw(sf::RenderWindow& window);
};

