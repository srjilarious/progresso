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
    std::cout << std::endl << std::endl << "progress bar without intermediate characters:" << std::endl;
    runProgressBar(
        progresso::progresso(0, 40, 40, {
            "(", ")", "#", {}, "-"
        }),
        1, 30
    );

    std::cout << std::endl << std::endl << "Simple ASCII progress bar w/ intermediate characters:" << std::endl;
    runProgressBar(
        progresso::progresso(0, 160, 20, {
            "(", ")", "#", {"_", ".", "-", "*"}, "-"
        }),
        1, 30
    );

    std::cout << std::endl;

    std::cout << "Finished." << std::endl;
    return 0;
}