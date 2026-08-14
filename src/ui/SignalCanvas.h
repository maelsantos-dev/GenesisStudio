#pragma once

#include <QWidget>

class SignalCanvas : public QWidget
{
    public:
         explicit SignalCanvas(QWidget *parent = nullptr);
    
    protected:
        void paintEvent(QPaintEvent *event) override;
};