#include <stdio.h>

__attribute__((weak)) void test_hook(void)
{
    printf("Second weak function called\n");
}
