#ifndef VIEWPORT_H
#define VIEWPORT_H

#include <QWidget>
#include <QLabel>

namespace Ui {
    class Viewport;
}

class Viewport : public QWidget {
    Q_OBJECT
private:
    Ui::Viewport *ui;

    QLabel* _renderImage;
public:
    explicit Viewport(QWidget* parent = nullptr);

    QLabel* getRenderImage() const;
};

#endif