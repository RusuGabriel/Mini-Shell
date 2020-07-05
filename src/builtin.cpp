#include "builtin.hpp"
#include <unistd.h>
#include <sys/resource.h>

using namespace std;

builtin *builtin::instance = nullptr;

builtin *builtin::getInstance()
{
    if (builtin::instance != nullptr)
        return instance;
    else
        return instance = new builtin();
}

void builtin::execute(command comm)
{
    builtin *instance = builtin::getInstance();
    int pid;
    int which = PRIO_PROCESS;
    if (!builtin::isKnown(comm))
        return;
    switch (instance->knownCommands[comm])
    {
    case CHDIR:
        chdir(comm);
        break;
    case SETPRIORITY:
        pid = getpid();
        int ret = setpriority(which, pid, atoi(comm));
        if(ret == -1){
            cout<<"Failed to change the priority of process with PID "<<pid<<endl;
            cout<<"Error no is: "<<errno<<endl;
        }else {
            cout<<"Priority changed"<<endl;
        }
        break;
    }
}
bool builtin::isKnown(command comm)
{
    builtin *instance = builtin::getInstance();
    return instance->knownCommands.find(comm) != instance->knownCommands.end();
}

builtin::builtin()
{
    knownCommands["cd"] = CHDIR;
    knownCommands["setuid"] = SETUID;
    knownCommands["setguid"] = SETGUID;
    knownCommands["setpriority"] = SETPRIORITY;
    knownCommands["symlink"] = SYMLINC;
};