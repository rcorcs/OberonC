/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#include "string_argument.h"

#include <cstring>
#include <sstream>
using namespace std;

StringArgument::StringArgument(const char *stringValue)
    : InstructionArgument(INSTRUCTION_ARGUMENT_TYPE_STRING), stringValue_(0)
{
    setStringValue(stringValue);
}

StringArgument::~StringArgument()
{
    delete []stringValue_;
}

void StringArgument::setStringValue(const char *stringValue)
{
    delete []stringValue_;

    this->stringValue_ = new char[strlen(stringValue)+1];
    strcpy(this->stringValue_, stringValue);
}

char *StringArgument::getStringValue() const
{
    return this->stringValue_;
}

void StringArgument::debug(CodeGeneratorDebugger * codeGeneratorDebugger)
{
    stringstream strValue;
    strValue <<  this->stringValue_;

    codeGeneratorDebugger->debugCode(strValue.str().c_str());
}

void StringArgument::debug(ostream &out)
{
    stringstream strValue;
    strValue <<  this->stringValue_;

    out << strValue.str().c_str();
}

