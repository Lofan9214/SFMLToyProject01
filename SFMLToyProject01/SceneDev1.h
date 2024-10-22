#pragma once
#include "Scene.h"

class SceneDev1 :
    public Scene
{
protected:
public:
    SceneDev1();
    ~SceneDev1() = default;

    void init() override;
    void enter() override;
    void exit() override;

    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;

};

