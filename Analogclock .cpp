#include "AnalogClock.h"
#include <cmath>

using namespace System::Drawing::Drawing2D;

static const float PI_F = 3.14159265f;

AnalogClock::AnalogClock(System::Drawing::Point center, int radius)
    : ClockBase() {
    this->center = center;
    this->radius = radius;
}

void AnalogClock::SetGeometry(System::Drawing::Point center, int radius) {
    this->center = center;
    this->radius = radius;
}

void AnalogClock::DrawHand(Graphics^ g, Pen^ pen, float angleDeg, int length) {
    float rad = (angleDeg - 90.0f) * PI_F / 180.0f;
    int x = center.X + (int)(cosf(rad) * length);
    int y = center.Y + (int)(sinf(rad) * length);
    pen->StartCap = LineCap::Round;
    pen->EndCap = LineCap::Round;
    g->DrawLine(pen, center.X, center.Y, x, y);
}

void AnalogClock::DrawFace(Graphics^ g) {
    // темна рамка
    g->FillEllipse(
        gcnew SolidBrush(Color::FromArgb(45, 45, 65)),
        center.X - radius - 8, center.Y - radius - 8,
        (radius + 8) * 2, (radius + 8) * 2);

    // фон циферблату
    g->FillEllipse(
        gcnew SolidBrush(Color::FromArgb(250, 250, 250)),
        center.X - radius, center.Y - radius,
        radius * 2, radius * 2);
}

void AnalogClock::DrawMarkers(Graphics^ g) {
    // дрібні та великі поділки
    for (int i = 0; i < 60; i++) {
        float rad = (i * 6.0f - 90.0f) * PI_F / 180.0f;
        bool isHour = (i % 5 == 0);
        int outer = radius - 3;
        int inner = outer - (isHour ? 14 : 6);
        int x1 = center.X + (int)(cosf(rad) * outer);
        int y1 = center.Y + (int)(sinf(rad) * outer);
        int x2 = center.X + (int)(cosf(rad) * inner);
        int y2 = center.Y + (int)(sinf(rad) * inner);
        g->DrawLine(
            gcnew Pen(Color::FromArgb(55, 55, 75), isHour ? 2.0f : 1.0f),
            x1, y1, x2, y2);
    }
}

void AnalogClock::DrawNumbers(Graphics^ g) {
    float fontSize = (float)radius * 0.12f;
    // захист від некоректного розміру шрифту
    if (fontSize < 1.0f) return;

    Font^ f = gcnew Font("Arial", fontSize, FontStyle::Bold);
    SolidBrush^ br = gcnew SolidBrush(Color::FromArgb(45, 45, 65));

    for (int i = 1; i <= 12; i++) {
        float   rad = (i * 30.0f - 90.0f) * PI_F / 180.0f;
        float   r = radius * 0.77f;
        float   x = center.X + cosf(rad) * r;
        float   y = center.Y + sinf(rad) * r;
        String^ s = i.ToString();
        SizeF   sz = g->MeasureString(s, f);
        g->DrawString(s, f, br, x - sz.Width / 2.0f, y - sz.Height / 2.0f);
    }
}

void AnalogClock::Draw(Graphics^ g) {
    // розмір не готовий — не малюємо
    if (radius <= 0) return;

    g->SmoothingMode = SmoothingMode::AntiAlias;
    g->TextRenderingHint = System::Drawing::Text::TextRenderingHint::AntiAlias;

    DrawFace(g);
    DrawMarkers(g);
    DrawNumbers(g);

    // кути стрілок залежать від внутрішнього стану
    float sAngle = seconds * 6.0f;
    float mAngle = minutes * 6.0f + seconds * 0.1f;
    float hAngle = (hours % 12) * 30.0f + minutes * 0.5f;

    DrawHand(g, gcnew Pen(Color::FromArgb(45, 45, 65), 5.0f), hAngle, (int)(radius * 0.50f));
    DrawHand(g, gcnew Pen(Color::FromArgb(45, 45, 65), 3.0f), mAngle, (int)(radius * 0.70f));
    DrawHand(g, gcnew Pen(Color::Crimson, 1.5f), sAngle, (int)(radius * 0.82f));

    // хвіст секундної стрілки
    float sRad = (sAngle - 90.0f) * PI_F / 180.0f;
    int   tx = center.X - (int)(cosf(sRad) * radius * 0.18f);
    int   ty = center.Y - (int)(sinf(sRad) * radius * 0.18f);
    g->DrawLine(gcnew Pen(Color::Crimson, 2.0f), center.X, center.Y, tx, ty);

    // центральна точка
    int cr = 6;
    g->FillEllipse(
        gcnew SolidBrush(Color::Crimson),
        center.X - cr, center.Y - cr, cr * 2, cr * 2);
    g->FillEllipse(
        gcnew SolidBrush(Color::FromArgb(45, 45, 65)),
        center.X - 2, center.Y - 2, 4, 4);
}
