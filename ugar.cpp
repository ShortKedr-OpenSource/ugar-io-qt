#include "ugar.h"

#define _USE_MATH_DEFINES
#include <math.h>

Ugar::Ugar() {

}

Ugar::Ugar(QPointF *_position, float _radius)
{
    color->setRgb(rand() % 256, rand() % 256, rand() % 256);
    *position = *_position;
    radius = _radius;
}

Ugar::~Ugar()
{
    if (position) delete position;
    if (currentSpeed) delete currentSpeed;
    if (color) delete color;
    if (drawingRect) delete drawingRect;
}

void Ugar::Update()
{
    UpdateSize();
    UpdateSpeedInc();
    position->setX(position->x() + currentSpeed->x());
    position->setY(position->y() + currentSpeed->y());
    currentSpeed->setX(currentSpeed->x() - currentSpeed->x() * FRICTION);
    currentSpeed->setY(currentSpeed->y() - currentSpeed->y() * FRICTION);
}

void Ugar::UpdateDrawingRect(float xoffset, float yoffset, float scale)
{
    drawingRect->setX((position->x() - showedRadius) * scale - xoffset);
    drawingRect->setY((position->y() - showedRadius) * scale - yoffset);
    drawingRect->setWidth(showedRadius * 2.0f * scale);
    drawingRect->setHeight(showedRadius * 2.0f * scale);
}

void Ugar::UpdateSpeedInc()
{
    float decrement = radius * SPEED_SIZE_DEC;
    currentSpeedInc = MAX_SPEED_INC - ((decrement < MAX_SPEED_SIZE_DEC) ? decrement : MAX_SPEED_SIZE_DEC);
}

void Ugar::UpdateSize()
{
    if (fabsf(radius-showedRadius) <= U_DIFFERENCE) return;
    showedRadius += (radius - showedRadius) * SIZE_LERP;
}

bool Ugar::CheckFoodCollision(Food *target)
{
    float xDist = position->x() - target->position->x();
    float yDist = position->y() - target->position->y();

    float dist = sqrtf(xDist*xDist + yDist*yDist);
    float collisionDist = radius + (target->radius*0.6f);
    if (dist <= collisionDist) return true;
    else return false;
}

void Ugar::SetPosition(float x, float y)
{
    position->setX(x);
    position->setY(y);
}

void Ugar::Move(float x, float y)
{
    UpdateSpeedInc();
    float sum = fabsf(x)+fabsf(y);
    currentSpeed->setX(currentSpeed->x() + ((sum != 0.0f) ? x/sum : 0) * currentSpeedInc);
    currentSpeed->setY(currentSpeed->y() + ((sum != 0.0f) ? y/sum : 0) * currentSpeedInc);
}

void Ugar::MoveDirection(float direction)
{
    float xmul = (float)((INVERT_X) ? -cosf(direction*M_PI/180.0f) : cosf(direction*M_PI/180.0f));
    float ymul = (float)((INVERT_Y) ? -sinf(direction*M_PI/180.0f) : sinf(direction*M_PI/180.0f));

    UpdateSpeedInc();
    currentSpeed->setX(currentSpeed->x() + currentSpeedInc * xmul);
    currentSpeed->setY(currentSpeed->y() + currentSpeedInc * ymul);
}

float Ugar::GetSquare() {
    return M_PI * radius * radius;
}

void Ugar::SetSquare(float square)
{
    radius = sqrtf(square / (float)M_PI);
}

void Ugar::Draw(QPainter *painter)
{
    QPainterPath *p = new QPainterPath();
    QBrush *brush = new QBrush(*color);
    p->addEllipse(*drawingRect);
    painter->fillPath(*p, *brush);
    delete p;
    delete brush;
};

bool Ugar::CheckCollision(Ugar *target, bool *isLesser)
{
    float xDist = position->x() - target->position->x();
    float yDist = position->y() - target->position->y();

    float dist = sqrtf(xDist*xDist + yDist*yDist);
    float collisionDist = (radius > target->radius) ? radius + (target->radius*0.6f) : (radius * 0.6f) + target->radius;
    if (radius < target->radius) *isLesser = true;
    else *isLesser = false;
    if (dist <= collisionDist) return true;
    else return false;
}
