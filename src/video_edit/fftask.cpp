#include "fftask.h"
#include "xexec.h"
#include <string>
#include <iostream>
#define DEFAULTPASS "0123456789ABCDEF0123456789ABCDEF"


static int TimeToSec(const std::string& s) {
	if (s.size() < 8) return 0;
	int h = 0;
	int m = 0;
	int sec = 0;
	try {
		 h = std::stoi(s.substr(0, 2));
		 m = std::stoi(s.substr(3, 2));
		 sec = std::stoi(s.substr(6, 2));
	}
	catch (const std::exception&) {

	}
	
	return h * 3600 + m * 60 + sec;
}

bool FFtask::Start(const Data& prara) {
	std::string cmd = "ffmpeg -y ";
	if (prara.type == "play")
	{
		cmd = "ffplay ";
	}

	if (prara.begin_sec > 0)
		cmd += " -ss " + std::to_string(prara.begin_sec);
	if (prara.end_sec > 0)
	{
		int t = prara.end_sec - prara.begin_sec;
		if (t > 0)
			cmd += " -t " + std::to_string(t);
	}
	if (!prara.is_enc)
	{
		if (!prara.password.empty())
		{
			std::string pass = DEFAULTPASS;
			for (int i = 0;
				i < prara.password.size() && i < pass.size(); i++)
			{
				pass[i] = prara.password[i];
			}
			cmd += "  -decryption_key ";
			cmd += pass;
		}
	}

	//输入文件
	cmd += " -i " + prara.src;
	if (!prara.password.empty() && prara.is_enc)
	{
		std::string pass = DEFAULTPASS;
		cmd += " -encryption_scheme cenc-aes-ctr -encryption_kid 0123456789ABCDEF0123456789ABCDEF ";
		cmd += " -encryption_key ";
		for (int i = 0;
			i < prara.password.size() && i < pass.size(); i++)
		{
			pass[i] = prara.password[i];
		}
		cmd += pass;
	}

	//输出文件
	if (!prara.out.empty())
		cmd += " " + prara.out;

	std::cout << "cmd:" << cmd << std::endl;

	exec_.Start(cmd.c_str(), [this](const std::string& s) {
		//std::cout << s << std::endl;

		//Duration: 00:02:31.17, start: 0.000000, bitrate: 575 kb/s
		if (total_sec <= 0)
		{
			auto pos = s.find("Duration: ");
			if (pos != std::string::npos) {
				std::string tem = s.substr(pos + 10, 8);
				//std::cout << tem << std::endl;
				total_sec = TimeToSec(tem);
				std::cout << "Total Sec: " << total_sec << "s" << std::endl;
				return;
			}
		}
		//frame = 604 fps = 294 q = 29.0 size = 1280KiB time = 00:00 : 20.06 bitrate = 522.6kbits / s speed = 9.77x
		{
			auto pos = s.find("time=");
			if (pos != std::string::npos) {
				std::string tem = s.substr(pos + 5, 8);
				int p = TimeToSec(tem);
				if (total_sec > 0)
					progess_ = p * 100 / total_sec;
				return;
			}	
		}

		});


	return true;
}