#include "whitebird.h"

whitebird::whitebird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene): Bird(x, y, radius, timer,pixmap, world, scene)
{

}

void whitebird::skill(){

    Bird::setLinearVelocity(b2Vec2(get_velocity().x, -1*abs(get_velocity().y)*10 ));

}




