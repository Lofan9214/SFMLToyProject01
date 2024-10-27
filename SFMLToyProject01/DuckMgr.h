#pragma once
#include "DuckGo.h"

class DuckMgr
{
protected:
	std::vector<DuckGo*> vecDuck;
	std::list<DuckGo*> lstAliveDuck;
	std::list<DuckGo*> lstDeadDuck;
	float respawntime = 0.f;

	DuckMgr(const DuckMgr&) = delete;
	DuckMgr& operator=(const DuckMgr&) = delete;

public:
	DuckMgr() = default;
	DuckMgr(int count);
	virtual ~DuckMgr() = default;

	std::list<DuckGo*> getDuckGoList() const;
	std::list<DuckGo*> getLivingDuck() const;
	void setDifficulty(float diff);

	void init();
	void update(float dt);
	void reset();
};

