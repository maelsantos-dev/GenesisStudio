#ifndef AMPKNOB_H
#define AMPKNOB_H

#include <QWidget>
#include <QMouseEvent>
#include <QPainter>

class AmpKnob : public QWidget
{
    Q_OBJECT

public:
    explicit AmpKnob(QWidget *parent = nullptr);

    int value() const;
    void setValue(int value);

signals:
    void valueChanged(int value);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private:
   int m_value = 50;
   int m_lastMouseY = 0;
};

#endif // AMPKNOB_H