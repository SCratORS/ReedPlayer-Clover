#pragma once

#include <vector>

class cloverTask
{
	struct clover_task
	{
		bool sleep;
		void (*func) ();
		int klass;
	};

public:
	std::vector<clover_task* > list;
	cloverTask();
	void Init();
};
