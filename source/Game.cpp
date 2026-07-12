#include "Game.h"
#include <cmath>

Game::Game()
{
    InitWindow(1600, 900, "Sistema de Control");
    SetTargetFPS(60);

    mundo.GetWorld()->SetContactListener(&listener);

    CargarRecursos();
    CrearObjetos();
}



Game::~Game()
{
    delete canon;
    delete proyectil;
    delete sensor;

    UnloadTexture(fondo);
    UnloadTexture(texturaPlataforma);

    CloseWindow();
}



void Game::CargarRecursos()
{
    fondo = LoadTexture("assets/fondo3.png");
    texturaPlataforma = LoadTexture("assets/plataforma1.png");

}



void Game::CrearObjetos()
{

    // LIMITES DE PANTALLA

    paredIzquierda.Crear(
        mundo.GetWorld(),
        20,
        450,
        40,
        900,
        texturaPlataforma
    );

    paredDerecha.Crear(
        mundo.GetWorld(),
        1580,
        450,
        40,
        900,
        texturaPlataforma
    );

    techo.Crear(
        mundo.GetWorld(),
        800,
        860,
        1600,
        80,
        texturaPlataforma
    );
    //-------------------------------------------
    piso.Crear(
        mundo.GetWorld(),
        800,
        40,
        1600,
        80,
        texturaPlataforma
    );

    plataformaObjetivo.Crear(
        mundo.GetWorld(),
        1450,
        200,
        350,
        40,
        texturaPlataforma
    );
    sensor = new Sensor(
        mundo.GetWorld(),
        1450,
        600,
        250,
        250
    );


    canon = new Canon(
        150,
        780
    );


    proyectil = new Proyectil(
        mundo.GetWorld(),
        150,
        780,
        15
    );
}



void Game::ProcesarControles()
{
    canon->Actualizar();


    // Disparo
    if (estadoJuego.Esperando())
    {
        if (IsKeyPressed(KEY_SPACE))
        {
            Vector2 punta = canon->ObtenerPunta();


            proyectil->Reiniciar( punta.x, punta.y );


            proyectil->Lanzar( canon->ObtenerAngulo(), 20 );


            estadoJuego.CambiarEstado(1);
        }
    }



    // Reiniciar partida
    if (estadoJuego.Finalizado())
    {
        if (IsKeyPressed(KEY_R))
        {
            listener.ReiniciarSensor();


            proyectil->Reiniciar(150, 780 );


            estadoJuego.CambiarEstado(0);
        }
    }
}


void Game::Update()
{
    mundo.Actualizar();

    if (estadoJuego.Ejecutando())
    {
        // Si entró al sensor
        if (listener.sensorActivado)
        {
            estadoJuego.CambiarEstado(2);
        }
        else
        {
            b2Vec2 vel = proyectil->GetBody()->GetLinearVelocity();

            // Si casi no se mueve, terminar el intento
            if (fabs(vel.x) < 1.0f &&
                fabs(vel.y) < 1.0f)
            {
                proyectil->GetBody()->SetLinearVelocity(b2Vec2_zero);
                proyectil->GetBody()->SetAngularVelocity(0);

                estadoJuego.CambiarEstado(3);
            }
        }
    }

    if (estadoJuego.EventoDetectado())
    {
        estadoJuego.CambiarEstado(3);
    }
}


void Game::Draw()
{
    BeginDrawing();

    ClearBackground(RAYWHITE);

    Rectangle origen = {0, 0, (float)fondo.width, (float)fondo.height};

    Rectangle destino = {  0, 0, 1600, 900};

    DrawTexturePro(fondo, origen, destino, Vector2{ 0, 0 },  0.0f, WHITE);

    piso.Draw();

    plataformaObjetivo.Draw();

    sensor->Dibujar();

    canon->Dibujar();

    proyectil->Dibujar();


    // INFORMACIÓN DEL SISTEMA

    DrawText(TextFormat("Angulo: %.1f grados", canon->ObtenerAngulo()), 20, 20, 25, WHITE);

    DrawText("Potencia: 20", 20, 50, 25, WHITE);

    b2Vec2 vel = proyectil->GetBody()->GetLinearVelocity();

    DrawText(TextFormat("Velocidad X: %.2f", vel.x), 20, 80, 25, WHITE);
    DrawText(TextFormat("Velocidad Y: %.2f", vel.y), 20, 110, 25, WHITE);

    if (listener.sensorActivado)
        DrawText("Sensor: ACTIVADO", 20, 140, 25, BLACK);
    else
        DrawText("Sensor: NO ACTIVADO", 20, 140, 25, RED);


   
    // ESTADO ACTUAL
 

    if (estadoJuego.Esperando())
    {
        DrawText("Estado: ESPERANDO", 20, 190, 30, DARKPURPLE);
        DrawText("SPACE - Disparar", 20, 230, 30, WHITE);
    }

    if (estadoJuego.Ejecutando())
    {
        DrawText("Estado: EJECUTANDO", 20, 190, 30, DARKPURPLE);
        DrawText("El proyectil esta en movimiento", 20, 230, 30, DARKPURPLE);
    }

    if (estadoJuego.EventoDetectado())
    {
        DrawText("Estado: EVENTO DETECTADO", 20, 190, 30, BLACK);
        DrawText("El proyectil entro al sensor", 20, 230, 30, BLACK);
    }

    if (estadoJuego.Finalizado())
    {
        DrawText("Estado: FINALIZADO", 20, 190, 30, RED);

        if (listener.sensorActivado)
            DrawText("OBJETIVO ALCANZADO", 20, 230, 30, BLACK);
        else
            DrawText("OBJETIVO NO ALCANZADO", 20, 230, 30, RED);

        DrawText("Presione R para reiniciar", 20, 270, 30, WHITE);
    }

    EndDrawing();
}



void Game::Run()
{
    while (!WindowShouldClose())
    {
        ProcesarControles();

        Update();

        Draw();
    }
}