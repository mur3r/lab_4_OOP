#pragma once
#pragma once
#include "ClockBase.h"

// цифровий годинник
public ref class DigitalClock : public ClockBase {
private:
    System::Drawing::Rectangle bounds;

public:
    DigitalClock(System::Drawing::Rectangle bounds);
    void SetBounds(System::Drawing::Rectangle bounds);
    virtual void Draw(Graphics^ g) override;
};
