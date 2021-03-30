
#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>
#include <sstream>

#include <progresso/progresso.h>

namespace
{
    constexpr const char HideCursor[]       = "\033[?25l";
    constexpr const char ShowCursor[]       = "\033[?25h";
}

namespace progresso
{

progresso::progresso(
        uint64_t curr, 
        uint64_t max, 
        uint64_t width,
        style st,
        ValueDisplayStyle display,
        uint64_t displayDivisor, 
        std::string valueSuffix
    )
    : mCurrVal(curr), 
      mMaxVal(max), 
      mWidth(width), 
      mStyle(st),
      mValueDisplay(display),
      mDisplayDivisor(displayDivisor),
      mValueSuffix(valueSuffix)
{

}

void 
progresso::tick(uint64_t amount)
{
    mCurrVal = std::max(static_cast<uint64_t>(0), 
            std::min(static_cast<uint64_t>(mCurrVal+amount), static_cast<uint64_t>(mMaxVal)));
}

void 
progresso::setValue(uint64_t value)
{
    mCurrVal = std::max(static_cast<uint64_t>(0), 
            std::min(static_cast<uint64_t>(value), static_cast<uint64_t>(mMaxVal)));
}

float 
progresso::getPercentDone() const
{
    if(mMaxVal == 0) return 0.0f;

    return 100.0f*fractionalPortionDone();
}

void 
progresso::erase()
{
    // + 2 for the start and end caps.
    uint64_t length = mWidth + 2;
    auto suffix = createSuffix();
    length += suffix.size();
    std::cout << '\r' << std::string(length, ' ') << '\r' ;
}

std::string
progresso::currValStr() const
{
    double divisor = mDisplayDivisor != 0 ? static_cast<double>(mDisplayDivisor) : 1.0;
    return formatValStr(static_cast<double>(mCurrVal)/static_cast<double>(divisor));
}

std::string
progresso::maxValStr() const
{
    double divisor = mDisplayDivisor != 0 ? static_cast<double>(mDisplayDivisor) : 1.0;
    return formatValStr(static_cast<double>(mMaxVal)/static_cast<double>(divisor));
}

std::string 
progresso::formatValStr(float val) const
{
    std::ostringstream valOut;
    valOut << std::setprecision(2)
            << std::fixed 
            << std::setw(5) 
            << std::setfill(' ') 
            << val;
    return valOut.str();
}

std::string 
progresso::createSuffix() const
{
    switch(mValueDisplay) 
    {
        case ValueDisplayStyle::Percentage:
            // space + 7 chars for percentage + ' / ' + '100' + ' %'
            return std::string(" ") + formatValStr(getPercentDone()) + " / 100 %";

        case ValueDisplayStyle::ValueMaxWithSuffix:
            return std::string(" ") + currValStr() + " / " + maxValStr() + " " + mValueSuffix;

        case ValueDisplayStyle::ValueBothWithSuffix:
            return std::string(" ") + currValStr() + " " + mValueSuffix + " / " + maxValStr() + " " + mValueSuffix;

        default:
        case ValueDisplayStyle::None:
            return "";
    };
}

int 
progresso::fullAmountDone() const
{
    return (mCurrVal*mWidth)/mMaxVal;
}

float 
progresso::fractionalPortionDone() const
{
    return static_cast<float>(mCurrVal)/static_cast<float>(mMaxVal);
}

int 
progresso::fractionalCharIndex() const
{
    auto fractionalVal = fractionalPortionDone()*mWidth;
    return (fractionalVal - fullAmountDone())*mStyle.fillChars.size();
}

int 
progresso::emptyAmountLeft() const
{
    return std::max(0, static_cast<int>(mWidth) - fullAmountDone());
}

void 
progresso::showCursor(bool show)
{
    if(show) {
        std::cout << ShowCursor;
    }
    else {
        std::cout << HideCursor;
    }
}

void 
progresso::draw(bool startOfLine)
{
    // auto fillAmount = std::max(static_cast<uint64_t>(0), std::min(
    //         static_cast<uint64_t>(mWidth*getPercentDone()/100.0f), 
    //         mWidth));
    //auto remainAmount = mWidth-fillAmount;
    if(startOfLine) std::cout << '\r';

    if(mStyle.colorize) std::cout << mStyle.capBackColor << mStyle.capColor;
    std::cout << mStyle.leftCap;
    if(mStyle.colorize) std::cout << mStyle.fillBackColor << mStyle.fillColor;
    for(int ii = 0; ii < fullAmountDone(); ii++) {
        std::cout << mStyle.doneChar;
    }

    if(mCurrVal >= mMaxVal) {
        std::cout << mStyle.doneChar;
    }
    else if(mStyle.fillChars.size() > 0) {
        std::cout << mStyle.fillChars[fractionalCharIndex()];
    }
    else {
        // If there are no fill chars, use the done char instead.
        std::cout << mStyle.doneChar;
    }

    auto emptyAmount = emptyAmountLeft()-1;
    if(emptyAmount > 0) {
        if(mStyle.colorize) std::cout << mStyle.emptyBackColor << mStyle.emptyColor;
        for(int ii = 0; ii < emptyAmount; ii++) {
            std::cout << mStyle.emptyChar;
        }
    }

    if(mStyle.colorize) std::cout << mStyle.capBackColor << mStyle.capColor;
    std::cout << mStyle.rightCap;
    if(mStyle.colorize) std::cout << color::ResetColor;
    
    std::cout << createSuffix();
    // if(mShowPercentage) {
    //     std::cout << " " 
    //             << std::setprecision(2)
    //             << std::fixed 
    //             << std::setw(5) 
    //             << std::setfill(' ') 
    //             << getPercentDone() 
    //             << " / 100 %";
    // }

    //if(startOfLine) std::cout << '\r';
    std::flush(std::cout);
}

}