#include "SquareLayout.h"
#include <QWidget>

SquareLayout::SquareLayout(QWidget* parent) : QLayout(parent) {

}

SquareLayout::~SquareLayout() {
    QLayoutItem* item;
    while ((item = takeAt(0)))
        delete item;
}

void SquareLayout::addItem(QLayoutItem* item) {
    _items.append(item);
}

QSize SquareLayout::sizeHint() const {
    QSize size;
    for (QLayoutItem* item : _items)
        size += item->sizeHint();
    return size;
}

QSize SquareLayout::minimumSize() const {
    QSize size;
    for (QLayoutItem* item : _items)
        size = size.expandedTo(item->minimumSize());
    return size;
}

void SquareLayout::setGeometry(const QRect& rect) {
    QLayout::setGeometry(rect);

    Qt::LayoutDirection direction = parentWidget()->layoutDirection();
    int n = _items.size();

    if (n == 0)
        return;

    int spacing = this->spacing();
    int size = qMin(rect.width() / n - spacing, rect.height());

    int x = direction == Qt::LeftToRight ? rect.x() : rect.width() - size;
    int y = rect.y() + (rect.height() - size) / 2;

    for (int i = 0; i < n; ++i) {
        _items[i]->setGeometry(QRect(x, y, size, size));
        
        if (direction == Qt::LeftToRight)
            x += size + spacing;
        else
            x -= size + spacing;
    }
}