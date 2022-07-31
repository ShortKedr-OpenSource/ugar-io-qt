#ifndef GAME_H
#define GAME_H

#include <QtGui>
#include "ugar.h"
#include "food.h"
#include "camera.h"
#include "line.h"

class Game : public QObject
{
    Q_OBJECT

    static const QString START_GAME_LABEL;
    constexpr static const float FONT_SIZE = 28.0f;

    constexpr static const float GAME_FIELD_WIDTH = 4000;
    constexpr static const float GAME_FIELD_HEIGHT = 4000;

    constexpr static const int UGAR_AMOUNT = 75;
    constexpr static const int FOOD_AMOUNT = 750;

    constexpr static const int VERT_LINE_AMOUNT = 21;
    constexpr static const int HORZ_LINE_AMOUNT = 21;

    constexpr static const float CAMERA_LERP = 0.05f;
    constexpr static const float SCALE_LERP = 0.05f;

    constexpr static const float NORMAL_SCALE_RESOLUTION = 768.0f;
    constexpr static const float NORMAL_SCALE_RADIUS = 60.0f;

public:

    Camera *cam;
    Ugar *ugars[UGAR_AMOUNT];
    Food *foods[FOOD_AMOUNT];

    Line *vertLines[VERT_LINE_AMOUNT];
    Line *horzLines[HORZ_LINE_AMOUNT];

    Game();
    ~Game();

    void ObjectControlUpdate();
    bool IsStarted();
    void Start();


public slots:
    void Update();
    void Draw(QPainter *painter);

private:
    constexpr static const int OBJ_CONTROL_UPDATE_TIME = 300;
    int objectControlTimer = 0;
    bool isStarted = false;
};

#endif // GAME_H
