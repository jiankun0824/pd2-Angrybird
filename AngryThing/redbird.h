#ifndef REDBIRD_H
#define REDBIRD_H

#include<gameitem.h>
#include<bird.h>

class redbird : public Bird{
public:
    redbird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    virtual void skill();
};

#endif // REDBIRD_H
