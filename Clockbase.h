#pragma once
#include <ctime>

using namespace System;
using namespace System::Drawing;

// базовий клас: зберігає поточний час
public ref class ClockBase abstract {
protected:
    int hours;
    int minutes;
    int seconds;

public:
    ClockBase();

    virtual void Update();

    // нащадки самі малюють себе
    virtual void Draw(Graphics^ g) = 0;

    property int Hours{ int get() { return hours; } }
    property int Minutes{ int get() { return minutes; } }
    property int Seconds{ int get() { return seconds; } }
};
