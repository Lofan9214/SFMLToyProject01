#include "stdafx.h"
#include "DuckMgr.h"

DuckMgr::DuckMgr(int count)
{
	for (int i = 0; i < count; ++i)
	{
		DuckGo* tmp = new DuckGo("graphics/duckAll.png", "duck");
		tmp->setOrigin(Origins::MC);
		vecDuck.push_back(tmp);
		lstAliveDuck.push_back(tmp);
	}
}

std::list<DuckGo*> DuckMgr::getDuckGoList() const
{
	std::list<DuckGo*> tmp;
	std::copy(vecDuck.begin(), vecDuck.end(), std::back_inserter(tmp));
	return tmp;
}

std::list<DuckGo*> DuckMgr::getLivingDuck() const
{
	return lstAliveDuck;
}

void DuckMgr::setDifficulty(float diff)
{
	for (auto itDuck : vecDuck)
	{
		itDuck->setDifficulty(diff);
	}
}

void DuckMgr::init()
{
}

void DuckMgr::update(float dt)
{
	respawntime += dt;

	if (respawntime > 3.f)
	{
		for (auto rit = lstDeadDuck.rbegin();rit != lstDeadDuck.rend();++rit)
		{
			if ((*rit)->isActive() == false)
			{
				respawntime = 0.f;

				(*rit)->spawn(true);

				lstAliveDuck.push_back(*rit);
				lstDeadDuck.remove(*rit);
			}
		}
	}

	for (auto rit = lstAliveDuck.rbegin();rit != lstAliveDuck.rend();++rit)
	{
		if ((*rit)->isAlive() == false)
		{
			lstDeadDuck.push_back(*rit);
			lstAliveDuck.remove(*rit);
		}
	}
}

void DuckMgr::reset()
{
	respawntime = 0.f;
	lstDeadDuck.clear();
	lstAliveDuck.clear();
	std::copy(vecDuck.begin(), vecDuck.end(), std::back_inserter(lstAliveDuck));
}
