#ifndef UGARAI_H
#define UGARAI_H
#include "ugar.h"
#include "food.h"

class UgarAI : public Ugar
{
public:
    bool isAgressive = false;

    UgarAI();
    UgarAI(QPointF* _position, float _radius);

    ~UgarAI();

    void Update() override;
    void AssignAIData(Food **_foods, int _foods_count, Ugar **_ugars, int _ugars_count);

private:
    constexpr static const int AGRESSIVE_UPDATE_PERIOD = 15000;
    int agressiveTimer = 0;

    Food **foods;
    int foods_count;

    Ugar **ugars;
    int ugars_count;


    float pointDist(QPointF *first, QPointF *second);
};

#endif // UGARAI_H
