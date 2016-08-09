#pragma once
#include <iostream>

// 模板循环插入每个头文件
#include "UserInfoConfig.h"

class ConfigMgr
{
public:
	static ConfigMgr* GetInstance()
	{
		if (Instance == nullptr)
		{
			Instance = new ConfigMgr();
		}
		return Instance;
	}

	ConfigMgr()
	{
		if (!InitConfig())
		{
			std::cout << "Config Init Failed!" << std::endl;
			return;
		}
	}

	bool InitConfig()
	{
		// 模板循环初始化每个配表的数值
		UserInfoConfigLength = 6;
		_UserInfoConfig.insert(std::map<unsigned int, UserInfoConfig> ::value_type(111, UserInfoConfig(111, "apanoo", "apanoo@126com", "123456"))); 
		_UserInfoConfig.insert(std::map<unsigned int, UserInfoConfig> ::value_type(112, UserInfoConfig(112, "bpanoo", "apanoo@126com", "123456")));
		_UserInfoConfig.insert(std::map<unsigned int, UserInfoConfig> ::value_type(113, UserInfoConfig(113, "cpanoo", "apanoo@126com", "123456")));
		_UserInfoConfig.insert(std::map<unsigned int, UserInfoConfig> ::value_type(114, UserInfoConfig(114, "dpanoo", "apanoo@126com", "123456")));
		_UserInfoConfig.insert(std::map<unsigned int, UserInfoConfig> ::value_type(115, UserInfoConfig(115, "epanoo", "apanoo@126com", "123456")));
		_UserInfoConfig.insert(std::map<unsigned int, UserInfoConfig> ::value_type(116, UserInfoConfig(116, "fpanoo", "apanoo@126com", "123456")));

		return true;
	}

public:
	// 模板循环输入每个配表对应的长度
	unsigned int UserInfoConfigLength;

private:
	// 模板循环定义每个配表map
	std::map<unsigned int, UserInfoConfig> _UserInfoConfig;

public:
	// 模板循环生成每个配表的获取函数
	UserInfoConfig GetUserInfoConfig(unsigned int id)
	{
		return _UserInfoConfig[id];
	}
	
	static ConfigMgr* Instance;
};
ConfigMgr* ConfigMgr::Instance = nullptr;