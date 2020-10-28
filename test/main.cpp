#include <stdlib.h>
#include <stdio.h>

#include <progresso/progresso.h>

int main()
{
    printf("Hello World.\n");

    progresso::progresso p1 = {30, 100};
    p1.draw();
    
    return 0;
}