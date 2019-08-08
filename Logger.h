#pragma once
#include <string>
#include <Windows.h>
#include <iostream>

namespace LOG
{
	class Logger
	{
	public:
		void operator()(RECT re) {
			std::cout << "left : " << re.left
				<< "top : " << re.top
				<< "right : " << re.right
				<< "bottom : " << re.bottom << std::endl;
		}
	};

}
