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
    this->time = 0;
    animationTimer = new QTimer(this);
    connect(animationTimer, SIGNAL(timeout()), this, SLOT(updateAnimation()));
    animationStart = false;
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
    }
}

void Canvas::paintEvent(QPaintEvent *)
{
    paint = new QPainter;
    paint->begin(this);
    paint->setPen(QPen(QColor(150, 150, 150), 2));
    paint->drawRect(25, 80, 750, 280);

    paint->setPen(QPen(QColor(0, 255, 255), 2));
    for(int i = 0; i < this->begin_shape.point.size(); i ++){
        paint->drawEllipse(this->begin_shape.point[i], 2, 2);
    }
    paint->setPen(QPen(QColor(255, 0, 0), 2));
    for(int i = 1; i < this->begin_shape.point.size(); i ++) {
        paint->drawLine(this->begin_shape.point[i-1], this->begin_shape.point[i]);
    }

    paint->setPen(QPen(QColor(255, 0, 255), 2));
    for(int i = 0; i < this->end_shape.point.size(); i ++){
        paint->drawEllipse(this->end_shape.point[i], 2, 2);
    }
    paint->setPen(QPen(QColor(0, 255, 0), 2));
    for(int i = 1; i < this->end_shape.point.size(); i ++) {
        paint->drawLine(this->end_shape.point[i-1], this->end_shape.point[i]);
    }

    paint->setPen(QPen(QColor(255, 255, 0), 2));
    for(int i = 0; i < this->inter_shape.point.size(); i ++){
        paint->drawEllipse(this->inter_shape.point[i], 2, 2);
    }
    paint->setPen(QPen(QColor(0, 0, 255), 2));
    for(int i = 1; i < this->inter_shape.point.size(); i ++) {
        paint->drawLine(this->inter_shape.point[i-1], this->inter_shape.point[i]);
    }
    paint->~QPainter();
}

void Canvas::updateAnimation()
{
    if(this->interMethod == 0){
        this->inter_shape.clear();
        float val = (float)this->time / this->num_time;
        if(this->timeMethod == 1) val = 1 - qCos(3.14 * val / 2);
        if(this->timeMethod == 2) val = qSin(3.14 * val / 2);
        qDebug()<<val;
        for(int i = 0; i < this->begin_shape.point.size(); i ++)
            this->inter_shape.add_point((1-val) * this->begin_shape.point[i] + val * this->end_shape.point[i]);
    }
    this->time++;
    if(this->time > this->num_time) {
        this->time = 0;
    }

    qDebug("haha");

    repaint();
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


void Canvas::on_startButton_clicked()
{
    if(!animationStart)
    {
        this->interMethod = this->ui->interpolationType->currentIndex();
        this->timeMethod = this->ui->timingFunction->currentIndex();

        this->total_time = this->ui->totalTime->text().toInt();
        this->num_time = this->total_time * 100 / 5;
        animationTimer->start(5);
        animationStart = true;
        this->ui->startButton->setText("Stop Animation");
    }
    else
    {
        animationStart = false;
        if(animationTimer->isActive()) animationTimer->stop();
        this->ui->startButton->setText("Start Animation");
    }
}

void Canvas::on_startButton_2_clicked()
{
    this->time = 0;
    if(animationTimer->isActive()) animationTimer->stop();
    this->inter_shape.clear();
    repaint();
}
