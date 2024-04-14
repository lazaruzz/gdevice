#include <stdio.h>
#include <gdevice.h>

int main()
{
    // HANDLE window = gdOpen();
    int window = gdCreateWindow();
/*
    while(gdIsOpen(window)) 
    {
        // TODO gameloop
    }
*/

    printf("WalkerC: %i\n", window);
    return 0;
}
