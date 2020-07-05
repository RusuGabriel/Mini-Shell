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
    int pid = getpid();
    int which = PRIO_PROCESS;
    if(!builtin::isKnown(comm))
        return;
    switch (instance->knownCommands[comm])
    {
    case CHDIR:
        chdir(comm);
        break;
    case SETPRIORITY:
        cout<<(const char *)comm<<endl;
        setpriority(which,pid,atoi(comm));
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