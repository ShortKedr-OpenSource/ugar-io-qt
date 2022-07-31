#ifndef UGAR_H
#define UGAR_H
#include<QtGui>
#include<time.h>
#include "food.h"

class Ugar : public QObject {

    Q_OBJECT

public:

    QPointF *position = new QPointF(0.0, 0.0);

    float radius = 0.5f;
    float showedRadius = 0.5f;

    QPointF *currentSpeed = new QPointF(0.0, 0.0);
    float currentSpeedInc = 0.5f;

    QColor *color = new QColor(0, 0, 0);

    QRectF *drawingRect = new QRectF(0, 0, 0 ,0);


    Ugar();
    Ugar(QPointF *_position, float _radius);
    virtual ~Ugar();

    virtual void Update();
    void UpdateSize();
    void UpdateDrawingRect(float xoffset, float yoffset, float scale);
    void UpdateSpeedInc();

    bool CheckCollision(Ugar *target, bool *isLesser);
    bool CheckFoodCollision(Food *target);

    void SetPosition(float x, float y);

    void Move(float x, float y);
    void MoveDirection(float direction);

    float GetSquare();
    void SetSquare(float square);
    void Draw(QPainter *painter);

private:
    static const bool INVERT_X = false;
    static const bool INVERT_Y = true;

    constexpr static const float COLLISION_DISTANCE = 0.1f;
    constexpr static const float U_DIFFERENCE = 0.00001f;
    constexpr static const float SIZE_LERP = 0.1f;

    constexpr static const float FRICTION = 0.1f;

    constexpr static const float MAX_SPEED_INC = 0.4f;
    constexpr static const float MAX_SPEED_SIZE_DEC = 0.35f;
    constexpr static const float SPEED_SIZE_DEC = 0.005f;

};

#endif // UGAR_H
