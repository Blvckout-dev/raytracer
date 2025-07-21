#ifndef SQUAREWIDGET_H
#define SQUAREWIDGET_H

#include "SquareLayout.h"
#include <QWidget>

class SquareLayoutWidget : public QWidget {
    Q_OBJECT
protected:
    void childEvent(QChildEvent *event) override;
public:
    explicit SquareLayoutWidget(QWidget* parent = nullptr);
};

#endif