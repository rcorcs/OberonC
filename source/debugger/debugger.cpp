/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#include "debugger.h"

Debugger::Debugger()
{
    this->enabled_ = false;
}

Debugger::~Debugger()
{
    if(this->debugFile_.is_open())
    {
        // Fecha arquivo de debug, caso necessário.
        this->debugFile_.close();
    }
}

void Debugger::start(const char *baseFileName)
{
    this->stop();

    this->createDebugFile(baseFileName);
    this->enabled_ = true;
}

void Debugger::stop()
{
    if(this->debugFile_.is_open())
    {
        this->preCloseDebugFile();

        // Fecha arquivo de debug, caso necessário.
        this->debugFile_.close();

    }

    // Reseta flags de controle I/O.
    this->debugFile_.clear();
    this->enabled_ = false;
}

void Debugger::preCloseDebugFile()
{
    // Do nothing.
}
