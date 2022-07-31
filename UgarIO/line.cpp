#include "line.h"

Line::Line()
{

}

Line::Line(QPointF *_start, QPointF *_end, QColor *_color)
{
    *start = *_start;
    *end =*_end;
    *color = *_color;
}

Line::~Line()
{
    delete start;
    delete end;
    delete color;
    delete drawableEnd;
    delete drawableStart;
}

void Line::UpdateDrawableLine(float xoffset, float yoffset, float scale)
{
    drawableStart->setX((start->x()*scale)-xoffset);
    drawableStart->setY((start->y()*scale)-yoffset);

    drawableEnd->setX((end->x()*scale)-xoffset);
    drawableEnd->setY((end->y()*scale)-yoffset);
}

void Line::Draw(QPainter *painter)
{
    QPen *pen = new QPen(*color);
    painter->setPen(*pen);
    painter->drawLine(*drawableStart, *drawableEnd);
    delete pen;
}
