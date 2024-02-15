#include "common_lib.h"
#include "syscall_if.h"
#include "um_lib_helper.h"

STATUS
__main(
    DWORD       argc,
    char**      argv
)
{
    UNREFERENCED_PARAMETER(argc);
    UNREFERENCED_PARAMETER(argv);

    TID tid = 0;
    TID ParentId = 0;
    DWORD TimesYielded = 0;
    DWORD TimesBlocked = 0;
    DWORD ChildrenCount = 0;
    DWORD PredecessorCount = 0;

    STATUS status = SyscallGetCurrentThreadId(&tid);
    if (!SUCCEEDED(status))
    {
        LOG_FUNC_ERROR("SyscallGetCurrentThreadId", status);
        return status;
    }

    SyscallGetThreadInformation(tid, &TimesYielded, &TimesBlocked, &ParentId, &ChildrenCount, &PredecessorCount);
    if (!SUCCEEDED(status))
    {
        LOG_FUNC_ERROR("SyscallGetThreadInformation", status);
        return status;
    }

    LOGL("Thread [tid=0x%X, parentTid=0x%X] yielded %d times, was blocked %d times and has %d children and %d predecessors.\n",
        tid, ParentId, TimesYielded, TimesBlocked, ChildrenCount, PredecessorCount);

    return STATUS_SUCCESS;
}