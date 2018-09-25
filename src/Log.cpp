/*
 * Log.cpp
 *
 *  Created on: 23 sep. 2018
 *      Author: lucio
 */

#define _CRT_SECURE_NO_WARNINGS
#include "../includes/Log.h"
#include <ctime>
#include <string>

using namespace std;
std::string Log::keyName = "";
std::string Log::keyNameComplex = "";
std::ofstream Log::file;
int Log::nivel = 0;

Log::Log(int nivel_)
{
	abrirArchivo("logger.txt", nivel_);
	bool result = this->estaAbierto();
	if (!result)
	{
		// tirar algun error de alguna forma
	}
	setearNivel(nivel_);
}

Log::~Log()
{
	cerrarArchivo();
}

void Log::abrirArchivo(string str, int nivel_)
{
    file.open(str, ios::out | ios::app);
	escribirArchivo("******************************\n***********Logger event level **************\n ************************\n\n");
}

bool Log::estaAbierto()
{
	return file.is_open();
}

void Log::cerrarArchivo()
{
	escribirArchivo("-----------THE END------------\n\n\n");
	file.close();
}

void Log::setearNivel(int nivel_) {
	nivel = nivel_;
}

int Log::getNivel()
{
	return nivel;
}

void Log::escribirArchivo(const char* str)
{
    time_t now = time(0);
    char* dt = ctime(&now);
    std::string cadena = str;
    std::string tiempo = dt;
    std::string msg = tiempo + cadena + "\n";
    const char* mensaje = msg.c_str();
    file.write(mensaje, strlen(mensaje));
	file.flush();
}

void Log::escribirArchivo(char* str)
{
    time_t now = time(0);
    char* dt = ctime(&now);
    std::string cadena = str;
    std::string tiempo = dt;
    std::string msg = tiempo + cadena + "\n";
    const char* mensaje = msg.c_str();
    file.write(mensaje, strlen(mensaje));
	file.flush();
}


// mensajes de Nivel 2
void Log::juegoCerrandoseCorrectamente()
{
	int i = getNivel();
	switch (i) {
	case 1: return;
	}
	const char* mensaje = "El programa se está cerrando\n";
	escribirArchivo(mensaje);
}

void Log::texturaDestruida()
{
	int i = getNivel();
	switch (i) {
	case 1: return;
	case 2: return;
	}
	const char* mensaje = "Textura destruida\n";
	escribirArchivo(mensaje);
}

void Log::imagenRenderizadaConExito(std::string path)
{
	int i = getNivel();
	switch (i) {
	case 1: return;
	case 2: return;
	}

	std::string msj = "Imagen renderizada con éxito: ";
	std::string mensaje = msj + path;
    const char* msg_string = mensaje.c_str();
    escribirArchivo(msg_string);
}

void Log::juegoInicializado()
{
	int i = getNivel();
	switch (i) {
	case 1: return;
	}
	const char* mensaje = "Juego inicializado\n";
	escribirArchivo(mensaje);
}

void Log::ventanaCreada()
{
	int i = getNivel();
	switch (i) {
	case 1: return;
	case 2: return;
	}
	const char* mensaje = "Ventana creada\n";
	escribirArchivo(mensaje);
}

void Log::renderCreado()
{
	int i = getNivel();
	switch (i) {
	case 1: return;
	case 2: return;
	}
	const char* mensaje = "Render creado\n";
	escribirArchivo(mensaje);
}

void Log::errorInicializandoSDL(const char* error)
{
    std::string msg_err = error;
    std::string msg = "Error incializando SDL: ";
    std::string mensaje = msg + msg_err;
    const char* msg_string = mensaje.c_str();
    escribirArchivo(msg_string);
}

void Log::errorCreandoVentana(const char* error)
{
    std::string msg_err = error;
    std::string msg = "Error creando ventana en SDL: ";
    std::string mensaje = msg + msg_err;
    const char* msg_string = mensaje.c_str();
    escribirArchivo(msg_string);
}

void Log::errorCreandoRenderer(const char* error)
{
    std::string msg_err = error;
    std::string msg = "Error creando renderer SDL: ";
    std::string mensaje = msg + msg_err;
    const char* msg_string = mensaje.c_str();
    escribirArchivo(msg_string);
}

void Log::errorCargandoImagen(const char* error, std::string path)
{
    std::string msg_err = error;
    std::string msg = "Error cargando imagen del directorio ";
    std::string full_msg = " en SDL: ";
    std::string mensaje = msg + path + full_msg + msg_err;
    const char* msg_string = mensaje.c_str();
    escribirArchivo(msg_string);
}

void Log::errorCreandoTextura(const char* error, std::string path)
{
    std::string msg_err = error;
    std::string msg = "Error creando textura del directorio ";
    std::string full_msg = " en SDL: ";
    std::string mensaje = msg + path + full_msg + msg_err;
    const char* msg_string = mensaje.c_str();
    escribirArchivo(msg_string);
}

void Log::errorInicializandoSdlImage(const char* error)
{
    std::string msg_err = error;
    std::string msg = "Error inicializando SDL_Image: ";
    std::string mensaje = msg + msg_err;
    const char* msg_string = mensaje.c_str();
    escribirArchivo(msg_string);
}

void Log::infoDeEvento(const char* tecla)
{
    int i = getNivel();
	switch (i) {
	case 1: return;
	case 2: return;
	}
	const char* key = keyName.c_str();
	if (strcmp(key, tecla) == 0) return;
    std::string msg = "Se realizo el siguiente movimiento: ";
    std::string aux = tecla;
    std::string mensaje = msg + aux + "\n";
    escribirArchivo(mensaje.c_str());
    keyName = tecla;
}


void Log::jugadorCreado()
{
    int i = getNivel();
	switch (i) {
        case 1: return;
        case 2: return;
	}
	escribirArchivo("Jugador creado exitosamente\n");

}


