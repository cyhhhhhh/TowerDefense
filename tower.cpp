#include "tower.h"
//#include "enemy.h"
#include "bullet.h"
#include "mainwindow.h"
#include "func_test_coll.h"
#include <QPainter>
#include <QColor>
#include <QTimer>
#include <QVector2D>
#include <QtMath>

int Tower::cost=300;
const QSize Tower::ms_fixedSize(73, 60);

Tower::Tower(QPoint pos, MainWindow *game, const QPixmap &sprite)
    : m_attacking(false)
    , m_attackRange(100)
    , m_damage(10)
    , m_fireRate(1000)
    , m_rotationSprite(0.0)
    , m_chooseEnemy(NULL)
    , m_game(game)
    , m_pos(pos)
    , m_sprite(sprite)
{
    m_fireRateTimer = new QTimer(this);
    connect(m_fireRateTimer, SIGNAL(timeout()), this, SLOT(shootWeapon()));//���������ӵ����롰����Ƶ�ʡ���������
}


void Tower::draw(QPainter *painter) const
{
    painter->save();

    // ����ƫת����,������+ƫ��=����
   static const QPoint offsetPoint(-ms_fixedSize.width() / 2, -ms_fixedSize.height() / 2);
    //����������ѡ������
    painter->translate(m_pos);
    painter->rotate(m_rotationSprite);
    painter->drawPixmap(offsetPoint, m_sprite);
    painter->restore();
}

void Tower::checkEnemyInRange()
{
    if (m_chooseEnemy)
    {
        // ���������,��Ҫ��ת��̨��׼����
        // ������׼��
        QVector2D normalized(m_chooseEnemy->pos() - m_pos);
        normalized.normalize();
        m_rotationSprite = qRadiansToDegrees(qAtan2(normalized.y(), normalized.x())) - 90;

        // ����������빥����Χ
        if (!collisionWithCircle(m_pos, m_attackRange, m_chooseEnemy->pos(), 1))
            lostSightOfEnemy();
    }
    else
    {
        // ��������,���Ƿ��е����ڹ�����Χ��
        vector<Enemy *> Enemylist = m_game->getEnemies();
        foreach (Enemy *enemy, Enemylist)
        {
            if (collisionWithCircle(m_pos, m_attackRange, enemy->pos(), 1))
            {
                chooseEnemyForAttack(enemy);
                break;
            }
        }
    }
}

void Tower::attackEnemy()
{
    m_fireRateTimer->start(m_fireRate);
}

void Tower::chooseEnemyForAttack(Enemy *enemy)
{
    m_chooseEnemy = enemy;//ѡ�����
    attackEnemy();//�������ӵ���������timer
    m_chooseEnemy->getAttacked(this);//�������빥����������ϵ����Ϊһ�����˿��ܱ���������
}


void Tower::lostSightOfEnemy()
{
    m_chooseEnemy->gotLostSight(this);
    if (m_chooseEnemy)
        m_chooseEnemy = NULL;

    m_fireRateTimer->stop();//�������߳���Ұ��Χ���������������ȡ����������ֹͣ����
    m_rotationSprite = 0.0;
}



int Tower::knowcost()
{
    return cost;
}

void Tower::shootWeapon()
{
    //��������λ����һ���ᣬ����������һ��ƫ�����������Զ���
    Bullet *bullet = new Bullet(m_pos, m_chooseEnemy->pos(), m_damage, m_chooseEnemy, m_game);
    bullet->move();
    m_game->addBullet(bullet);
}

void Tower::targetKilled()
{
    if (m_chooseEnemy)
        m_chooseEnemy = NULL;//����Ե��˵�����

    m_fireRateTimer->stop();
    m_rotationSprite = 0.0;
}

QPoint Tower::getpos()
{
    return m_pos;
}
