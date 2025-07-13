#ifndef SQUARELAYOUT_H
#define SQUARELAYOUT_H

#include <QLayout>
#include <QList>
#include <QWidgetItem>

class SquareLayout : public QLayout {
public:
    SquareLayout(QWidget* parent = nullptr)
        : QLayout(parent) {}

    ~SquareLayout() {
        QLayoutItem* item;
        while ((item = takeAt(0)))
            delete item;
    }

    void addItem(QLayoutItem* item) override {
        items.append(item);
    }

    int count() const override {
        return items.size();
    }

    QLayoutItem* itemAt(int index) const override {
        return index >= 0 && index < items.size() ? items.at(index) : nullptr;
    }

    QLayoutItem* takeAt(int index) override {
        return index >= 0 && index < items.size() ? items.takeAt(index) : nullptr;
    }

    QSize sizeHint() const override {
        QSize size;
        for (QLayoutItem* item : items)
            size += item->sizeHint();
        return size;
    }

    QSize minimumSize() const override {
        QSize size;
        for (QLayoutItem* item : items)
            size = size.expandedTo(item->minimumSize());
        return size;
    }

    void setGeometry(const QRect& rect) override {
        QLayout::setGeometry(rect);

        int n = items.size();

        if (n == 0)
            return;

        int spacing = this->spacing();
        int totalSpacing = spacing * (n - 1);

        int availableWidth = rect.width() - totalSpacing;
        int width = availableWidth / n;
        int size = qMin(width, rect.height());  // force square

        int x = rect.x();
        int y = rect.y(); // + (rect.height() - size) / 2;

        for (int i = 0; i < n; ++i) {
            QLayoutItem* item = items[i];
            item->setGeometry(QRect(x, y, size, size));
            x += size + spacing;
        }
    }

private:
    QList<QLayoutItem*> items;
};

#endif // SQUARELAYOUT_H