#include "cañon.h"
#include <cmath>

Canon::Canon(float x, float y){
    posicion = { x, y };

    largo = 80;

    angulo = 45;
}

void Canon::Actualizar(){
    if (IsKeyDown(KEY_LEFT))
        angulo += 1.0f;

    if (IsKeyDown(KEY_RIGHT))
        angulo -= 1.0f;

    if (angulo > 80)
        angulo = 80;

    if (angulo < 10)
        angulo = 10;
}

void Canon::Dibujar(){
    float rad = angulo * DEG2RAD;

    Vector2 punta;

    punta.x = posicion.x + cos(rad) * largo;
    punta.y = posicion.y - sin(rad) * largo;

    DrawCircleV(posicion, 20, DARKGRAY);

    DrawLineEx( posicion, punta, 12,  GRAY );
}

float Canon::ObtenerAngulo(){
    return angulo;
}

Vector2 Canon::ObtenerPunta(){
    float rad = angulo * DEG2RAD;

    Vector2 punta;

    punta.x = posicion.x + cos(rad) * largo;
    punta.y = posicion.y - sin(rad) * largo;

    return punta;
}