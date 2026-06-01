#include "DigitalClock.h"

DigitalClock::DigitalClock(System::Drawing::Rectangle bounds)
    : ClockBase() {
    this->bounds = bounds;
}

void DigitalClock::SetBounds(System::Drawing::Rectangle bounds) {
    this->bounds = bounds;
}

void DigitalClock::Draw(Graphics^ g) {
    // розмір не готовий — не малюємо
    if (bounds.Width <= 0 || bounds.Height <= 0) return;

    // темний фон дисплея
    g->FillRectangle(
        gcnew SolidBrush(Color::FromArgb(18, 18, 28)),
        bounds);

    // підсвічення меж
    g->DrawRectangle(
        gcnew Pen(Color::FromArgb(45, 45, 65), 1),
        bounds.X, bounds.Y, bounds.Width - 1, bounds.Height - 1);

    // рядок часу з внутрішнього стану
    String^ timeStr = String::Format(
        "{0:D2}:{1:D2}:{2:D2}", hours, minutes, seconds);

    float       fs = bounds.Height * 0.38f;
    if (fs < 1.0f) return;

    Font^ font = gcnew Font("Consolas", fs, FontStyle::Bold);
    SolidBrush^ br = gcnew SolidBrush(Color::FromArgb(0, 220, 110));

    SizeF  sz = g->MeasureString(timeStr, font);
    float  x = bounds.X + (bounds.Width - sz.Width) / 2.0f;
    float  y = bounds.Y + (bounds.Height - sz.Height) / 2.0f;
    g->DrawString(timeStr, font, br, x, y);
}
