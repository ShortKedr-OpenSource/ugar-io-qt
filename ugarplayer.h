#ifndef UGARPLAYER_H
#define UGARPLAYER_H

#include <QtGui>
#include "ugar.h"

class UgarPlayer : public Ugar {

public:

    static const int UP_KEY = Qt::Key::Key_W;
    static const int DOWN_KEY = Qt::Key::Key_S;
    static const int LEFT_KEY = Qt::Key::Key_A;
    static const int RIGHT_KEY = Qt::Key::Key_D;


    UgarPlayer();
    UgarPlayer(QPointF *_position, float _radius);

    ~UgarPlayer();

    void Update() override;

    void event(QKeyEvent *event);

private:
   bool upKey = false;
   bool downKey = false;
   bool leftKey = false;
   bool rightKey = false;

};

#endif // UGARPLAYER_H
