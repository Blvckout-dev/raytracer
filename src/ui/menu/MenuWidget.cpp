#include "MenuWidget.h"
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include "ui_MenuWidget.h"

MenuWidget::MenuWidget(QWidget *parent) :
    QWidget(parent),
    _ui(new Ui::MenuWidget)
{
    _ui->setupUi(this);

    _ui->menuOptionsWidget->setVisible(false);
    _ui->menuDetailWidget->setVisible(false);

    connect(_ui->exitButton, &QToolButton::clicked, qApp, &QCoreApplication::quit);
}

MenuWidget::~MenuWidget()
{
    delete _ui;
}

QPropertyAnimation* MenuWidget::buildSlideAnimation(
    QWidget* target,
    uint32_t durationMs,
    QEasingCurve easingCurve
)
{
    QPropertyAnimation* animation = new QPropertyAnimation(target, "geometry");
    animation->setDuration(durationMs);

    QRect expandedRect = target->parentWidget()->contentsRect();

    QRect collapsedRect;

    // Shift upwards
    collapsedRect = expandedRect.translated(0, -expandedRect.height());

    if (target->isVisible())
    {
        animation->setStartValue(expandedRect);
        animation->setEndValue(collapsedRect);

        connect(animation, &QPropertyAnimation::finished, [target]() {
            target->setVisible(false);
        });
    }
    else
    {
        target->setGeometry(collapsedRect);
        target->setVisible(true);
        animation->setStartValue(collapsedRect);
        animation->setEndValue(expandedRect);
    }
    
    animation->setEasingCurve(easingCurve);

    return animation;
}

void MenuWidget::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);

    if (!_ui->menuOptionsWidget->isHidden()) {
        _ui->menuOptionsWidget->setGeometry(_ui->menuOptionsWidget->parentWidget()->contentsRect());
    }

    if (!_ui->menuDetailWidget->isHidden()) {
        _ui->menuDetailWidget->setGeometry(_ui->menuDetailWidget->parentWidget()->contentsRect());
    }
}

void MenuWidget::toggleMenu()
{
    QSequentialAnimationGroup* group = new QSequentialAnimationGroup(this);

    if (_ui->menuOptionsWidget->isVisible())
    {
        if (_ui->menuDetailWidget->isVisible())
            group->addAnimation(buildSlideAnimation(_ui->menuDetailWidget, 600));

        group->addAnimation(buildSlideAnimation(_ui->menuOptionsWidget, 400));
    }
    else
    {
        group->addAnimation(buildSlideAnimation(_ui->menuOptionsWidget, 400));

        if (_ui->menuDetailWidget->layout()->count())
            group->addAnimation(buildSlideAnimation(_ui->menuDetailWidget, 600));
    }

    group->start(QAbstractAnimation::DeleteWhenStopped);
}