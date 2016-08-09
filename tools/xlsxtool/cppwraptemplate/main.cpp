#include "ConfigMgr.h"
#include <iostream>

int main()
{
	std::cout << ConfigMgr::GetInstance()->GetUserInfoConfig(111).email;
	return 0;
}