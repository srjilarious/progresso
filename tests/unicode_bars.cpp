#include <stdlib.h>
#include <stdio.h>
#include <chrono>
#include <thread>
#include <iostream>

#include <progresso/progresso.h>

void runProgressBar(progresso::progresso bar, int amountTick, int delayTick)
{
    for(int i = 0; i < bar.getTotal();) {
        i+= amountTick;
        bar.setValue(i);
        std::this_thread::sleep_for(std::chrono::milliseconds(delayTick));
        bar.draw();
    }
}

int main()
{
    std::cout << std::endl << std::endl << "unicode block based progress bar:" << std::endl;
    auto p1 = progresso::progresso(0, 160, 40, progresso::styles::BlockStyleFilledBackground);
    p1.showCursor(false);
    runProgressBar(p1, 1, 40);

    std::cout << std::endl;

    std::cout << std::endl << std::endl << "Another unicode 'climbing' block progress bar with max value suffix:" << std::endl;
    
    // Progress bar for 30 MB.
    auto p2 = progresso::progresso(0, 1024*1024*30, 40, {
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

    // Simulate downloading at 128k / 50ms -> 2.5MB/sec
    runProgressBar(p2, 1024*128, 50);
    std::cout << std::endl;


    std::cout << std::endl << std::endl << "unicode block progress with dimmed intermediates:" << std::endl;

    // Progress bar for 20 MB.
    progresso::progresso p3 = {0, 20*1024*1024, 40, {
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

    // Simulate 128k / 50ms -> 2.5 MB / sec
    runProgressBar(p3, 1024*128, 50);
    
    std::cout << std::endl;

     std::cout << std::endl << std::endl << "unicode block progress with rising intermediate blocks:" << std::endl;

    // Progress bar for 20 MB.
    progresso::progresso p4 = {0, 20*1024*1024, 40, {
        u8"\u2523", // left T
        u8"\u252b", // right T
        u8"\u2588", // Full block
        // Intermediates: block grows up from bottom.
        { u8"\u2581", u8"\u2582", u8"\u2583", u8"\u2584",
          u8"\u2585", u8"\u2586", u8"\u2587", u8"\u2588"}, 
        u8"\u2588", // Full block,
        true,
        progresso::color::foreground::BoldYellowColor,
        progresso::color::ResetColor,

        progresso::color::foreground::BoldMagentaColor,
        progresso::color::background::BlueColor,

        progresso::color::foreground::BlueColor,
        progresso::color::background::BlueColor},
        progresso::ValueDisplayStyle::ValueBothWithSuffix,
        1024*1024,
        "MB"};

    // Simulate 128k / 50ms -> 2.5 MB / sec
    runProgressBar(p4, 1024*128, 50);
    
    std::cout << std::endl;

    std::cout << "Finished." << std::endl;
    p1.showCursor(true);
    return 0;
}