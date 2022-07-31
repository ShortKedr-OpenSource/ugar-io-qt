#ifndef CAMERA_H
#define CAMERA_H

#include <QtGui>

class Camera {

public:

    QPointF *viewportSize = new QPointF(0, 0);
    QPointF *observedPosition = new QPointF(0, 0);
    float scale = 1.0f;


    Camera();
    Camera(QPointF *vs, QPointF *op, float _scale = 1.0f);

    ~Camera();

    float GetNormalXOffset();
    float GetNormalYOffset();

    void SetCamera(QPointF *vs, QPointF *op);
    void SetCamera(QPointF *vs, QPointF *op, float _scale);

};

#endif // CAMERA_H
