#include "bluebird.h"

bluebird::bluebird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene): Bird(x, y, radius, timer,pixmap, world, scene)
{

}

void bluebird::skill(){

    Bird::setLinearVelocity(b2Vec2(0.0f,0.0f));


}
