#include "FrameProvider.h"
#include "FrameProcesser.h"
#include "DisplayProcess.h"
#include "StatProcess.hpp"
#include "globalVariables.h"
#include "globalFunctions.hpp"

int main()
{
    char *argv[2] = { "1", "20" };
    CreateProc(frameProvider, 2, argv);
    delay(0.1);
    CreateProcInt(frameProcesser);
    delay(0.1);
    CreateProcInt(frameDisplayer);
    delay(0.1);
    CreateProcInt(statProcess);

    return 0;
}
