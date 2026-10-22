#include <iostream>
#include "xlog.h"
#include "log_fac.h"
#include "xexec.h"
#include "user_Input.h"
int main()
{

    UserInput user;
    user.Reg("-s", [](const std::string& s) {
        std::cout << "-------src : " << s << std::endl;
        }
    ).Reg("-d", [](const std::string& d) {
        std::cout << "-----dev : " << d << std::endl;
        }
    ).Reg("-p", [](const std::string& p) {
        std::cout << "------password : " << p << std::endl;
        }
    ).RegTask("cv", [] {
        std::cout << "@@@@@cv task@@@@" << std::endl;
        });

    user.Start();
    //XExec exec;
    //exec.Start("ping 127.0.0.1");
    //std::string out;
    //while (exec.Running()) {
    //    if (exec.GetOutPut(out)) {
    //        std::cout << out << std::endl;
    //    }
    //} 
    //while (exec.GetOutPut(out)) {
    //    std::cout << out << std::endl;
    //}
    //exec.Wait();
    ////exec.Start("cd");
    //Cxlog c; 
    //std::cout << "Hello World!\n";
}

