/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#ifndef DEBUGGER_H
#define DEBUGGER_H

#include "debugger_utils.h"
#include <fstream>
using namespace std;

class Debugger
{

public:

    Debugger();
    virtual ~Debugger();

    void start(const char *baseFileName);
    void stop();

protected:

    virtual void createDebugFile(const char *baseFileName) = 0;
    virtual void preCloseDebugFile();

    bool enabled_;
    ofstream debugFile_;

};


#endif
