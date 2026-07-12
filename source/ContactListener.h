#ifndef CONTACTLISTENER_H
#define CONTACTLISTENER_H

#include <box2d.h>

class ContactListener : public b2ContactListener
{
public:

    bool sensorActivado;

    ContactListener();

    void ReiniciarSensor();

    void BeginContact(b2Contact* contact) override;

    void EndContact(b2Contact* contact) override;

};

#endif