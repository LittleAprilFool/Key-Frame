#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QPainter>
#include <QDebug>

#incllude "shape.h"

namespace Ui {
class Canvas;
}

class Canvas : public QWidget
{
    Q_OBJECT

public:
    explicit Canvas(QWidget *parent = 0);
    ~Canvas();

private:
    Ui::Canvas *ui;
    QPainter *paint;
    void paintEvent(QPaintEvent *);
};

#endif // CANVAS_H
