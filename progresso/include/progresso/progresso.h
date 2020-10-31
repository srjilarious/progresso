#pragma once

#include <cstdint>

namespace progresso
{

struct style {
    char leftCap    = '[';
    char rightCap   = ']';
    char fillChar   = '=';
    char emptyChar  = '.';

};

class progresso {
private:
    uint32_t mCurrVal = 0, mMaxVal = 100;
    uint32_t mWidth = 40;
    style mStyle;

public:
    progresso(uint32_t curr, uint32_t max, uint32_t width, style st);
    void setTotal(uint32_t max) { mMaxVal = max; }
    void setValue(uint32_t value) { mCurrVal = value; }
    uint32_t getValue() const { return mCurrVal; }
    void tick(uint32_t amount=1);

    float getPercentDone() const;
    void draw(bool startOfLine=true);
};

}
