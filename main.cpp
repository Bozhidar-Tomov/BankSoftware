#include "onStart.h"

#include <iostream>

int main(void)
{
    // make system call to enable ANSI support on Windows terminal. ANSI supported by default on other platforms
    system("");

    run();
    return 0;
}