#pragma once
#include "Scene.h"
#include "TextGo.h"
#include "PlayerGo.h"
#include "DuckMgr.h"
#include "BulletMgr.h"

class SceneDev2 : public Scene
{
protected:
    int score = 0;
    float time = 0.f;
    sf::RectangleShape timebar;
    TextGo* gameOver;
    TextGo* textScore;
    PlayerGo* playerGo;
    SpriteGo* cloudGo;
    SpriteGo* groundGo;

    DuckMgr duckMgr;
    BulletMgr bulletMgr;

    std::vector<DuckGo*> vecDuck;
    std::vector<BulletGo*> vecBullet;

public:
    SceneDev2();
    ~SceneDev2() = default;

    void init() override;
    void enter() override;
    void exit() override;

    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;
};

