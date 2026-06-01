#pragma once
#include "AnalogClock.h"
#include "DigitalClock.h"

namespace ClockApp {

    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;
    using namespace System::ComponentModel;

    // панель з подвійною буферизацією
    ref class SmoothPanel : public Panel {
    public:
        SmoothPanel() {
            this->DoubleBuffered = true;
        }
    };

    public ref class MyForm : public Form {
    private:
        array<ClockBase^>^ clocks;
        SmoothPanel^ drawPanel;
        System::Windows::Forms::Timer^ timer;
        System::ComponentModel::Container^ components;

        void InitializeClocks() {
            int w = drawPanel->Width;
            int h = drawPanel->Height;
            int cx = w / 2;
            int cy = (h - 80) / 2;
            int r = Math::Min(cx - 15, cy - 15);

            // панель ще не має правильного розміру — чекаємо
            if (r <= 0) return;

            if (clocks == nullptr) {
                clocks = gcnew array<ClockBase^>(2);
                clocks[0] = gcnew AnalogClock(Point(cx, cy), r);
                clocks[1] = gcnew DigitalClock(
                    Rectangle(0, h - 75, w, 75));
            }
            else {
                // оновлюємо геометрію при зміні розміру
                safe_cast<AnalogClock^>(clocks[0])->SetGeometry(Point(cx, cy), r);
                safe_cast<DigitalClock^>(clocks[1])->SetBounds(
                    Rectangle(0, h - 75, w, 75));
            }
        }

        //!!!!!! обробники подій (лише виклики методів класів) !!!!!! 

        // Shown спрацьовує після того як DockStyle::Fill вже застосований
        void MyForm_Shown(Object^ sender, EventArgs^ e) {
            InitializeClocks();
            timer->Start();
        }

        void timer_Tick(Object^ sender, EventArgs^ e) {
            for each (ClockBase ^ c in clocks) c->Update();
            drawPanel->Invalidate();
        }

        void drawPanel_Paint(Object^ sender, PaintEventArgs^ e) {
            // ліниве ініціалізування на випадок якщо Shown ще не спрацював
            if (clocks == nullptr) {
                InitializeClocks();
                if (clocks == nullptr) return;
            }
            for each (ClockBase ^ c in clocks) c->Draw(e->Graphics);
        }

    public:
        MyForm() {
            clocks = nullptr;
            components = nullptr;
            InitializeComponent();
        }

    protected:
        ~MyForm() {
            if (components) delete components;
        }

    private:
        void InitializeComponent() {
            drawPanel = gcnew SmoothPanel();
            timer = gcnew System::Windows::Forms::Timer();

            this->SuspendLayout();

            // панель малювання
            drawPanel->Dock = DockStyle::Fill;
            drawPanel->BackColor = Color::FromArgb(238, 238, 244);
            drawPanel->Paint += gcnew PaintEventHandler(this, &MyForm::drawPanel_Paint);

            // таймер
            timer->Interval = 100;
            timer->Tick += gcnew EventHandler(this, &MyForm::timer_Tick);

            // форма
            this->Text = L"Годинник";
            this->ClientSize = System::Drawing::Size(430, 510);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
            this->MaximizeBox = false;
            this->BackColor = Color::FromArgb(238, 238, 244);
            this->Shown += gcnew EventHandler(this, &MyForm::MyForm_Shown);
            this->Controls->Add(drawPanel);

            this->ResumeLayout(false);
        }
    };

}
