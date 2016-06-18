#include "yellowbird.h"

yellowbird::yellowbird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene): Bird(x, y, radius, timer,pixmap, world, scene)
{

}

void yellowbird::skill(){

    Bird::setLinearVelocity(b2Vec2(get_velocity().x*2, get_velocity().y));
}
