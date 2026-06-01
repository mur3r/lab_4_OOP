#pragma once
#include "ClockBase.h"

// аналоговий годинник: малює стрілки та циферблат
public ref class AnalogClock : public ClockBase {
private:
    System::Drawing::Point center;
    int radius;

    void DrawFace(Graphics^ g);
    void DrawMarkers(Graphics^ g);
    void DrawNumbers(Graphics^ g);
    void DrawHand(Graphics^ g, Pen^ pen, float angleDeg, int length);

public:
    AnalogClock(System::Drawing::Point center, int radius);
    void SetGeometry(System::Drawing::Point center, int radius);
    virtual void Draw(Graphics^ g) override;
};
