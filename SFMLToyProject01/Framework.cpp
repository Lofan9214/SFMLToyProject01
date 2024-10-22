#include "stdafx.h"
#include "Framework.h"

void Framework::init(int iWidth, int iHeight, const std::string& name)
{
	window.create(sf::VideoMode(iWidth, iHeight), name);

	SceneMgr::Instance().Init();
}

void Framework::doThis()
{
	sf::Time dt;
	sf::Event ev;
	while (window.isOpen())
	{
#pragma region 시간 간격

		dt = clkClock.restart();
		fRealDeltaTime = dt.asSeconds();
		fGameDeltaTime = fRealDeltaTime;
		fGameDeltaTime *= fTimeScale;

		fRealTime += fRealDeltaTime;
		fGameTime += fGameDeltaTime;

#pragma endregion 시간 간격

#pragma region 이벤트 루프

		InputMgr::clear();
		while (window.pollEvent(ev))
		{
			if (ev.type == sf::Event::Closed)
			{
				window.close();
			}
			InputMgr::updateEvent(ev);
		}

#pragma endregion 이벤트 루프

#pragma region 업데이트

		SceneMgr::Instance().Update(fGameDeltaTime);

#pragma endregion 업데이트

#pragma region 드로우

		window.clear();

		SceneMgr::Instance().Draw(window);
		
		window.display();

#pragma endregion 드로우
	}

}

void Framework::release()
{
	SceneMgr::Instance().RElease();
}
