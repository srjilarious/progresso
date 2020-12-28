#include <stdlib.h>
#include <stdio.h>
#include <chrono>
#include <thread>
#include <iostream>

#include <progresso/progresso.h>

int main()
{
    std::cout << std::endl << std::endl << "Simple ASCII progress bar w/ intermediate characters:" << std::endl;
    auto p1 = progresso::progresso(0, 160, 20, {
        "(", ")", "#", {"_", ".", "-", "*"}, "-"
    });

    for(int i = 0; i < p1.getTotal(); i++) {
        p1.tick(1);
        std::this_thread::sleep_for(std::chrono::milliseconds(30));
        p1.draw();
    }


    std::cout << std::endl << std::endl << "unicode block based progress bar:" << std::endl;
    auto p2 = progresso::progresso(0, 160, 40, progresso::styles::BlockStyleFilledBackground);

    for(int i = 0; i < p2.getTotal(); i++) {
        p2.tick(1);
        std::this_thread::sleep_for(std::chrono::milliseconds(40));
        p2.draw();
    }


    std::cout << std::endl << std::endl << "progress bar without intermediate characters:" << std::endl;
    auto p3 = progresso::progresso(0, 40, 40, {
        "(", ")", "#", {}, "-"
    });

    for(int i = 0; i < p3.getTotal(); i++) {
        p3.tick(1);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        p3.draw();
    }

    std::cout << std::endl;

    std::cout << std::endl << std::endl << "Another unicode block progress bar:" << std::endl;
    auto p4 = progresso::progresso(0, 1024*1024*30, 40, {
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
        progresso::color::background::BlueColor},
        progresso::ValueDisplayStyle::ValueMaxWithSuffix,
        1024*1024,
        "MB");

    // Simulate downloading at 128k / 50ms.
    for(uint64_t i = 0; i < p4.getTotal();) {
        i+= 1024*128;
        p4.setValue(i);
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        p4.draw();
    }

    std::cout << std::endl;


    std::cout << std::endl << std::endl << "unicode block progress with dimmed intermediates:" << std::endl;
    progresso::progresso p5 = {0, 50*1024*1024, 40, {
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
        progresso::color::background::BlueColor},
        progresso::ValueDisplayStyle::ValueBothWithSuffix,
        1024*1024,
        "MB"};

    // Simulate 512k / 50ms
    for(int i = 0; i < p5.getTotal();) {
        i += 1024*512;
        p5.setValue(i);
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        p5.draw();
    }

    std::cout << std::endl;

    std::cout << "Finished." << std::endl;
    return 0;
}