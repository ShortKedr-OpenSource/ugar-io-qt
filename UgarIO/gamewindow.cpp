#include "gamewindow.h"
#include "ugar.h"
#include "ugarplayer.h"

GameWindow::GameWindow(QWindow *parent)
    : QWindow(parent),
    m_backingstore(new QBackingStore(this))
{
    setGeometry(screen()->size().width()/2-GameWindow::DEFAULT_WIDTH/2, screen()->size().height()/2-GameWindow::DEFAULT_HEIGHT/2, GameWindow::DEFAULT_WIDTH, GameWindow::DEFAULT_HEIGHT);
    game = new Game();

    QTimer *renderTimer = new QTimer(this);
    connect(renderTimer, SIGNAL(timeout()), this, SLOT(renderNow()));
    renderTimer->start(16);

    QTimer *updateTimer = new QTimer(this);
    connect(updateTimer, SIGNAL(timeout()), game, SLOT(Update()));
    updateTimer->start(16);

    /*QTimer *objectControlTimer = new QTimer(this);
    connect(objectControlTimer, SIGNAL(timeout()), game, SLOT(ObjectControlUpdate()));
    updateTimer->start(5000);*/
}

GameWindow::~GameWindow()
{
    delete game;
}

bool GameWindow::event(QEvent *event){

    if (event->type() == QEvent::UpdateRequest){
        renderNow();
        return true;
    } else if (event->type() == QEvent::KeyPress || event->type() == QEvent::KeyRelease){
        if ((static_cast<QKeyEvent*>(event))->key() == Qt::Key::Key_Space) game->Start();
        else if (game->ugars[0] != nullptr) (static_cast<UgarPlayer*>(game->ugars[0]))->event(static_cast<QKeyEvent*>(event));
        return true;
    }
    return QWindow::event(event);
}

void GameWindow::renderLater()
{
    requestUpdate();
}

void GameWindow::resizeEvent(QResizeEvent *resizeEvent)
{
    m_backingstore->resize(resizeEvent->size());
}

void GameWindow::exposeEvent(QExposeEvent *)
{
    if (isExposed())
        renderNow();
}

void GameWindow::renderNow()
{
    if (!isExposed())
        return;

    QRect rect(0, 0, width(), height());
    m_backingstore->beginPaint(rect);

    QPaintDevice *device = m_backingstore->paintDevice();
    QPainter painter(device);

    QBrush *brush = new QBrush(Qt::white);
    painter.setRenderHint(QPainter::RenderHint::Antialiasing);
    painter.fillRect(0, 0, width(), height(), *brush);
    render(&painter);
    painter.end();

    m_backingstore->endPaint();
    m_backingstore->flush(rect);
    delete brush;
}

void GameWindow::render(QPainter *painter)
{
    game->cam->viewportSize->setX(this->width());
    game->cam->viewportSize->setY(this->height());
    game->Draw(painter);
}
