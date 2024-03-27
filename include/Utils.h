#ifndef _UTILS_
#define _UTILS_

#include <time.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif

class Utils
{
public:
    static double cpuSecond(void)
    {
        struct timeval tp;
        gettimeofday(&tp, NULL);
        //                秒                 微秒
        return ((double)tp.tv_sec + (double)tp.tv_usec * 1e-6);
    }
};
#endif