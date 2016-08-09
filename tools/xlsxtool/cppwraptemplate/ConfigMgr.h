#pragma once
#include <iostream>

// ģ��ѭ������ÿ��ͷ�ļ�
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
		// ģ��ѭ����ʼ��ÿ��������ֵ
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
	// ģ��ѭ������ÿ������Ӧ�ĳ���
	unsigned int UserInfoConfigLength;

private:
	// ģ��ѭ������ÿ�����map
	std::map<unsigned int, UserInfoConfig> _UserInfoConfig;

public:
	// ģ��ѭ������ÿ�����Ļ�ȡ����
	UserInfoConfig GetUserInfoConfig(unsigned int id)
	{
		return _UserInfoConfig[id];
	}
	
	static ConfigMgr* Instance;
};
ConfigMgr* ConfigMgr::Instance = nullptr;