#ifndef GAME_H
#define GAME_H

#include "Mundo.h"
#include "cañon.h"
#include "Proyectil.h"
#include "Plataforma.h"
#include "Sensor.h"
#include "ContactListener.h"
#include "EstadoJuego.h"

class Game
{
private:

    Mundo mundo;

    ContactListener listener;

    EstadoJuego estadoJuego;

    Canon* canon;

    Proyectil* proyectil;

    Sensor* sensor;

    Plataforma piso;
    Plataforma paredIzquierda;
    Plataforma paredDerecha;
    Plataforma techo;
    Plataforma plataformaObjetivo;
    Texture2D fondo;
	Texture2D texturaPlataforma;    

    void CargarRecursos();

    void CrearObjetos();

    void ProcesarControles();

    void Update();

    void Draw();

public:

    Game();

    ~Game();

    void Run();
};

#endif