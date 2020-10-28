#pragma once

#include <
namespace progresso
{

#include <cstdint>

class progresso {
private:
    uint32_t mCurrVal = 0, mMaxVal = 100;

public:
    void setTotal(uint32_t max);
    void setValue(uint32_t value);
    void getValue(uint32_t value) const;
    void tick(uint32_t amount=1);

    float getPercentDone() const;
    void draw();
};

}
