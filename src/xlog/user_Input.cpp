#include "user_Input.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

static std::vector<std::string> Splict(std::string& s) {
	std::vector<std::string>vec;
	std::istringstream is(s);
	std::string temp;
	while (std::getline(is,temp,' ')){
		if (temp.empty()) continue;
		vec.push_back(temp);
	}
	return vec;
}

void UserInput::Start(std::function<void(std::vector<std::string>)>Init_) {
	std::cout << "User Input" << std::endl;
	while (!is_exit_) {
		std::string input;
		std::cout << "\n>>" << std::flush;
		std::getline(std::cin, input);
		if (input == " ")continue;
		auto vec = Splict(input);
		if (vec.empty())continue;
		/*for (auto v : vec) std::cout << v << std::endl;*/
		/*std::cout << input << std::endl;*/
		if (input == "exit") break;
		std::string type = vec[0];
		Init_(vec);

		//参数处理
		for (int i = 0; i < vec.size(); i++)
		{
			auto& k = vec[i];
			auto fitr = keys_func_.find(k);
			if (fitr != keys_func_.end()) {
				if (vec.size() - 1 > i) {
					auto& v = vec[i + 1];
					if (keys_func_.find(v) == keys_func_.end()) {
						std::cout << k << ":" << v << std::endl;
						fitr->second(v);
						i++;
						continue;
					}
				}
				fitr->second("");
				std::cout << k << " " << std::endl;
			}
		}

		//执行任务
		auto task = task_func_.find(type);
		if (task == task_func_.end()) {
			std::cout << type << "Not Support this commond!" << std::endl;
		}
		else {
			task->second();
		}
	}
	
}