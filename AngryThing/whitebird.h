#ifndef WHITEBIRD_H
#define WHITEBIRD_H

#include<gameitem.h>
#include<bird.h>


class whitebird : public Bird{
public:
    whitebird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    virtual void skill();
};

#endif // WHITEBIRD_H
