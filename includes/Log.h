/*
 * Log.h
 *
 *  Created on: 23 sep. 2018
 *      Author: lucio
 */

#ifndef LOG_H_
#define LOG_H_

#include "iostream"
#include "fstream"
#include <string.h>
#include <SDL2/SDL.h>

class Log
{
private:
    static std::ofstream file;
    static int nivel;
    void abrirArchivo(std::string str, int nivel_);
    void cerrarArchivo();
    bool estaAbierto();
    void setearNivel(int nivel_);
    static int getNivel();
    static std::string keyName;
    static std::string keyNameComplex;


public:
// mensajes para Nivel Error
    static void errorInicializandoSDL(const char* error);
    static void errorCreandoVentana(const char* error);
    static void errorCreandoRenderer(const char* error);
    static void errorCargandoImagen(const char* error, std::string path);
    static void errorCreandoTextura(const char* error, std::string path);
    static void errorInicializandoSdlImage(const char* error);


// mensajes para Nivel Info
    static void juegoCerrandoseCorrectamente();
    static void juegoInicializado();



// mensajes para Nivel Debug
    static void imagenRenderizadaConExito();
    static void ventanaCreada();
    static void renderCreado();
    static void equipoCreado();
    static void jugadorCreado();
    static void texturaDestruida();


    Log(int nivel_);
    ~Log();
    static void escribirArchivo(const char* str);
    static void escribirArchivo(char* str);
};



#endif /* LOG_H_ */
