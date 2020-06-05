#include "bullet.h"
#include "enemy.h"
#include "mainwindow.h"
#include <QPainter>
#include <QPropertyAnimation>

const QSize Bullet::ms_fixedSize(8, 8);

Bullet::Bullet(QPoint startPos, QPoint targetPoint, int damage, Enemy *target,
               MainWindow *game, const QPixmap &sprite)
    : m_startPos(startPos)
    , m_targetPos(targetPoint)
    , m_sprite(sprite)
    , m_currentPos(startPos)
    , m_target(target)
    , m_game(game)
    , m_damage(damage)
{
}

void Bullet::move()
{
    // 100�����ڻ��е���
    static const int duration = 100;
    QPropertyAnimation *animation = new QPropertyAnimation(this, "m_currentPos");
    animation->setDuration(duration);
    animation->setStartValue(m_startPos);
    animation->setEndValue(m_targetPos);
    connect(animation, SIGNAL(finished()), this, SLOT(hitTarget()));

    animation->start();
}

bool Bullet::checkEnemy()
{
    vector<Enemy*> Enemylist=m_game->getEnemies();
    for(vector<Enemy*>::iterator iter=Enemylist.begin();iter!=Enemylist.end();iter++)
    {
        if(*iter==m_target)
            return true;//�õ����Դ���
    }
    return false;//�õ����ѱ�����
}

void Bullet::hitTarget()
{
    // ���������ԭ����:
    // ���ܶ���ڵ����е���,������һ����������,���µ���delete
    // �����ڵ��ٹ������ĵ��˾�����Ч�ڴ�����
    // ������ж��µ����Ƿ���Ч
    if (checkEnemy())
        m_target->getDamage(m_damage);
    m_game->removedBullet(this);
}

void Bullet::setCurrentPos(QPoint pos)
{
    m_currentPos = pos;
}

QPoint Bullet::currentPos() const
{
    return m_currentPos;
}

void Bullet::draw(QPainter *painter) const
{
    painter->drawPixmap(m_currentPos, m_sprite);
}

