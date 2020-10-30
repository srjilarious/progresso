#pragma once

#include <cstdint>

namespace progresso
{


class progresso {
private:
    uint32_t mCurrVal = 0, mMaxVal = 100;

public:
    progresso(uint32_t curr, uint32_t max);
    void setTotal(uint32_t max) { mMaxVal = max; }
    void setValue(uint32_t value) { mCurrVal = value; }
    uint32_t getValue() const { return mCurrVal; }
    void tick(uint32_t amount=1);

    float getPercentDone() const;
    void draw(bool startOfLine=true);
};

}
