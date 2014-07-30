/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/


#include "identifier_argument.h"

#include <cstdlib>

IdentifierArgument::IdentifierArgument(IdentifierInformation *information)
    : InstructionArgument(INSTRUCTION_ARGUMENT_TYPE_IDENTIFIER)
{
    setIdentifierInformation(information);
}

void IdentifierArgument::setIdentifierInformation(IdentifierInformation *information)
{
    this->information_ = information;
}

IdentifierInformation *IdentifierArgument::getIdentifierInformation()
{
    return this->information_;
}

void IdentifierArgument::debug(CodeGeneratorDebugger * codeGeneratorDebugger)
{
    const char *str = information_->getIdentifier();

    codeGeneratorDebugger->debugCode(str);

}

void IdentifierArgument::debug(ostream &out)
{
    const char *str = information_->getIdentifier();

    out << str;

}
