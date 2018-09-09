/*
 * logGenerator.h
 *
 *  Created on: 7 sep. 2018
 *      Author: lucio
 */

#ifndef HEADERS_LOG_H_
#define HEADERS_LOG_H_

#include <string>
#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>
#include <ctime>

enum logLevels {
    LOG_DEBUG = 1,
    LOG_INFO = 2,
    LOG_ERROR = 3,
};

class Log {
    public:
		Log(){}
        virtual ~Log(){}
        virtual std::string toString()=0;

        std::string getFormatedDateTime(const char* format);
        std::string getDate();
        std::string getTime();
        std::string getMessageLevelString(int messageLevel);
        int getLogLevelFromString(std::string level);

        // Escribe en el log
        int log(std::string message, int messageLevel);

        // Funciones sobrecargadas.
        int log(std::string messageToConcatenate, int integerToConcatenate, int messageLevel);
        int log(std::string messageToConcatenate, float floatToConcatenate, int messageLevel);
        int log(std::string messageToConcatenate, double doubleToConcatenate, int messageLevel);
        int log(std::string messageToConcatenate, std::string stringToConcatenate, int messageLevel);
        int log(std::string messageToConcatenate, const char* charsToConcatenate, int messageLevel);
        int log(std::string messageToConcatenate, char* charsToConcatenate, int messageLevel);
        int log(Log* classToConcatenate, int messageLevel);
        int log(std::string messageToConcatenate, Log* classToConcatenate, int messageLevel);

        // Borra el log
        void flushLog();

        // Funciones para el encabezado y pie de archivos.
        int logSessionStarted();
        int logSessionFinished();
};










#endif /* HEADERS_LOG_H_ */
