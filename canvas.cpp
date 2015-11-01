#include "canvas.h"
#include "ui_canvas.h"


Canvas::Canvas(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Canvas)
{
    ui->setupUi(this);
    this->editMethod = 0;
    this->ui->undoButton->setDisabled("True");
    this->ui->clearButton->setDisabled("True");
    this->ui->saveButton->setDisabled("True");
}

Canvas::~Canvas()
{
    delete ui;
}

void Canvas::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton) {
        this->mousePoint = event->pos();
        this->editPoint();
        repaint();
        qDebug()<<this->mousePoint.x()<<this->mousePoint.y();
    }
}

void Canvas::paintEvent(QPaintEvent *)
{
    paint = new QPainter;
    paint->begin(this);
    paint->setPen(QPen(QColor(150, 150, 150), 2));
    paint->drawRect(25, 80, 750, 280);

    paint->setPen(QPen(QColor(255, 0, 0), 2));
    for(int i = 0; i < this->begin_shape.point.size(); i ++){
        paint->drawEllipse(this->begin_shape.point[i], 2, 2);
    }
    paint->setPen(QPen(QColor(255, 255, 0), 2));
    for(int i = 1; i < this->begin_shape.point.size(); i ++) {
        paint->drawLine(this->begin_shape.point[i-1], this->begin_shape.point[i]);
    }

    paint->setPen(QPen(QColor(0, 0, 255), 2));
    for(int i = 0; i < this->end_shape.point.size(); i ++){
        paint->drawEllipse(this->end_shape.point[i], 2, 2);
    }
    paint->setPen(QPen(QColor(0, 255, 255), 2));
    for(int i = 1; i < this->end_shape.point.size(); i ++) {
        paint->drawLine(this->end_shape.point[i-1], this->end_shape.point[i]);
    }


}

void Canvas::editPoint()
{
    if(this->mousePoint.x() > 25 && this->mousePoint.x() < 775 && this->mousePoint.y() > 80 && this->mousePoint.y() < 360){
        if(this->editMethod == 1)
            this->begin_shape.add_point(this->mousePoint);
        if(this->editMethod == 2)
            this->end_shape.add_point(this->mousePoint);
    }
}

void Canvas::on_beginButton_clicked()
{
    this->editMethod = 1;
    this->ui->endButton->setDisabled("True");
    this->ui->undoButton->setEnabled("True");
    this->ui->clearButton->setEnabled("True");
    this->ui->saveButton->setEnabled("True");

}

void Canvas::on_endButton_clicked()
{
    this->editMethod = 2;
    this->ui->beginButton->setDisabled("True");
    this->ui->undoButton->setEnabled("True");
    this->ui->clearButton->setEnabled("True");
    this->ui->saveButton->setEnabled("True");
}

void Canvas::on_saveButton_clicked()
{
    this->ui->saveButton->setDisabled("True");
    this->ui->undoButton->setDisabled("True");
    this->ui->clearButton->setDisabled("True");
    this->editMethod = 0;
    this->ui->beginButton->setEnabled("True");
    this->ui->endButton->setEnabled("True");
}

void Canvas::on_undoButton_clicked()
{
    if(this->editMethod == 1) this->begin_shape.undo();
    if(this->editMethod == 2) this->end_shape.undo();
    repaint();
}

void Canvas::on_clearButton_clicked()
{
    if(this->editMethod == 1) this->begin_shape.clear();
    if(this->editMethod == 2) this->end_shape.clear();
    repaint();
}
