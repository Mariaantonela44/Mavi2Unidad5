#include "EstadoJuego.h"

EstadoJuego::EstadoJuego()
{
    // 0 = Esperando
    // 1 = Ejecutando
    // 2 = Evento detectado
    // 3 = Finalizado 

    estado = 0;
}

void EstadoJuego::CambiarEstado(int nuevoEstado){
    estado = nuevoEstado;
}

int EstadoJuego::ObtenerEstado(){
    return estado;
}

bool EstadoJuego::Esperando(){
    return estado == 0;
}

bool EstadoJuego::Ejecutando(){
    return estado == 1;
}

bool EstadoJuego::EventoDetectado(){
    return estado == 2;
}

bool EstadoJuego::Finalizado(){
    return estado == 3;
}
