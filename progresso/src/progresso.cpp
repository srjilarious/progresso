
#include <iostream>
#include <string>
#include <algorithm>

#include <progresso/progresso.h>

namespace progresso
{

progresso::progresso(uint32_t curr, uint32_t max)
    : mCurrVal(curr), mMaxVal(max)
{

}

void 
progresso::tick(uint32_t amount)
{
    mCurrVal = std::max(static_cast<uint16_t>(0), 
            std::min(static_cast<uint16_t>(mCurrVal+amount), static_cast<uint16_t>(mMaxVal)));
}


float 
progresso::getPercentDone() const
{
    if(mMaxVal == 0) return 0.0f;

    return static_cast<float>(mCurrVal)/static_cast<float>(mMaxVal);
}

void 
progresso::draw(bool startOfLine)
{
    constexpr char FillChar = '#';
    constexpr char EmptyChar = '.';
    constexpr char LeftCap = '[';
    constexpr char RightCap = ']';
    constexpr uint16_t Width = 80;

    auto fillAmount = std::max(static_cast<uint16_t>(0), std::min(
            static_cast<uint16_t>(Width*getPercentDone()), 
            Width));
    auto remainAmount = Width-fillAmount;
    if(startOfLine) std::cout << '\r';
    std::cout << LeftCap 
            << std::string(fillAmount, FillChar) 
            << std::string(remainAmount, EmptyChar)
            << RightCap;
    if(startOfLine) std::cout << '\r';
    std::flush(std::cout);
}

}