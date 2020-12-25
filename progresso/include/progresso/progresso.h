#pragma once

#include <cstdint>
#include <vector>

namespace progresso
{

constexpr const char ResetColor[]   = "\033[0m";
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

// TODO: Add background colors.

struct style {
    std::string leftCap    = "[";
    std::string rightCap   = "]";
    std::string doneChar   = "=";
    std::vector<std::string> fillChars = {"="};
    std::string emptyChar  = ".";

    bool colorize   = true;
    const char* capColor   = BlueColor;
    const char* fillColor  = BoldGreenColor;
    const char* emptyColor = GrayColor;
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
        u8"\u2589", // Full block
        { u8"\u258f", u8"\u258d", u8"\u258b", u8"\u2589"}, 
        u8"\u2589", // Full block,
        true,
        BoldWhiteColor,
        BoldGreenColor,
        BoldRedColor};
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
    uint32_t mCurrVal = 0, mMaxVal = 100;
    uint32_t mWidth = 40;
    style mStyle;

    // TODO: Change to Value Display Style.
    bool mShowPercentage = true;

    // TODO: Add suffix for value case (e.g. MB)
    std::string mValueSuffix;

    int fullAmountDone() const;
    float fractionalPortionDone() const;
    int fractionalCharIndex() const;
    int emptyAmountLeft() const;

public:
    progresso(uint32_t curr, uint32_t max, uint32_t width, bool percentage, style st);
    
    uint32_t getTotal() const { return mMaxVal; }
    void setTotal(uint32_t max) { mMaxVal = max; }

    void setValue(uint32_t value) { mCurrVal = value; }
    uint32_t getValue() const { return mCurrVal; }

    void tick(uint32_t amount=1);

    float getPercentDone() const;
    void erase();
    void draw(bool startOfLine=true);
};

}
