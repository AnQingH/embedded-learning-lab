#include <stdio.h>

static void local_hook(void)
{

	printf("Local function called\n");

}



void public_hook(void)
{
	local_hook();
}
