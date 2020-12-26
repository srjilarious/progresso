#include <stdlib.h>
#include <stdio.h>
#include <chrono>
#include <thread>
#include <iostream>

#include <progresso/progresso.h>

int main()
{
    std::cout << std::endl << std::endl << "Simple ASCII progress bar w/ intermediate characters:" << std::endl;
    progresso::progresso p1 = {0, 160, 20, true, {
        "(", ")", "#", {"_", ".", "-", "*"}, "-"
    }};

    for(int i = 0; i < p1.getTotal(); i++) {
        p1.tick(1);
        std::this_thread::sleep_for(std::chrono::milliseconds(30));
        p1.draw();
    }


    std::cout << std::endl << std::endl << "unicode block based progress bar:" << std::endl;
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


    std::cout << std::endl << std::endl << "Another unicode block progress bar:" << std::endl;
    progresso::progresso p4 = {0, 200, 40, true, {
        u8"\u2595", // Right 1/8th block
        u8"\u258f", // Left 1/8th block
        u8"\u2588", // Full block
        { u8"\u2598", u8"\u259a", u8"\u2599", u8"\u2588"}, 
        u8"\u2588", // Full block,
        true,
        progresso::color::foreground::BoldWhiteColor,
        progresso::color::ResetColor,

        progresso::color::foreground::BoldYellowColor,
        progresso::color::background::BlueColor,

        progresso::color::foreground::BlueColor,
        progresso::color::background::BlueColor}};

    for(int i = 0; i < p4.getTotal(); i++) {
        p4.tick(1);
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        p4.draw();
    }

    std::cout << std::endl;


    std::cout << std::endl << std::endl << "unicode block progress with dimmed intermediates:" << std::endl;
    progresso::progresso p5 = {0, 100, 40, true, {
        u8"\u2595", // Right 1/8th block
        u8"\u258f", // Left 1/8th block
        u8"\u2588", // Full block
        { u8"\u2591", u8"\u2592", u8"\u2593", u8"\u2588"}, 
        u8"\u2588", // Full block,
        true,
        progresso::color::foreground::BoldWhiteColor,
        progresso::color::ResetColor,

        progresso::color::foreground::BoldCyanColor,
        progresso::color::background::BlueColor,

        progresso::color::foreground::BlueColor,
        progresso::color::background::BlueColor}};

    for(int i = 0; i < p5.getTotal(); i++) {
        p5.tick(1);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        p5.draw();
    }

    std::cout << std::endl;

    std::cout << "Finished." << std::endl;
    return 0;
}