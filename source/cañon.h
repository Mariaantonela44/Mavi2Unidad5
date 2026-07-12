#ifndef CAÑON_H
#define CAÑON_H   

#include <raylib.h>

class Canon
{
private:

    Vector2 posicion;

    float largo;

    float angulo;

public:

    Canon(float x, float y);

    void Actualizar();

    void Dibujar();

    float ObtenerAngulo();

    Vector2 ObtenerPunta();
};

 
#endif
