#include "ContactListener.h"

ContactListener::ContactListener(){
    sensorActivado = false;
}

void ContactListener::ReiniciarSensor(){
    sensorActivado = false;
}


void ContactListener::BeginContact(b2Contact* contact){
    b2Body* cuerpoA = contact->GetFixtureA()->GetBody();
    b2Body* cuerpoB = contact->GetFixtureB()->GetBody();

    uintptr_t tipoA = cuerpoA->GetUserData().pointer;
    uintptr_t tipoB = cuerpoB->GetUserData().pointer;

   
    if ((tipoA == 4 && tipoB == 3) ||
        (tipoA == 3 && tipoB == 4))
    {
        sensorActivado = true;
    }
}

void ContactListener::EndContact(b2Contact* contact){
    b2Body* cuerpoA = contact->GetFixtureA()->GetBody();
    b2Body* cuerpoB = contact->GetFixtureB()->GetBody();

    uintptr_t tipoA = cuerpoA->GetUserData().pointer;
    uintptr_t tipoB = cuerpoB->GetUserData().pointer;

    if ((tipoA == 4 && tipoB == 3) ||
        (tipoA == 3 && tipoB == 4))
    {
        sensorActivado = false;
    }
}