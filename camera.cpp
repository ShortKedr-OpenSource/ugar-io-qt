#include "camera.h"

Camera::Camera()
{

}

Camera::Camera(QPointF *vs, QPointF *op, float _scale)
{
    *viewportSize = *vs;
    *observedPosition = *op;
    scale = _scale;
}

Camera::~Camera()
{
    delete viewportSize;
    delete observedPosition;
}

float Camera::GetNormalXOffset()
{
    return observedPosition->x() * scale - (viewportSize->x() / 2.0f);
}

float Camera::GetNormalYOffset()
{
    return observedPosition->y() * scale - (viewportSize->y() / 2.0f);
}

void Camera::SetCamera(QPointF *vs, QPointF *op)
{
    *viewportSize = *vs;
    *observedPosition = *op;
}

void Camera::SetCamera(QPointF *vs, QPointF *op, float _scale)
{
    *viewportSize = *vs;
    *observedPosition = *op;
    scale = _scale;
}
