#ifndef BULLET_H
#define BULLET_H

#include <QPoint>
#include <QSize>
#include <QPixmap>
#include <QObject>
#include "tower.h"
class QPainter;
class Enemy;
class MainWindow;

class Bullet : QObject
{
    Q_OBJECT
    Q_PROPERTY(QPoint m_currentPos READ currentPos WRITE setCurrentPos)//Qt的动画机制，将m_currentPos注册为属性来使用

public:
    Bullet(QPoint startPos, QPoint targetPoint, int damage, Enemy *target,
           MainWindow *game, const QPixmap &sprite = QPixmap("image/bullet.png"));

    void draw(QPainter *painter) const;
    void move();
    void setCurrentPos(QPoint pos);
    QPoint currentPos() const;
    bool checkEnemy();

private slots:
    void hitTarget();

private:
    const QPoint	m_startPos;//子弹起始位置即攻击塔的位置
    const QPoint	m_targetPos;//终止位置即敌人位置
    const QPixmap	m_sprite;
    QPoint			m_currentPos;//子弹当前位置
    Enemy *			m_target;//目标敌人
    MainWindow *	m_game;
    int				m_damage;//攻击力，由攻击塔决定

    static const QSize ms_fixedSize;
};



#endif // BULLET_H
