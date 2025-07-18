#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include <QEasingCurve>

namespace Ui {
    class MenuWidget;
}

class MenuWidget : public QWidget {
    Q_OBJECT
private:
    Ui::MenuWidget* _ui;

    class QPropertyAnimation* buildSlideAnimation(
        QWidget* target,
        uint32_t durationMs = 500,
        QEasingCurve easingCurve = QEasingCurve::OutCubic
    );

protected:
    void resizeEvent(QResizeEvent* event) override;

public:
    explicit MenuWidget(QWidget* parent = nullptr);
    ~MenuWidget();

    void toggleMenu();
};

#endif