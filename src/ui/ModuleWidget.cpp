#include "ModuleWidget.h"

#include <QLabel>
#include <QVBoxLayout>
#include <QMouseEvent>



ModuleWidget::ModuleWidget(const QString &name,
                           const QString &category,
                           QWidget *parent)
    : QFrame(parent)
{
    setObjectName("moduleWidget");
    setMinimumHeight(58);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 8, 12, 8);
    layout->setSpacing(2);

    categoryLabel = new QLabel(category);
    categoryLabel->setObjectName("moduleCategory");

    nameLabel = new QLabel(name);
    nameLabel->setObjectName("moduleName");

    layout->addWidget(categoryLabel);
    layout->addWidget(nameLabel);

    setStyleSheet(R"(
        #moduleWidget {
            background-color: #252930;
            border: 1px solid #343942;
            border-radius: 5px;
        }

        #moduleWidget:hover {
            background-color: #2d323a;
            border: 1px solid #4b515c;
        }

        #moduleCategory {
            background-color: transparent;
            color: #7f8792;
            font-size: 9px;
            font-weight: bold;
        }

        #moduleName {
            background-color: transparent;
            color: #e8ebef;
            font-size: 12px;
            font-weight: bold;
        }
    )");
}

void ModuleWidget::mousePressEvent(QMouseEvent *event)
    {
        if (event->button() == Qt::LeftButton)
        {
            dragOffset = event->position().toPoint();
            event->accept();
            return;
        }

        QFrame::mousePressEvent(event);
    }

    void ModuleWidget::mouseMoveEvent(QMouseEvent *event)
    {
        if (event->buttons() & Qt::LeftButton)
        {
            QPoint newPos = pos() + event->position().toPoint() - dragOffset;

            QWidget *canvas = parentWidget();

            if (canvas)
            {
                int minX = 0;
                int minY = 0;

                // Garante que o limite nunca fique negativo
                int maxX = qMax(0, canvas->width() - width());
                int maxY = qMax(0, canvas->height() - height());

                // Mantém o módulo dentro do Signal Canvas
                newPos.setX(qBound(minX, newPos.x(), maxX));
                newPos.setY(qBound(minY, newPos.y(), maxY));

                
            }

            move(newPos);
            event->accept();
            return;
        }

        QFrame::mouseMoveEvent(event);
    }
