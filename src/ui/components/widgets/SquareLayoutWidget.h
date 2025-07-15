#ifndef SQUAREWIDGET_H
#define SQUAREWIDGET_H

#include "SquareLayout.h"
#include <QWidget>
#include <QTimer>

class SquareLayoutWidget : public QWidget {
    Q_OBJECT
public:
    explicit SquareLayoutWidget(QWidget* parent = nullptr) : QWidget(parent) {
        auto layout = new SquareLayout(this);
        setLayout(layout);

        // Defer widget registration until after construction finishes
        QTimer::singleShot(0, this, [this, layout]() {
            const auto& children = this->findChildren<QWidget*>(QString(), Qt::FindDirectChildrenOnly);
            for (QWidget* child : children) {
                layout->addWidget(child);
            }
        });
    }
};

#endif