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
    Q_PROPERTY(QPoint m_currentPos READ currentPos WRITE setCurrentPos)//Qt�Ķ������ƣ���m_currentPosע��Ϊ������ʹ��

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
    const QPoint	m_startPos;//�ӵ���ʼλ�ü���������λ��
    const QPoint	m_targetPos;//��ֹλ�ü�����λ��
    const QPixmap	m_sprite;
    QPoint			m_currentPos;//�ӵ���ǰλ��
    Enemy *			m_target;//Ŀ�����
    MainWindow *	m_game;
    int				m_damage;//���������ɹ���������

    static const QSize ms_fixedSize;
};



#endif // BULLET_H
