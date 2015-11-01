#include "shape.h"

Shape::Shape()
{

}

void Shape::add_point(QPoint p)
{
    this->point.append(p);
}

void Shape::undo()
{
    this->point.pop_back();
}

void Shape::clear()
{
    this->point.clear();
}

