#ifndef IMOVEWIDGET_H
#define IMOVEWIDGET_H

#include <QMouseEvent>
#include <QWidget>

class IMoveWidget : public QWidget
{
public:
    IMoveWidget(QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    QPoint dragPosition;
};

#endif // IMOVEWIDGET_H
