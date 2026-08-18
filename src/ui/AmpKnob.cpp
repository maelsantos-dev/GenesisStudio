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
    painter.setRenderHint(QPainter::Antialiasing, true);

    const QPointF center(width() / 2.0, height() / 2.0);
    const qreal radius = 25.0;

    // ======================================================
    // SOMBRA EXTERNA
    // ======================================================
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor("#090b0f"));
    painter.drawEllipse(center + QPointF(1.5, 2.5),
                        radius + 1,
                        radius + 1);
    
    // ======================================================
    // CORPO PRINCIPAL
    // ======================================================
    QRadialGradient bodyGradient(
        center - QPointF(7, 8),
        radius + 4
    );

    bodyGradient.setColorAt(0.0, QColor("#f5f7fa"));
    bodyGradient.setColorAt(0.35, QColor("#d9dee5"));
    bodyGradient.setColorAt(0.72, QColor("#aeb6c1"));
    bodyGradient.setColorAt(1.0, QColor("#626b77"));

    painter.setBrush(bodyGradient);
    painter.drawEllipse(center, radius, radius);

    // ===========================================================
    // BORDA EXTERNA
    // ============================================================
    

    // ===========================================================
    // ÁREA INTERNA
    // ===========================================================
    painter.setPen(QPen(QColor("#69727e"), 1.0));

    QRadialGradient innerGradient(
        center - QPointF(5, 6),
        radius - 3
    );

    innerGradient.setColorAt(0.0, QColor("#727b87"));
    innerGradient.setColorAt(0.5, QColor("#414953"));
    innerGradient.setColorAt(1.0, QColor("#20262e"));

    painter.setBrush(innerGradient);
    painter.drawEllipse(center, radius - 3, radius - 3);

    // ======================================================
    // SUPERFÍCIE DO KNOB
    // ======================================================
    painter.setPen(Qt::NoPen);

    QRadialGradient surfaceGradient(
        center - QPointF(5, 7),
        radius - 7
    );

    surfaceGradient.setColorAt(0.0, QColor("#aeb6c0"));
    surfaceGradient.setColorAt(0.25, QColor("#7f8995"));
    surfaceGradient.setColorAt(0.65, QColor("#4b545f"));
    surfaceGradient.setColorAt(1.0, QColor("#272d35"));

    painter.setBrush(surfaceGradient);
    painter.drawEllipse(center, radius - 7, radius - 7);

    // =========================================================
    // ARCO DE POSIÇÃO
    // =========================================================

    const QRectF arcRect(
        center.x() - radius + 5,
        center.y() - radius + 5,
        (radius - 5) * 2,
        (radius - 5) * 2
    );

    QPen arcPen(QColor("#8f98a4"), 2.0);
    arcPen.setCapStyle(Qt::RoundCap);

    painter.setPen(arcPen);

    const int startAngle = 135 * 16;
    const int spanAngle = 270 * 16;

    painter.drawArc(arcRect, startAngle, spanAngle);

    // ===========================================================
    // INDICADOR
    // ===========================================================

    const double angle = 
       135.0 + 270.0 * (m_value / 100.0);

    const double radians = qDegreesToRadians(angle);

    const QPointF indicatorEnd(
        center.x() + qCos(radians) * (radius - 10),
        center.y() + qSin(radians) * (radius - 10)
    );

    QPen indicatorPen(QColor("#f1f3f5"));
    indicatorPen.setCapStyle(Qt::RoundCap);

    painter.setPen(indicatorPen);
    painter.drawLine(center, indicatorEnd);

    // ===========================================
    // CENTRO METÁLICO
    // ===========================================

    QRadialGradient centerGradient(
        center - QPointF(2, 2), 4
    );

    centerGradient.setColorAt(0.0, QColor("#d8dde2"));
    centerGradient.setColorAt(0.45, QColor("#8b949e"));
    centerGradient.setColorAt(1.0, QColor("#30363e"));

    painter.setPen(Qt::NoPen);
    painter.setBrush(centerGradient);

    painter.drawEllipse(center, 3.5, 3.5);

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