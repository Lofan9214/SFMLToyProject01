#pragma once
#include "BulletGo.h"
#include "PlayerGo.h"
#include "DuckMgr.h"

class BulletMgr
{
protected:
	std::vector<BulletGo*> vecBullet;
	std::list<BulletGo*> lstFiredBullet;
	std::list<BulletGo*> lstRemainBullet;
	float reloadtime = 0.f;

	BulletMgr(const BulletMgr&) = delete;
	BulletMgr& operator=(const BulletMgr&) = delete;
public:
	BulletMgr() = default;
	BulletMgr(int count);
	virtual ~BulletMgr() = default;

	void init();
	void update(float dt);
	void reset();

	std::list<BulletGo*> getBulletGoList() const;

	void fire(PlayerGo* playerGo);
	void setDifficulty(int dif);
	int checkHit(DuckMgr& lstliveduck);
};

