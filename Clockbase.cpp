#include "ClockBase.h"

ClockBase::ClockBase() {
    Update();
}

void ClockBase::Update() {
    // читаємо системний час
    time_t t = time(nullptr);
    struct tm lt;
    localtime_s(&lt, &t);
    hours = lt.tm_hour;
    minutes = lt.tm_min;
    seconds = lt.tm_sec;
}
