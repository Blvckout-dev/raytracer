#ifndef SQUARELAYOUT_H
#define SQUARELAYOUT_H

#include <QLayout>
#include <QList>
#include <QWidgetItem>

class SquareLayout : public QLayout {
private:
    QList<QLayoutItem*> items;

public:
    explicit SquareLayout(QWidget* parent = nullptr);

    ~SquareLayout() override;

    void addItem(QLayoutItem* item) override;

    int count() const override {
        return items.size();
    }

    QLayoutItem* itemAt(int index) const override {
        return index >= 0 && index < items.size() ? items.at(index) : nullptr;
    }

    QLayoutItem* takeAt(int index) override {
        return index >= 0 && index < items.size() ? items.takeAt(index) : nullptr;
    }

    QSize sizeHint() const override;
    QSize minimumSize() const override;

    void setGeometry(const QRect& rect) override;
};

#endif // SQUARELAYOUT_H