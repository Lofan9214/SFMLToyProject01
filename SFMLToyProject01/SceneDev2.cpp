#include "stdafx.h"
#include "SceneDev2.h"
#include "SpriteGo.h"
#include "PlayerGo.h"
#include "TextGo.h"

SceneDev2::SceneDev2()
	: Scene(SceneIds::Dev2), gameOver(nullptr), bulletMgr(15), duckMgr(10)
{
}

void SceneDev2::init()
{
	std::cout << "SceneDev2::Init()" << std::endl;

	cloudGo = new SpriteGo("graphics/underbackground.png");
	AddGo(cloudGo);

	groundGo = new SpriteGo("graphics/background2.png");
	groundGo->setOrigin(Origins::BL);
	groundGo->setPosition({ 0.f, (float)Framework::Instance().getWindow().getSize().y });
	AddGo(groundGo);

	auto lstbullet = bulletMgr.getBulletGoList();
	gameObjects.insert(gameObjects.end(), lstbullet.begin(), lstbullet.end());

	playerGo = new PlayerGo("graphics/Player2.png", "player");
	AddGo(playerGo);

	auto lstduck = duckMgr.getDuckGoList();
	gameObjects.insert(gameObjects.end(), lstduck.begin(), lstduck.end());

	textScore = new TextGo("fonts/KOMIKAP_.ttf", "Scoreboard");

	AddGo(textScore);
	textScore->setPosition({ 10.f, 10.f });
	gameOver = new TextGo("fonts/KOMIKAP_.ttf", "GameOver");
	AddGo(gameOver);

	gameOver->setActive(false);
	gameOver->setOrigin(Origins::MC);
	gameOver->setPosition({ Framework::Instance().getWindow().getSize().x * 0.5f,
		Framework::Instance().getWindow().getSize().y * 0.5f });
	Scene::init();
}

void SceneDev2::enter()
{
	std::cout << "SceneDev2::Enter()" << std::endl;

	Framework::Instance().setTimeScale(1.0);
	time = 0.f;
	score = 0;

	ResourceMgr<sf::Texture>::Instance().load("graphics/underbackground.png");
	ResourceMgr<sf::Texture>::Instance().load("graphics/background2.png");
	ResourceMgr<sf::SoundBuffer>::Instance().load("sound/Bernice_Skill01_Fire.wav");
	ResourceMgr<sf::SoundBuffer>::Instance().load("sound/chicken5.wav");
	ResourceMgr<sf::Texture>::Instance().load("graphics/Player2.png");
	playerGo->setOrigin({ 100.f,300.f });
	playerGo->setPosition({ 1920 / 2, 1080 });
	ResourceMgr<sf::Texture>::Instance().load("graphics/Bullet.png");
	ResourceMgr<sf::Texture>::Instance().load("graphics/duckAll.png");
	ResourceMgr<sf::Font>::Instance().load("fonts/KOMIKAP_.ttf");

	timebar.setFillColor(sf::Color::Red);
	timebar.setSize({ Framework::Instance().getWindow().getSize().x + 0.f , 10.f });

	gameOver->setActive(false);

	Scene::enter();
}

void SceneDev2::exit()
{
	std::cout << "SceneDev2::exit()" << std::endl;

	Scene::exit();

	ResourceMgr<sf::Texture>::Instance().unload("graphics/underbackground.png");
	ResourceMgr<sf::Texture>::Instance().unload("graphics/background2.png");
	ResourceMgr<sf::SoundBuffer>::Instance().unload("sound/Bernice_Skill01_Fire.wav");
	ResourceMgr<sf::SoundBuffer>::Instance().unload("sound/chicken5.wav");
	ResourceMgr<sf::Texture>::Instance().unload("graphics/Player2.png");
	ResourceMgr<sf::Texture>::Instance().unload("graphics/Bullet.png");
	ResourceMgr<sf::Texture>::Instance().unload("graphics/duckAll.png");
	ResourceMgr<sf::Font>::Instance().unload("fonts/KOMIKAP_.ttf");
}

void SceneDev2::update(float dt)
{
	if (InputMgr::isKeyDown(sf::Keyboard::Space)
		&& Framework::Instance().getTimeScale() == 0)
	{
		SceneMgr::Instance().changeScene(SceneIds::Dev1);
		return;
	}

	time += 192.0f * dt;

	duckMgr.update(dt);
	bulletMgr.update(dt);

	if (Framework::Instance().getTimeScale() != 0)
	{
		if (InputMgr::isKeyPressing(sf::Keyboard::D))
		{
			playerGo->playerMove(400);
		}
		if (InputMgr::isKeyPressing(sf::Keyboard::A))
		{
			playerGo->playerMove(-400);
		}
		if ((InputMgr::isKeyUp(sf::Keyboard::D) || InputMgr::isKeyUp(sf::Keyboard::A)))
		{
			playerGo->playerMove(0);
		}
	}

	if (InputMgr::isMouseButtonDown(sf::Mouse::Left))
	{
		bulletMgr.fire(playerGo);
	}
	if (InputMgr::isMouseButtonUp(sf::Mouse::Left))
	{
		playerGo->setfireClick(false);
	}

#pragma region 面倒 眉农

	int upscore = bulletMgr.checkHit(duckMgr);
	score += upscore;
	time -= upscore * 20;
	textScore->setString("Score : " + std::to_string(score));

#pragma endregion 面倒 眉农


	if (score % 100 == 0)
	{
		duckMgr.setDifficulty(score / 100);
		bulletMgr.setDifficulty(score / 100);
	}


	timebar.setSize({ Framework::Instance().getWindow().getSize().x - time, 10.f });
	if (Framework::Instance().getWindow().getSize().x < time)
	{
		if (gameOver != nullptr)
		{
			gameOver->setActive(true);
			gameOver->setString("Game Over! score: " + std::to_string(score) + "\npress Space to go Main screen");
		}
		Framework::Instance().setTimeScale(0.0);
	}

	auto cloudpos = cloudGo->getPosition();
	cloudpos.x -= 30.f * dt;
	if (cloudpos.x < -5540)
	{
		std::cout << "cloudmove" << std::endl;

		cloudpos.x += 5000.f;
	}
	cloudGo->setPosition(cloudpos);
	Scene::update(dt);
}

void SceneDev2::draw(sf::RenderWindow& window)
{
	Scene::draw(window);
	window.draw(timebar);
}
