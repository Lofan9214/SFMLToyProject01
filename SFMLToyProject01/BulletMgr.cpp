#include "stdafx.h"
#include "BulletMgr.h"

BulletMgr::BulletMgr(int count)
{
	for (int i = 0; i < count; ++i)
	{
		BulletGo* tmp = new BulletGo("graphics/Bullet.png", "bullet");
		tmp->setOrigin(Origins::MC);
		vecBullet.push_back(tmp);
		lstRemainBullet.push_back(tmp);
	}
}

void BulletMgr::init()
{
}

void BulletMgr::update(float dt)
{
	reloadtime += dt;

	for (auto it = lstFiredBullet.rbegin(); it != lstFiredBullet.rend(); ++it)
	{
		if ((*it)->isActive() == false)
		{
			lstRemainBullet.push_back(*it);
			lstFiredBullet.remove(*it);
		}
	}
}

void BulletMgr::reset()
{
	reloadtime = 0.f;
	lstFiredBullet.clear();
	lstRemainBullet.clear();
	std::copy(vecBullet.begin(), vecBullet.end(), std::back_inserter(lstRemainBullet));
}

std::list<BulletGo*> BulletMgr::getBulletGoList() const
{
	std::list<BulletGo*> tmp;
	std::copy(vecBullet.begin(), vecBullet.end(), std::back_inserter(tmp));
	return tmp;
}

void BulletMgr::fire(PlayerGo* playerGo)
{
	if (reloadtime > 0.5f && lstRemainBullet.size() > 3)
	{
		reloadtime = 0.f;
		for (int i = 0;i < 3;++i)
		{
			auto itbegin = lstRemainBullet.begin();
			(*itbegin)->fire(Framework::Instance().getWindow(), playerGo->getMuzzlePos());

			lstFiredBullet.push_back(*itbegin);
			lstRemainBullet.erase(itbegin);
		}
		playerGo->playGunsound("sound/Bernice_Skill01_Fire.wav");
		playerGo->setfireClick(true);
	}
}

void BulletMgr::setDifficulty(int dif)
{
	for (auto it : vecBullet)
	{
		it->setDifficulty(dif);
	}
}

int BulletMgr::checkHit(DuckMgr& duckMgr)
{
	int score = 0;
	int result = 0;
	std::list<DuckGo*> aliveduck = duckMgr.getLivingDuck();
	for (auto rit = lstFiredBullet.rbegin(); rit != lstFiredBullet.rend();++rit)
	{
		result = (*rit)->checkHit(aliveduck);
		if (result != 0)
		{
			lstRemainBullet.push_back(*rit);
			lstFiredBullet.remove(*rit);
		}
		score += result;
	}
	return score;
}
