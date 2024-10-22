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
#pragma region �ð� ����

		dt = clkClock.restart();
		fRealDeltaTime = dt.asSeconds();
		fGameDeltaTime = fRealDeltaTime;
		fGameDeltaTime *= fTimeScale;

		fRealTime += fRealDeltaTime;
		fGameTime += fGameDeltaTime;

#pragma endregion �ð� ����

#pragma region �̺�Ʈ ����

		InputMgr::clear();
		while (window.pollEvent(ev))
		{
			if (ev.type == sf::Event::Closed)
			{
				window.close();
			}
			InputMgr::updateEvent(ev);
		}

#pragma endregion �̺�Ʈ ����

#pragma region ������Ʈ

		SceneMgr::Instance().Update(fGameDeltaTime);

#pragma endregion ������Ʈ

#pragma region ��ο�

		window.clear();

		SceneMgr::Instance().Draw(window);
		
		window.display();

#pragma endregion ��ο�
	}

}

void Framework::release()
{
	SceneMgr::Instance().RElease();
}
