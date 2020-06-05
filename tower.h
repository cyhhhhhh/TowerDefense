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
    void checkEnemyInRange();//�鿴�����Ƿ��ڹ�����Χ��
    void targetKilled();
    void attackEnemy();//��������
    void chooseEnemyForAttack(Enemy *enemy);//ѡ�񹥻��Ķ���
    QPoint getpos();
    void lostSightOfEnemy();//�����Ѳ��ڹ�����Χ
    static int knowcost();
private slots:
    void shootWeapon();


private:
    bool			m_attacking;
    int				m_attackRange;//���������Թ��������˵ľ���
    int				m_damage;//����������ʱ��ɵ��˺�
    int				m_fireRate;//�����ٴι������˵�ʱ����
    static int      cost;//�����������Ľ��
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
