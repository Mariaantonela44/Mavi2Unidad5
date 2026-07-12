#ifndef ESTADOJUEGO_H
#define ESTADOJUEGO_H 

class EstadoJuego
{
private:

    int estado;

public:

    EstadoJuego();

    void CambiarEstado(int nuevoEstado);

    int ObtenerEstado();

    bool Esperando();

    bool Ejecutando();

    bool EventoDetectado();

    bool Finalizado();
};
#endif