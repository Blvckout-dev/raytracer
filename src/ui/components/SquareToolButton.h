#ifndef SQUAREBUTTON_H
#define SQUAREBUTTON_H

#include <QToolButton>
#include <QResizeEvent>

class SquareToolButton : public QToolButton {
private:
    uint32_t prefSize { 50 };
protected:
    void resizeEvent(QResizeEvent *event) override {
        qDebug() << "QSquareButton Resize called";

        QToolButton::resizeEvent(event);
        
        if (event->size().height() == this->width())
            return;

        prefSize = event->size().height();

        qDebug() << "PrefSize: " << prefSize;

        // qDebug() << "QSquareButton Resize " << 
        //     "from  w: " << this->width() << " h: " << this->height() <<
        //     "to w: " << event->size().height() << " h: " << event->size().height();

        // resize(event->size().height(), event->size().height());
    }

    void updateStyle() {
        if (isChecked()) {
            setStyleSheet("QToolButton { background-color: #00aaff; }");
        } else {
            setStyleSheet("QToolButton { background-color: #ff0000; }");
        }
    }

public:
    SquareToolButton(QWidget *parent = nullptr) : QToolButton(parent) {
        setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        setMinimumSize(50, 50);
        setToolButtonStyle(Qt::ToolButtonIconOnly);
        setCheckable(true); // allows toggling
        // setIcon(QIcon(":/icons/myicon.png")); // use your icon
        setIconSize(QSize(128, 128)); // max size of icon
        connect(this, &QToolButton::toggled, this, &SquareToolButton::updateStyle);
    }

    bool hasHeightForWidth() const override { return true; }

    int heightForWidth(int w) const override {
        return w;
    }

    QSize sizeHint() const override {
        return QSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX);
    }
};

#endif