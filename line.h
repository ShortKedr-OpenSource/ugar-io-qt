#ifndef LINE_H
#define LINE_H
#include <QtGui>

class Line {

public:

    QPointF *start = new QPointF();
    QPointF *end = new QPointF();
    QColor *color = new QColor();

    QPointF* drawableStart = new QPointF();
    QPointF* drawableEnd = new QPointF();


    Line();
    Line(QPointF *_start, QPointF *_end, QColor *_color);

    ~Line();

    void UpdateDrawableLine(float xoffset, float yoffset, float scale);

    void Draw(QPainter *painter);

};

#endif // LINE_H
