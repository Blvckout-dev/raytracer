#include "SquareLayoutWidget.h"

SquareLayoutWidget::SquareLayoutWidget(QWidget *parent) : QWidget(parent)
{
    auto layout = new SquareLayout(this);
    setLayout(layout);
}

void SquareLayoutWidget::childEvent(QChildEvent *event)
{
    if (event->added() && event->child()->isWidgetType()) {
        QWidget *childWidget = static_cast<QWidget*>(event->child());
        if (childWidget->parent() == this) {  // Ensure direct child
            layout()->addWidget(childWidget);
        }
    }
    QWidget::childEvent(event);
}
