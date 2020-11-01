
#include <iostream>
#include <string>
#include <algorithm>

#include <progresso/progresso.h>

namespace progresso
{

progresso::progresso(uint32_t curr, uint32_t max, uint32_t width, style st)
    : mCurrVal(curr), mMaxVal(max), mWidth(width), mStyle(st)
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
progresso::erase()
{
    // + 2 for the start and end caps.
    std::cout << '\r' << std::string(mWidth + 2, ' ') << '\r' ;
}

void 
progresso::draw(bool startOfLine)
{
    auto fillAmount = std::max(static_cast<uint32_t>(0), std::min(
            static_cast<uint32_t>(mWidth*getPercentDone()), 
            mWidth));
    auto remainAmount = mWidth-fillAmount;
    if(startOfLine) std::cout << '\r';
    std::cout << mStyle.leftCap 
            << std::string(fillAmount, mStyle.fillChar) 
            << std::string(remainAmount, mStyle.emptyChar)
            << mStyle.rightCap;
    if(startOfLine) std::cout << '\r';
    std::flush(std::cout);
}

}