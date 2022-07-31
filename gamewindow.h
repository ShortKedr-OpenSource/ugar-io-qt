#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H
#include<QtGui>
#include "ugar.h"
#include "game.h"

class GameWindow : public QWindow {
    Q_OBJECT

public:
    const int DEFAULT_WIDTH = 800;
    const int DEFAULT_HEIGHT = 600;

    Game *game;

    explicit GameWindow (QWindow *parent = nullptr);
    ~GameWindow();

    virtual void render (QPainter *painter);

public slots:
    void renderLater();
    void renderNow();



protected:
    bool event(QEvent *event) override;

    void resizeEvent(QResizeEvent *event) override;
    void exposeEvent(QExposeEvent *event) override;

private:
    QBackingStore *m_backingstore;
};

#endif // GAMEWINDOW_H
