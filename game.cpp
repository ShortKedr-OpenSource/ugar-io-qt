#include<time.h>
#include "game.h"
#include "ugar.h"
#include "ugarplayer.h"
#include "line.h"
#include "ugarai.h"


const QString Game::START_GAME_LABEL = "Press Space to Play";

Game::Game()
{
    srand(time(NULL));

    isStarted = false;

    delete cam;
    cam = new Camera(new QPointF(640, 480), new QPointF(320, 240), 1.0f);

    for (int i = 0; i < VERT_LINE_AMOUNT; i++) {
        QColor *color = (i == 0 || i == VERT_LINE_AMOUNT - 1) ? new QColor(0, 0, 0) : new QColor(240, 240, 240);
        delete vertLines[i];
        vertLines[i] = new Line(new QPointF((i*200), 0), new QPointF((i*200), 4000.0), color);
    }

    for (int i = 0; i < HORZ_LINE_AMOUNT; i++) {
        QColor *color = (i == 0 || i == HORZ_LINE_AMOUNT - 1) ? new QColor(0, 0, 0) : new QColor(240, 240, 240);
        delete horzLines[i];
        horzLines[i] = new Line(new QPointF(0, (i*200)), new QPointF(4000.0, (i*200)), color);
    }

    delete ugars[0];
    if (isStarted) ugars[0] = new UgarPlayer(new QPointF(rand() % (int)(GAME_FIELD_WIDTH/2.0f) + GAME_FIELD_WIDTH/2.0f, rand() % (int)(GAME_FIELD_HEIGHT/2.0f) + GAME_FIELD_HEIGHT/2.0f), 5.0f);
    for (int i = 1; i < UGAR_AMOUNT; i++){
        delete ugars[i];
        ugars[i] = new UgarAI(new QPointF(rand() % (int)(GAME_FIELD_WIDTH/2.0f) + GAME_FIELD_WIDTH/2.0f, rand() % (int)(GAME_FIELD_HEIGHT/2.0f) + GAME_FIELD_HEIGHT/2.0f), 5.0f);
        ((UgarAI*)ugars[i])->AssignAIData(foods, FOOD_AMOUNT, ugars, UGAR_AMOUNT);
    }
    for (int i = 0; i < FOOD_AMOUNT; i++){
        delete foods[i];
        foods[i] = new Food(2.0f, new QPointF(rand() % (int)(GAME_FIELD_WIDTH), rand() % (int)(GAME_FIELD_HEIGHT)));
    }

}

Game::~Game()
{
    delete cam;
    for (int i = 0; i < UGAR_AMOUNT; i++)
        delete ugars[i];
    for (int i = 0; i < FOOD_AMOUNT; i++)
        delete foods[i];
    for (int i = 0; i < VERT_LINE_AMOUNT; i++)
        delete vertLines[i];
    for (int i = 0; i < HORZ_LINE_AMOUNT; i++)
        delete horzLines[i];
}

void Game::Update()
{
    if (ugars[0] != nullptr && isStarted){
        cam->observedPosition->setX(cam->observedPosition->x() + (ugars[0]->position->x() - cam->observedPosition->x()) * CAMERA_LERP);
        cam->observedPosition->setY(cam->observedPosition->y() + (ugars[0]->position->y() - cam->observedPosition->y()) * CAMERA_LERP);

        float requiredScale = 0.0f;
        if (ugars[0]->radius < 60.0f) requiredScale = (cam->viewportSize->y() / NORMAL_SCALE_RESOLUTION);
        else requiredScale = (cam->viewportSize->y() / NORMAL_SCALE_RESOLUTION) * (NORMAL_SCALE_RADIUS / (int)(ugars[0]->radius));
        cam->scale += (requiredScale - cam->scale) * SCALE_LERP;
    } else if (ugars[1] != nullptr) {
        cam->observedPosition->setX(cam->observedPosition->x() + (ugars[1]->position->x() - cam->observedPosition->x()) * CAMERA_LERP);
        cam->observedPosition->setY(cam->observedPosition->y() + (ugars[1]->position->y() - cam->observedPosition->y()) * CAMERA_LERP);

        float requiredScale = 0.0f;
        if (ugars[1]->radius < 60.0f) requiredScale = (cam->viewportSize->y() / NORMAL_SCALE_RESOLUTION);
        else requiredScale = (cam->viewportSize->y() / NORMAL_SCALE_RESOLUTION) * (NORMAL_SCALE_RADIUS / (int)(ugars[1]->radius));
        cam->scale += (requiredScale - cam->scale) * SCALE_LERP;
    }

    for (int i = 0; i < UGAR_AMOUNT; i++){
        if (ugars[i] == nullptr) continue;
        ugars[i]->Update();
        if (ugars[i]->position->x() - ugars[i]->radius < 0) ugars[i]->position->setX(ugars[i]->radius);
        if (ugars[i]->position->x() + ugars[i]->radius > GAME_FIELD_WIDTH) ugars[i]->position->setX(GAME_FIELD_WIDTH - ugars[i]->radius);
        if (ugars[i]->position->y() - ugars[i]->radius < 0) ugars[i]->position->setY(ugars[i]->radius);
        if (ugars[i]->position->y() + ugars[i]->radius > GAME_FIELD_HEIGHT) ugars[i]->position->setY(GAME_FIELD_HEIGHT - ugars[i]->radius);

        for (int j = 0; j < UGAR_AMOUNT; j++){
            if (ugars[j] == nullptr || ugars[i] == nullptr || ugars[j] == ugars[i]) continue;
            bool isLesser = false;
            if (ugars[i]->CheckCollision(ugars[j], &isLesser)){
                if (isLesser){
                    ugars[j]->SetSquare(ugars[j]->GetSquare() + ugars[i]->GetSquare());
                    if (ugars[i]) delete ugars[i];
                    ugars[i] = nullptr;
                    if (i == 0) isStarted = false;
                } else {
                    ugars[i]->SetSquare(ugars[j]->GetSquare() + ugars[i]->GetSquare());
                    if (ugars[j]) delete ugars[j];
                    ugars[j] = nullptr;
                    if (j == 0) isStarted = false;
                }
            }
        }
        for (int j = 0; j < FOOD_AMOUNT; j++){
            if (foods[j] == nullptr) continue;
            if (ugars[i] != nullptr && ugars[i]->CheckFoodCollision(foods[j])) {
                ugars[i]->SetSquare(ugars[i]->GetSquare() + foods[j]->GetSquare());
                if (foods[j]) delete foods[j];
                foods[j] = nullptr;
            }
        }
    }

    if (objectControlTimer > OBJ_CONTROL_UPDATE_TIME){
        ObjectControlUpdate();
        objectControlTimer = 0;
    } else objectControlTimer++;

}

void Game::ObjectControlUpdate()
{
    int count = 0;
    for (int i = 0; i < FOOD_AMOUNT; i++) {
        if (foods[i] == nullptr && count < 50) {
            foods[i] = new Food(2.0f, new QPointF(rand() % (int)(GAME_FIELD_WIDTH), rand() % (int)(GAME_FIELD_HEIGHT)));
            count++;
        }
    }

    count = 0;
    if (ugars[0] == nullptr && isStarted) ugars[0] = new UgarPlayer(new QPointF(rand() % (int)(GAME_FIELD_WIDTH/2.0f) + GAME_FIELD_WIDTH/2.0f, rand() % (int)(GAME_FIELD_HEIGHT/2.0f) + GAME_FIELD_HEIGHT/2.0f), 5.0f);
    for (int i = 1; i < UGAR_AMOUNT; i++) {
        if (ugars[i] == nullptr && count < 2) {
            ugars[i] = new UgarAI(new QPointF(rand() % (int)(GAME_FIELD_WIDTH/2.0f) + GAME_FIELD_WIDTH/2.0f, rand() % (int)(GAME_FIELD_HEIGHT/2.0f) + GAME_FIELD_HEIGHT/2.0f), 5.0f);
            ((UgarAI*)ugars[i])->AssignAIData(foods, FOOD_AMOUNT, ugars, UGAR_AMOUNT);
            count++;
        }
    }
}

bool Game::IsStarted()
{
    return isStarted;
}

void Game::Start()
{
    isStarted = true;
    if (ugars[0] == nullptr && isStarted) ugars[0] = new UgarPlayer(new QPointF(rand() % (int)(GAME_FIELD_WIDTH/2.0f) + GAME_FIELD_WIDTH/2.0f, rand() % (int)(GAME_FIELD_HEIGHT/2.0f) + GAME_FIELD_HEIGHT/2.0f), 5.0f);
}

void Game::Draw(QPainter *painter)
{

    for (int i = 0; i < VERT_LINE_AMOUNT; i++){
        if (vertLines[i] == nullptr) continue;
        vertLines[i]->UpdateDrawableLine(cam->GetNormalXOffset(), cam->GetNormalYOffset(), cam->scale);
        vertLines[i]->Draw(painter);
    }

    for (int i = 0; i < HORZ_LINE_AMOUNT; i++){
        if (horzLines[i] == nullptr) continue;
        horzLines[i]->UpdateDrawableLine(cam->GetNormalXOffset(), cam->GetNormalYOffset(), cam->scale);
        horzLines[i]->Draw(painter);
    }

    for (int i = 0; i < UGAR_AMOUNT; i++){
        if (ugars[i] == nullptr) continue;
        ugars[i]->UpdateDrawingRect(cam->GetNormalXOffset(), cam->GetNormalYOffset(), cam->scale);
        ugars[i]->Draw(painter);
    }

    for (int i = 0; i < FOOD_AMOUNT; i++){
        if (foods[i] == nullptr) continue;
        foods[i]->UpdateDrawingRect(cam->GetNormalXOffset(), cam->GetNormalYOffset(), cam->scale);
        foods[i]->Draw(painter);
    }

    if (cam != nullptr && !isStarted){
        QRectF* mainRect = new QRectF(0.0, 20.0, cam->viewportSize->x(), 100.0);
        QRectF* shadowRect = new QRectF(3.0, 23.0, cam->viewportSize->x(), 100.0);

        QFont* mainFont = new QFont("Arial", FONT_SIZE);
        QFont* shadowFont = new QFont("Arial", FONT_SIZE);

        QPen* mainPen = new QPen(QColor(0,0,0,255));
        QPen* shadowPen = new QPen(QColor(0, 0, 0, 67));

        painter->setFont(*shadowFont);
        painter->setPen(*shadowPen);
        painter->drawText(*shadowRect, Qt::AlignHCenter | Qt::AlignTop, START_GAME_LABEL);

        painter->setFont(*mainFont);
        painter->setPen(*mainPen);
        painter->drawText(*mainRect, Qt::AlignHCenter | Qt::AlignTop, START_GAME_LABEL);

        delete mainRect;
        delete shadowRect;

        delete mainFont;
        delete shadowFont;

        delete mainPen;
        delete shadowPen;
    }
}
