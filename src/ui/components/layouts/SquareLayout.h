#ifndef SQUARELAYOUT_H
#define SQUARELAYOUT_H

#include <QLayout>
#include <QList>
#include <QWidgetItem>

class SquareLayout : public QLayout {
private:
    QList<QLayoutItem*> _items;

public:
    explicit SquareLayout(QWidget* parent = nullptr);
    SquareLayout(const SquareLayout&) = delete;
    SquareLayout& operator=(const SquareLayout&) = delete;
    ~SquareLayout() override;

    void addItem(QLayoutItem* item) override;

    int count() const override {
        return _items.size();
    }

    QLayoutItem* itemAt(int index) const override {
        return index >= 0 && index < _items.size() ? _items.at(index) : nullptr;
    }

    QLayoutItem* takeAt(int index) override {
        return index >= 0 && index < _items.size() ? _items.takeAt(index) : nullptr;
    }

    QSize sizeHint() const override;
    QSize minimumSize() const override;

    void setGeometry(const QRect& rect) override;
};

#endif // SQUARELAYOUT_H