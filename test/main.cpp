#include <stdlib.h>
#include <stdio.h>
#include <chrono>
#include <thread>
#include <iostream>

#include <progresso/progresso.h>

int main()
{
    printf("Hello World.\n");

    progresso::progresso p1 = {0, 160, 20, true, {
        '(', ')', "#", {"_", ".", "-", "*"}, "-"
    }};

    for(int i = 0; i < p1.getTotal(); i++) {
        p1.tick(1);
        std::this_thread::sleep_for(std::chrono::milliseconds(30));
        p1.draw();
    }


    std::cout << std::endl << std::endl << "unicode block:" << std::endl;
    progresso::progresso p2 = {0, 160, 40, true, {
        '[', ']', u8"\u2589", 
        { u8"\u258f", u8"\u258d", u8"\u258b", u8"\u2589"}, 
        u8" "
    }};

    for(int i = 0; i < p2.getTotal(); i++) {
        p2.tick(1);
        std::this_thread::sleep_for(std::chrono::milliseconds(40));
        p2.draw();
    }

    std::cout << std::endl;

    progresso::progresso p3 = {0, 40, 40, true, {
        '(', ')', "#", {}, "-"
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