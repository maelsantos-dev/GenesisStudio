#include "SignalCanvas.h"
#include "ModuleWidget.h"

#include <QPainter>

SignalCanvas::SignalCanvas(QWidget *parent)
     : QWidget(parent)
{
   setObjectName("signalCanvas");

   ModuleWidget *drive =
     new ModuleWidget("OVERDRIVE", "DRIVE", this);

   drive->setParent(this);
   drive->move(60, 80);
   drive->show();  
} 

void SignalCanvas::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);

    const int reservedBotton = 160;
    const int dividerY = height() - reservedBotton;

    painter.setPen(QColor("#343942"));
    painter.drawLine(0, dividerY, width(), dividerY);

    painter.setRenderHint(QPainter::Antialiasing);

    // Fundo do Signal Canvas
    painter.fillRect(rect(), QColor("#202328"));

    // Grade sutil
    painter.setPen(QColor("#292d33"));

    const int gridSize = 32;

    for (int x = 0; x < width(); x += gridSize)
        painter.drawLine(x, 0, x, height());
    
    for (int y = 0; y < height(); y += gridSize)
        painter.drawLine(0, y, width(), y);
}