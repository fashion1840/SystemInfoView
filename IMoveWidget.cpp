#include "IMoveWidget.h"
#include <QApplication>
#include <QDesktopWidget>

IMoveWidget::IMoveWidget(QWidget *parent) : QWidget(parent) {}

void IMoveWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        dragPosition = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    }
}

void IMoveWidget::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event)

    if (this->geometry().y() < QApplication::desktop()->geometry().top())
    {
        move(geometry().x(), QApplication::desktop()->geometry().top());
    }
}

void IMoveWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        move(event->globalPos() - dragPosition);
    }
}
