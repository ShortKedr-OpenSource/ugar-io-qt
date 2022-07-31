#include "ugarplayer.h"

UgarPlayer::UgarPlayer()
{

}

UgarPlayer::UgarPlayer(QPointF *_position, float _radius)
    : Ugar (_position, _radius) {

}

UgarPlayer::~UgarPlayer()
{
    //Ugar::~Ugar();
}

void UgarPlayer::Update()
{
    Ugar::Update();
    if (upKey) {
        if (leftKey) MoveDirection(135.0f);
        else if (rightKey) MoveDirection(45.0f);
        else MoveDirection(90.0f);
    } else if (downKey) {
        if (leftKey) MoveDirection(225.0f);
        else if (rightKey) MoveDirection(315.0f);
        else MoveDirection(270.0f);
    } else if (leftKey) {
        if (upKey) MoveDirection(135.0f);
        else if (downKey) MoveDirection(225.0f);
        else MoveDirection(180.0f);
    } else if (rightKey) {
        if (upKey) MoveDirection(45.0f);
        else if (downKey) MoveDirection(315.0f);
        else MoveDirection(0.0f);
    }
}

void UgarPlayer::event(QKeyEvent *event)
{
    bool press = true;
    if (event->type() == QKeyEvent::Type::KeyPress) press = true;
    else if(event->type() == QKeyEvent::Type::KeyRelease) press = false;
    else return;

    switch (event->key()){
        case UP_KEY:
            upKey = press;
            break;
        case DOWN_KEY:
            downKey = press;
            break;
        case LEFT_KEY:
            leftKey = press;
            break;
        case RIGHT_KEY:
            rightKey = press;
            break;
    }
}
