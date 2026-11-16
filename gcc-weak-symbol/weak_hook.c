#include <stdio.h>

__attribute__((weak))
void test_hook(void)
{
    printf("Weak function called\n");
}
