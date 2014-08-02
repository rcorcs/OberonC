/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#include "debugger_utils.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>

char * getDebugFileName(const char *baseFileName, const char *extension)
{
    const char *baseFileExtension = strrchr(baseFileName, '.');
    size_t debugFileExtensionLen = strlen(extension) + 1 ; //  '.' + extension

    char *debugFileName;

    if(baseFileExtension != NULL)
    {
        // [baseFileName]'.'
        size_t baseFileNameLen = (size_t)baseFileExtension  - (size_t)baseFileName;

        debugFileName = new char[baseFileNameLen + debugFileExtensionLen + 1];

        // baseFileName + '.'
        strncpy(debugFileName, baseFileName, baseFileNameLen+1);
        debugFileName[baseFileNameLen+1] = '\0';

        // extension + '\0'
        strcat(debugFileName, extension);
    }
    else
    {
        size_t baseFileNameLen = strlen(baseFileName);

        // baseFileName + '.' + extension  + '\0'
        debugFileName = new char[baseFileNameLen + debugFileExtensionLen + 1];
        sprintf(debugFileName, "%s.%s", baseFileName, extension);
    }

    return debugFileName;


}
