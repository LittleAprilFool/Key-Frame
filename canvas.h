#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QPainter>
#include <QDebug>
#include <QMouseEvent>

#include "shape.h"

namespace Ui {
class Canvas;
}

class Canvas : public QWidget
{
    Q_OBJECT

public:
    explicit Canvas(QWidget *parent = 0);
    ~Canvas();

protected:
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

private slots:
    void on_beginButton_clicked();

    void on_endButton_clicked();

    void on_saveButton_clicked();

    void on_undoButton_clicked();

    void on_clearButton_clicked();

private:
    Ui::Canvas *ui;
    QPainter *paint;
    void paintEvent(QPaintEvent *);
    QPoint mousePoint;
    Shape begin_shape;
    Shape end_shape;
    int editMethod;
    int interMethod;
    int timeMethod;
    int time;
    void editPoint();
    void paintBeginShape();
    void paintEndShape();
};

#endif // CANVAS_H
