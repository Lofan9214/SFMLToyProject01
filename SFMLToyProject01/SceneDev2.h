#pragma once
#include "Scene.h"
#include "TextGo.h"
#include "PlayerGo.h"
#include "DuckGo.h"
#include "BulletGo.h"

class SceneDev2 : public Scene
{
protected:
    float respawntime = 0.f;
    int score = 0;
    float time = 0.f;
    sf::RectangleShape timebar;
    TextGo* gameOver;
    TextGo* textScore;
    PlayerGo* playerGo;
    SpriteGo* cloudGo;
    std::vector<DuckGo*> vecDuck;
    std::vector<DuckGo*> vecDuckAlive;
    std::vector<DuckGo*> vecDuckDead;
    std::vector<BulletGo*> vecBullet;
    std::vector<BulletGo*> vecBulletFired;
    std::vector<BulletGo*> vecBulletLoaded;

    float reloadtime = 0.f;

public:
    SceneDev2();
    ~SceneDev2() = default;

    void init() override;
    void enter() override;
    void exit() override;

    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;
};

