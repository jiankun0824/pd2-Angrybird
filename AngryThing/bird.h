#ifndef BIRD_H
#define BIRD_H

#include <gameitem.h>
#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>
#include <cstdlib>

#define BIRD_DENSITY 10.0f
#define BIRD_FRICTION 0.2f
#define BIRD_RESTITUTION 0.4f

class Bird : public GameItem{
public:
    Bird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    void setLinearVelocity(b2Vec2 velocity);
    virtual void skill() = 0;
    void set_transform(b2Vec2 loc, float angle);
    b2Vec2 get_position();
    b2Vec2 get_velocity();
};

#endif // BIRD_H
