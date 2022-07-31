#ifndef FOOD_H
#define FOOD_H
#include<QtGui>
#include<time.h>

class Food {
public:

    float radius = 0.5f;
    QPointF *position = new QPointF(0.0, 0.0);
    QColor *color = new QColor(0, 0, 0);

    QRectF *drawingRect = new QRectF(0, 0 ,0 ,0);


    Food();
    Food(float _radius, QPointF *_position);

    ~Food();

    void UpdateDrawingRect(float xoffset, float yoffset, float scale);

    float GetSquare();
    void SetSquare(float square);

    void Draw(QPainter *painter);

};

#endif // FOOD_H
