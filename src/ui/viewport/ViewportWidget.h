#ifndef VIEWPORTWIDGET_H
#define VIEWPORTWIDGET_H

#include <QWidget>
#include <QLabel>

namespace Ui {
    class ViewportWidget;
}

class ViewportWidget : public QWidget {
    Q_OBJECT
private:
    Ui::ViewportWidget* _ui;

    QLabel* _renderImage;
public:
    explicit ViewportWidget(QWidget* parent = nullptr);
    ViewportWidget(const ViewportWidget&) = delete;
    ViewportWidget& operator=(const ViewportWidget&) = delete;
    ~ViewportWidget();

    QLabel* getRenderImage() const;
};

#endif