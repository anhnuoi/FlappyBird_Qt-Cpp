#include "pillar.h"
#include <QRandomGenerator>
#include <QGraphicsScene>
#include "../game.h"
Pillar::Pillar()
    : m_topPillar(new QGraphicsPixmapItem(Game::PATH_TO_PILLAR_PIXMAP)),
      m_bottomPillar(new QGraphicsPixmapItem(Game::PATH_TO_PILLAR_PIXMAP)),
      m_pastBird(false)
{
    m_topPillar->setPos(QPointF(0,0) - QPointF(m_topPillar->boundingRect().width()/2, m_topPillar->boundingRect().height() + 60));
    m_bottomPillar->setPos(QPointF(0,0) + QPointF(-m_bottomPillar->boundingRect().width()/2, m_topPillar->boundingRect().height() + 60));

    addToGroup(m_topPillar);
    addToGroup(m_bottomPillar);

    m_yPos = QRandomGenerator::global()->bounded(150);
    int xRandomizer = QRandomGenerator::global()->bounded(200);

    setPos(QPoint(0,0) + QPoint(260+xRandomizer, m_yPos));

    m_xAnimation = new QPropertyAnimation(this,"x",this);
    m_xAnimation->setStartValue(260 + xRandomizer);
    m_xAnimation->setEndValue(-260);
    m_xAnimation->setEasingCurve(QEasingCurve::Linear);
    m_xAnimation->setDuration(1500);

    connect(m_xAnimation,&QPropertyAnimation::finished,[=](){
        qDebug() << "Animation finished";
        scene()->removeItem(this);
        delete this;
    });

    m_xAnimation->start();
}

Pillar::~Pillar()
{
    delete m_topPillar;
    delete m_bottomPillar;
}

qreal Pillar::x() const
{
    return m_x;
}

void Pillar::setX(qreal x)
{
    m_x = x;

    setPos(QPointF(0,0) + QPointF(x, m_yPos));
}
