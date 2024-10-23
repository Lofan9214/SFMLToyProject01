#pragma once
#include "Scene.h"

class SceneDev2 : public Scene
{
protected:
    float respawntime = 0.f;
    int score = 0;
    float time = 0.f;
    sf::RectangleShape timebar;

public:
    SceneDev2();
    ~SceneDev2() = default;

    void init() override;
    void enter() override;
    void exit() override;

    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;
};

