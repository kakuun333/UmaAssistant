#pragma once

#include <iostream>

#include "cppsrc/util/Singleton.h"

class test : public Singleton<test>
{
public:
	void foo()
	{
		std::cout << "foooooooooooooooooooooo" << std::endl;
	};
};