#include "AmpKnob.h"

#include <QPainter>
#include <QMouseEvent>
#include <QtMath>

AmpKnob::AmpKnob(QWidget *parent)
    : QWidget(parent)
{
    setFixedSize(64, 64);
    setMouseTracking(true);
}

int AmpKnob::value() const
{
    return m_value;
}

void AmpKnob::setValue(int value)
{
    value = qBound(0, value, 100);

    if (m_value == value)
        return;

    m_value = value;

    update();
    emit valueChanged(m_value);
}

void AmpKnob::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    const QPointF center(width() / 2.0, height() / 2.0);
    const qreal radius = 24.0;

    // Corpo externo
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor("#15191f"));
    painter.drawEllipse(center, radius, radius);

    // Corpo interno
    painter.setBrush(QColor("#2c323a"));
    painter.drawEllipse(center, radius - 3, radius - 3);

    // Área superior iluminada
    painter.setBrush(QColor("#3b424c"));
    painter.drawEllipse(center, radius - 6, radius - 6);

    // Indicador de posição
    const double startAngle = 135.0;
    const double endAngle = 405.0;

    const double angle =
        startAngle + (endAngle - startAngle) * (m_value / 100.0);

    const double radians = qDegreesToRadians(angle);

    const QPointF indicatorEnd(
        center.x() + qCos(radians) * (radius - 9),
        center.y() + qSin(radians) * (radius - 9)
    );

    QPen indicatorPen(QColor("#e8ebef"));
    indicatorPen.setWidth(3);
    indicatorPen.setCapStyle(Qt::RoundCap);

    painter.setPen(indicatorPen);
    painter.drawLine(center, indicatorEnd);

    // Ponto central
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor("#0d1014"));
    painter.drawEllipse(center, 3, 3);
}

void AmpKnob::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_lastMouseY = event->position().toPoint().y();
        event->accept();
        return;
    }

    QWidget::mousePressEvent(event);
}

void AmpKnob::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        const int currentY = event->position().toPoint().y();
        const int delta = m_lastMouseY - currentY;

        if (delta != 0)
        {
            setValue(m_value + delta);
            m_lastMouseY = currentY;
        }

        event->accept();
        return;
    }

    QWidget::mouseMoveEvent(event);
}