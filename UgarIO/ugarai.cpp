#include <math.h>
#include "ugarai.h"

UgarAI::UgarAI()
{

}

UgarAI::UgarAI(QPointF *_position, float _radius)
    : Ugar (_position, _radius) {

}

UgarAI::~UgarAI()
{

}

void UgarAI::Update()
{
    Ugar::Update();

    if (agressiveTimer > AGRESSIVE_UPDATE_PERIOD){
        isAgressive = (rand()%101 >= 80) ? true : false;
        agressiveTimer = 0;
    } else agressiveTimer++;

    if (foods == nullptr || ugars == nullptr) return;
    Food *nearFood = nullptr;
    float minFoodDist = 10000.0f;
    for (int i = 0; i < foods_count; i++){
        if (foods[i] == nullptr) continue;
        float dist = pointDist(foods[i]->position, position);
        if (minFoodDist > dist){
            nearFood = foods[i];
            minFoodDist = dist;
        }
    }

    Ugar *nearUgar = nullptr;
    float minUgarDist = 10000.0f;

    Ugar *nearDUgar = nullptr;
    float minDUgarDist = 10000.0f;

    for (int i = 0; i < ugars_count; i++){
        if (ugars[i] == nullptr || ugars[i] == this) continue;
        float dist = pointDist(ugars[i]->position, position) - ugars[i]->radius - radius;
        if (ugars[i]->radius < radius && minUgarDist > dist){
            nearUgar = ugars[i];
            minUgarDist = dist;
        } else if (ugars[i]->radius > radius && minDUgarDist > dist){
            nearDUgar = ugars[i];
            minDUgarDist = dist;
        }
    }

    if (isAgressive){
        if (minDUgarDist < minUgarDist){
            if (nearDUgar != nullptr) Move(position->x() - nearDUgar->position->x(), position->y() - nearDUgar->position->y());
        } else{
            if (nearUgar != nullptr) Move(nearUgar->position->x() - position->x(), nearUgar->position->y() - position->y());
        }

    } else {
        if (minDUgarDist < minUgarDist && minDUgarDist < minFoodDist) {
            if (nearDUgar != nullptr) Move(position->x() - nearDUgar->position->x(), position->y() - nearDUgar->position->y());
        } else if (minUgarDist < minFoodDist) {
            if (nearUgar != nullptr) Move(nearUgar->position->x() - position->x(), nearUgar->position->y() - position->y());
        } else {
            if (nearFood != nullptr) Move(nearFood->position->x() - position->x(), nearFood->position->y() - position->y());
        }

    }
}

void UgarAI::AssignAIData(Food **_foods, int _foods_count, Ugar **_ugars, int _ugars_count)
{
    foods = _foods;
    foods_count = _foods_count;
    ugars = _ugars;
    ugars_count = _ugars_count;
}

float UgarAI::pointDist(QPointF *first, QPointF *second)
{
    return sqrtf(powf(first->x()-second->x(), 2.0f) + powf(first->y()-second->y(), 2.0f));
}
