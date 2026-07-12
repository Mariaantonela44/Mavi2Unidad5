#ifndef PROYECTIL_H 
#define PROYECTIL_H 

#include "box2d.h"
#include "raylib.h"

class Proyectil
{
private:

    b2Body* body;

    float radio;

public:

    Proyectil(
        b2World* world,
        float x,
        float y,
        float r
    );

    void Lanzar(float angulo, float potencia);

    void Dibujar();

    void Reiniciar(float x, float y);

    b2Body* GetBody();
};

#endif