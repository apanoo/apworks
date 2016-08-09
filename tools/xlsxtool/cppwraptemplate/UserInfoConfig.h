#pragma once
#include <string>
#include <map>

class UserInfoConfig
{
public:

	// ģ�屣��ÿ������

	// id
	unsigned int id;

	// name
	std::string name;

	// email
	std::string email;

	// phone
	std::string phone;

	// ģ�����ɹ��캯��
	UserInfoConfig(){}
	UserInfoConfig(unsigned int _id, std::string _name, std::string _email, std::string _phone)
		: id(_id), name(_name), email(_email), phone(_phone)
	{}
};