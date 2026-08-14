#pragma once

#include <QFrame>
#include <QString>
#include <QPoint>

class QLabel;
class QMouseEvent;

class ModuleWidget : public QFrame
{
    public:
        explicit ModuleWidget(
            const QString &name,
            const QString &category,
            QWidget *parent = nullptr
        );
    protected:
        void mousePressEvent(QMouseEvent *event) override;
        void mouseMoveEvent(QMouseEvent *event) override;

    private:
        QLabel *categoryLabel;
        QLabel *nameLabel;
    
        QPoint dragOffset;
};