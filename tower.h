#ifndef TOWER_H
#define TOWER_H

#include <QPoint>
#include <QSize>
#include <QPixmap>
#include <QObject>

class QPainter;
class Enemy;
class Enemy1;
class MainWindow;
class QTimer;

class Tower :  QObject
{
    Q_OBJECT
public:
    Tower(QPoint pos, MainWindow *game, const QPixmap &sprite = QPixmap("image/tower.png"));
    //~Tower();
    Tower();
    void draw(QPainter *painter) const;
    void checkEnemyInRange();//查看敌人是否在攻击范围内
    void targetKilled();
    void attackEnemy();//攻击敌人
    void chooseEnemyForAttack(Enemy *enemy);//选择攻击的对象
    QPoint getpos();
    void lostSightOfEnemy();//敌人已不在攻击范围
    static int knowcost();
private slots:
    void shootWeapon();


private:
    bool			m_attacking;
    int				m_attackRange;//代表塔可以攻击到敌人的距离
    int				m_damage;//代表攻击敌人时造成的伤害
    int				m_fireRate;//代表再次攻击敌人的时间间隔
    static int      cost;//购买该塔所需的金币
    qreal			m_rotationSprite;

    Enemy *			m_chooseEnemy;
    Enemy1*         m_chooseEnemy1;
    MainWindow *	m_game;
    QTimer *		m_fireRateTimer;

    const QPoint	m_pos;
    const QPixmap	m_sprite;

    static const QSize ms_fixedSize;
};


#endif // TOWER_H
