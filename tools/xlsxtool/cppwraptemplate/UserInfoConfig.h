#pragma once
#include <string>
#include <map>

class UserInfoConfig
{
public:

	// 模板保存每个属性

	// id
	unsigned int id;

	// name
	std::string name;

	// email
	std::string email;

	// phone
	std::string phone;

	// 模板生成构造函数
	UserInfoConfig(){}
	UserInfoConfig(unsigned int _id, std::string _name, std::string _email, std::string _phone)
		: id(_id), name(_name), email(_email), phone(_phone)
	{}
};