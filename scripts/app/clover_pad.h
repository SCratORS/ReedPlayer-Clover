#pragma once
#include <string>
#include <map>

class CloverPadBase
{
private:

public:
	CloverPadBase();
	void init();
};

class cloverPadUI: public CloverPadBase
{
public:
	bool is_enable_user = false;
	bool is_enable_auto = false;
	std::string priority_input = "";
	std::map<std::string, bool> disable_id_list = {};
	cloverPadUI();
	void init();
	void EnableUserInput(bool, std::string);
};