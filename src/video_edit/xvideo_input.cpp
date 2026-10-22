#include "xvideo_input.h"
#include "user_Input.h"
#include "xdir.h"
#include <vector>
#include <iostream>

void XVideoInput::RunTask(XTask& task,
	const XTask::Data& data)
{
	task.Start(data);
	//等待任务结束，显示进度
	int p = 0;
	int l = -1;
	while (task.Running())
	{
		p = task.Progess();
		if (p != l)
		{
			std::cout << "\r%" << task.Progess();
			l = p;
		}
	}
	std::cout << "\r%" << "100" << std::endl;
}


void XVideoInput::Start(std::unique_ptr<XTask>task) {
	std::cout << __FUNCSIG__ << std::endl;
	UserInput user;
	XTask::Data data;
    user
        .RegTask("play", [&] { //播放视频处理函数
        data.type = "play";
        task->Start(data);
            })
        .RegTask(
            "cv", [&] { //cv处理任务函数
                std::cout << "cv task" << std::endl;
                std::cout << data.src << " "
                    << data.out << std::endl;
                data.type = "cv";
                task->Clear();

                if (XDir::IsDir(data.src))
                {
                    XDir dir;
                    auto files = dir.GetFiles(data.src);
                    for (auto f : files)
                    {
                        XTask::Data d = data;
                        d.src = f.path;
                        if (!XDir::IsDir(data.out))
                        {
                            XDir::Create(data.out);
                        }
                        d.out = data.out + "/" + f.name;
                        task->Clear();
                        RunTask(*task, d);
                    }
                }
                else
                {
                    RunTask(*task, data);
                }


            }
        ).Reg("-s", [&](const std::string& s) {//源文件
            std::cout << "-s：" << s << std::endl;
            data.src = s;
            })

        .Reg("-d", [&](const std::string& s) {//目标文件
        std::cout << "-d：" << s << std::endl;
        data.out = s;
            })

        .Reg("-b", [&](const std::string& s) { //剪切开始秒
        data.begin_sec = stoi(s);
            })

        .Reg("-e", [&](const std::string& s) {//剪切结束秒
        data.end_sec = stoi(s);
            })
        .Reg("-p", [&](const std::string& s) {//加密
        if (s.empty())
        {
            std::cout << "password:" << std::flush;
            std::string pass;
            std::cin >> pass;
            data.password = pass;
        }
        else
            data.password = s;
            })

        .Reg("-dp", [&](const std::string& s) {//解密
        if (s.empty())
        {
            std::cout << "password:" << std::flush;
            std::string pass;
            std::cin >> pass;
            data.password = pass;
        }
        else
            data.password = s;
        data.is_enc = false;
            })

        ;

    user.Start([&] (std::vector<std::string> prara) {
        std::cout << "init task" << std::endl;
        task->Clear();

        data = XTask::Data();
        // play test.mp4
        // cv test.mp4 out.mp4
        if (prara.size() < 4)
        {
            if (prara.size() > 1)
                data.src = prara[1];
            if (prara.size() > 2)
                data.out = prara[2];
        }

        });
}