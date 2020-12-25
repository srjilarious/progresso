#include <stdlib.h>
#include <stdio.h>
#include <chrono>
#include <thread>
#include <iostream>

#include <progresso/progresso.h>

int main()
{
    std::cout << std::endl << std::endl << "unicode block based progress bar.:" << std::endl;
    progresso::progresso p1 = {0, 160, 20, true, {
        "(", ")", "#", {"_", ".", "-", "*"}, "-"
    }};

    for(int i = 0; i < p1.getTotal(); i++) {
        p1.tick(1);
        std::this_thread::sleep_for(std::chrono::milliseconds(30));
        p1.draw();
    }


    std::cout << std::endl << std::endl << "unicode block based progress bar.:" << std::endl;
    progresso::progresso p2 = {0, 160, 40, true, progresso::styles::BlockStyleFilledBackground};

    for(int i = 0; i < p2.getTotal(); i++) {
        p2.tick(1);
        std::this_thread::sleep_for(std::chrono::milliseconds(40));
        p2.draw();
    }


    std::cout << std::endl << std::endl << "progress bar without intermediate characters:" << std::endl;
    progresso::progresso p3 = {0, 40, 40, true, {
        "(", ")", "#", {}, "-"
    }};

    for(int i = 0; i < p3.getTotal(); i++) {
        p3.tick(1);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        p3.draw();
    }

    std::cout << std::endl;
    std::cout << "Finished." << std::endl;
    return 0;
}