#include <stdlib.h>
#include <stdio.h>
#include <chrono>
#include <thread>
#include <iostream>

#include <progresso/progresso.h>

int main()
{
    printf("Hello World.\n");

    progresso::progresso p1 = {0, 160, 40, true, {
        '(', ')', '#', {'_', '.', '-', '*'}, '-'
    }};

    for(int i = 0; i < p1.getTotal(); i++) {
        p1.tick(1);
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        p1.draw();
    }

    p1.erase();
    
    std::cout << "Finished." << std::endl;
    return 0;
}