#include "Proyectil.h"
#include <cmath>

#define SCALE 30.0f
#define SCREEN_HEIGHT 900

Proyectil::Proyectil(b2World* world, float x, float y, float r){
    radio = r;

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;

    bodyDef.position.Set(x / SCALE,(SCREEN_HEIGHT - y) / SCALE);

    body = world->CreateBody(&bodyDef);

    b2CircleShape shape;
    shape.m_radius = radio / SCALE;

    b2FixtureDef fixture;

    fixture.shape = &shape;
    fixture.density = 1.0f;
    fixture.friction = 0.3f;
    fixture.restitution = 0.2f;

    body->CreateFixture(&fixture);

    // ID del proyectil
    body->GetUserData().pointer = 3;
}

void Proyectil::Lanzar(float angulo, float potencia){
    float rad = angulo * DEG2RAD;

    float vx = cos(rad) * potencia;
    float vy = sin(rad) * potencia;

    body->SetLinearVelocity(b2Vec2(vx, vy));
}

void Proyectil::Dibujar(){
    b2Vec2 pos = body->GetPosition();

    DrawCircle( pos.x * SCALE, SCREEN_HEIGHT - pos.y * SCALE, radio, ORANGE );
}

void Proyectil::Reiniciar(float x, float y){
    body->SetTransform(
        b2Vec2(x / SCALE, (SCREEN_HEIGHT - y) / SCALE), 0);

    body->SetLinearVelocity(b2Vec2_zero);
    body->SetAngularVelocity(0);
}

b2Body* Proyectil::GetBody()
{
    return body;
}