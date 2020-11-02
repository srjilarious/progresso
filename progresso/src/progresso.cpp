
#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>


#include <progresso/progresso.h>

namespace progresso
{

progresso::progresso(
        uint32_t curr, 
        uint32_t max, 
        uint32_t width, 
        bool percentage,
        style st
    )
    : mCurrVal(curr), 
      mMaxVal(max), 
      mWidth(width), 
      mShowPercentage(percentage),
      mStyle(st)
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

    return 100.0f*static_cast<float>(mCurrVal)/static_cast<float>(mMaxVal);
}

void 
progresso::erase()
{
    // + 2 for the start and end caps.
    uint32_t length = mWidth + 2;
    if(mShowPercentage) {
        length += 1 + 3 + 3 + 3 + 2;
    }
    std::cout << '\r' << std::string(length, ' ') << '\r' ;
}

void 
progresso::draw(bool startOfLine)
{
    auto fillAmount = std::max(static_cast<uint32_t>(0), std::min(
            static_cast<uint32_t>(mWidth*getPercentDone()/100.0f), 
            mWidth));
    auto remainAmount = mWidth-fillAmount;
    if(startOfLine) std::cout << '\r';

    if(mStyle.colorize) std::cout << mStyle.capColor;
    std::cout << mStyle.leftCap;
    if(mStyle.colorize) std::cout << mStyle.fillColor;
    std::cout << std::string(fillAmount, mStyle.fillChar);
    if(mStyle.colorize) std::cout << mStyle.emptyColor;
    std::cout << std::string(remainAmount, mStyle.emptyChar);
    if(mStyle.colorize) std::cout << mStyle.capColor;
    std::cout << mStyle.rightCap;
    if(mStyle.colorize) std::cout << ResetColor;
    
    if(mShowPercentage) {
        std::cout << " " << std::setprecision(4) << getPercentDone() 
                  << " / 100 %";
    }

    if(startOfLine) std::cout << '\r';
    std::flush(std::cout);
}

}