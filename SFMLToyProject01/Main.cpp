#include "stdafx.h"

int main()
{
	Framework::Instance().init(1920, 1080, "Duck Hunting");
	Framework::Instance().doThis();
	Framework::Instance().release();
	return 0;
}