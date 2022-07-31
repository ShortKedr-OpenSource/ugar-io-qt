#include "food.h"
#include <time.h>

Food::Food()
{

}

Food::Food(float _radius, QPointF *_position)
{
    color->setRgb(rand()%50, rand()%50, rand()%50);
    radius = _radius;
    *position = *_position;
}

Food::~Food()
{
    if (position) delete position;
    if (color) delete color;
    if (drawingRect) delete drawingRect;
}

void Food::UpdateDrawingRect(float xoffset, float yoffset, float scale) {
    drawingRect->setX((position->x() - radius) * scale - xoffset);
    drawingRect->setY((position->y() - radius) * scale - yoffset);
    drawingRect->setWidth(radius * 2.0f * scale);
    drawingRect->setHeight(radius * 2.0f * scale);
}

float Food::GetSquare()
{
    return M_PI * radius * radius;
}

void Food::SetSquare(float square)
{
    radius = sqrtf(square / (float)M_PI);
}

void Food::Draw(QPainter *painter)
{
    QPainterPath *p = new QPainterPath();
    QBrush *brush = new QBrush(*color);
    p->addEllipse(*drawingRect);
    painter->fillPath(*p, *brush);
    delete p;
    delete brush;
}

