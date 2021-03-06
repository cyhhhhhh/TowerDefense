#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QPoint>
#include <QSize>
#include <QPixmap>
#include <vector>
using namespace std;

class WayPoint;
class QPainter;
class MainWindow;
class Tower;

class Enemy : public QObject
{
    Q_OBJECT
public:
    Enemy(WayPoint *startWayPoint, MainWindow *game, const QPixmap &sprite = QPixmap("image/enemy.png"));
    ~Enemy();

    void draw(QPainter *painter) const;
    void move();
    void getDamage(int damage);
    void getRemoved();
    void getAttacked(Tower *attacker);
    void gotLostSight(Tower *attacker);
    QPoint pos() const;
    vector<Tower *>	m_attackedTowers;
public slots:
    void doActivate();

protected:
    bool			m_active;
    int				m_maxHp;
    int				m_currentHp;
    qreal			m_walkingSpeed;
    qreal			m_rotationSprite;

    QPoint			m_pos;
    WayPoint *		m_destinationWayPoint;
    MainWindow *	m_game;
    const QPixmap	m_sprite;
private:
    static const QSize ms_fixedSize;
};



#endif // ENEMY_H
