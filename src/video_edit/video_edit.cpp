#include <iostream>
#include "xtask_factory.h"
#include "xvideo_input.h"
int main()
{
    XVideoInput input;
    input.Start(XTaskFactory::Creat());
    /*auto task = XTaskFactory::Creat();
    XTask::Data data;
    data.src = "test.mp4";
    data.out = "out.mp4";
    data.type = "cv";
    task->Start(data);*/
    //system("ffmpeg -y -i test.mp4 out.mp4");
    //system("ffplay test.mp4");
}

