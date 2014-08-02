/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/


#include "argument_information.h"
#include <cstring>
#include <cstdlib>

ArgumentInformation::ArgumentInformation()
{
    this->instructionArgument_ = NULL;
    this->setStatus(ARGUMENT_INFORMATION_STATUS_UNDEFINED);

}

ArgumentInformation::~ArgumentInformation()
{


}


InstructionArgument * ArgumentInformation::getInstructionArgument() const
{

    return this->instructionArgument_;
}

void ArgumentInformation::setInstructionArgument(InstructionArgument * instructionArgument)
{

    this->instructionArgument_ = instructionArgument;
}

int ArgumentInformation::getStatus() const
{

    return this->status_;
}
void ArgumentInformation::setStatus(int status)
{

    this->status_ = status;

    switch(status)
    {

    case ARGUMENT_INFORMATION_STATUS_NOT_ALIVE:
        strcpy(this->statusPrefix_, "N");
        break;

    case ARGUMENT_INFORMATION_STATUS_ALIVE_ON_EXIT:
        strcpy(this->statusPrefix_, "S");
        break;

    case ARGUMENT_INFORMATION_STATUS_UNDEFINED:
        strcpy(this->statusPrefix_, "---");
        break;

    default:
        //itoa(status, this->statusPrefix_, 10);
        sprintf(this->statusPrefix_, "%d", status);
        break;
    }
}

const char * ArgumentInformation::getStatusPrefix() const
{

    return this->statusPrefix_;

}

