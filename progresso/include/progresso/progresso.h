#pragma once

#include <cstdint>
#include <vector>

namespace progresso
{

namespace color
{
    constexpr const char ResetColor[]   = "\033[0m";

namespace foreground
{
    constexpr const char BlackColor[]     = "\033[30m";
    constexpr const char RedColor[]     = "\033[31m";
    constexpr const char GreenColor[]   = "\033[32m";
    constexpr const char YellowColor[]  = "\033[33m";
    constexpr const char BlueColor[]    = "\033[34m";
    constexpr const char MagentaColor[] = "\033[35m";
    constexpr const char CyanColor[]    = "\033[36m";
    constexpr const char WhiteColor[]   = "\033[37m";

    constexpr const char GrayColor[]       = "\033[90m";
    constexpr const char BoldRedColor[]    = "\033[91m";
    constexpr const char BoldGreenColor[]  = "\033[92m";
    constexpr const char BoldYellowColor[] = "\033[93m";
    constexpr const char BoldBlueColor[]   = "\033[94m";
    constexpr const char BoldMagentaColor[]= "\033[95m";
    constexpr const char BoldCyanColor[]   = "\033[96m";
    constexpr const char BoldWhiteColor[]  = "\033[97m";

    // std::string color256(uint8_t which) {
    //     return std::string("\u001b[38;5;") + std::to_string(which) + "m";
    // }
} // foreground

namespace background
{
    constexpr const char BlackColor[]     = "\033[40m";
    constexpr const char RedColor[]     = "\033[41m";
    constexpr const char GreenColor[]   = "\033[42m";
    constexpr const char YellowColor[]  = "\033[43m";
    constexpr const char BlueColor[]    = "\033[44m";
    constexpr const char MagentaColor[] = "\033[45m";
    constexpr const char CyanColor[]    = "\033[46m";
    constexpr const char WhiteColor[]   = "\033[47m";

    constexpr const char GrayColor[]       = "\033[40;1m";
    constexpr const char BoldRedColor[]    = "\033[41;1m";
    constexpr const char BoldGreenColor[]  = "\033[42;1m";
    constexpr const char BoldYellowColor[] = "\033[43;1m";
    constexpr const char BoldBlueColor[]   = "\033[44;1m";
    constexpr const char BoldMagentaColor[]= "\033[45;1m";
    constexpr const char BoldCyanColor[]   = "\033[46;1m";
    constexpr const char BoldWhiteColor[]  = "\033[47;1m";

    // std::string color256(uint8_t which) {
    //     return std::string("\u001b[48;5;") + std::to_string(which) + "m";
    // }
} // background
} // color

struct style {
    std::string leftCap    = "[";
    std::string rightCap   = "]";
    std::string doneChar   = "=";
    std::vector<std::string> fillChars = {"="};
    std::string emptyChar  = ".";

    bool colorize   = true;
    std::string capColor   = color::foreground::BlueColor;
    std::string capBackColor   = color::ResetColor;

    std::string fillColor  = color::foreground::BoldGreenColor;
    std::string fillBackColor  = color::ResetColor;

    std::string emptyColor = color::foreground::GrayColor;
    std::string emptyBackColor  = color::ResetColor;
};

namespace styles
{
    const style BlockStyleNoBackground = {
        u8"\u2595", // Right 1/8th block
        u8"\u258f", // Left 1/8th block
        u8"\u2589", // Full block
        { u8"\u258f", u8"\u258d", u8"\u258b", u8"\u2589"}, 
        u8" "};

    const style BlockStyleFilledBackground = {
        u8"\u2595", // Right 1/8th block
        u8"\u258f", // Left 1/8th block
        u8"\u2588", // Full block
        { u8"\u258f", u8"\u258d", u8"\u258b", u8"\u2589"}, 
        u8"\u2588", // Full block,
        true,
        color::foreground::BoldWhiteColor,
        color::ResetColor,

        color::foreground::BoldGreenColor,
        color::background::RedColor,

        color::foreground::RedColor,
        color::background::RedColor};
}

enum class ValueDisplayStyle {
    None,
    Percentage,

    // Prints the current and max value, but with the max value having the suffix after.
    ValueMaxWithSuffix,

    // Prints both the current and max values with the suffix afterwards.
    ValueBothWithSuffix,
};

class progresso {
private:
    uint64_t mCurrVal = 0, mMaxVal = 100;
    uint64_t mWidth = 40;
    style mStyle;

    ValueDisplayStyle mValueDisplay = ValueDisplayStyle::Percentage;

    std::string mValueSuffix;
    uint64_t mDisplayDivisor = 1;

    int fullAmountDone() const;
    float fractionalPortionDone() const;
    int fractionalCharIndex() const;
    int emptyAmountLeft() const;

    std::string createSuffix() const;
    std::string formatValStr(float val) const;

    std::string currValStr() const;
    std::string maxValStr() const;
    
public:
    progresso(uint64_t curr, uint64_t max, uint64_t width, 
              style st,
              ValueDisplayStyle percentage = ValueDisplayStyle::Percentage, 
              uint64_t displayDivisor = 1,
              std::string valueSuffix = "");
    
    uint64_t getTotal() const { return mMaxVal; }
    void setTotal(uint64_t max) { mMaxVal = max; }

    void setValue(uint64_t value);
    uint64_t getValue() const { return mCurrVal; }

    std::string getValueSuffix() const { return mValueSuffix; }
    void setValueSuffix(std::string value) { mValueSuffix = value; }

    void tick(uint64_t amount=1);

    float getPercentDone() const;
    void erase();
    void draw(bool startOfLine=true);
};

}
