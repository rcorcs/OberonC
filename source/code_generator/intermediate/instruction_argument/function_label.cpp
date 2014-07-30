/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/


#include "function_label.h"

#include <cstring>
#include <sstream>
using namespace std;

FunctionLabel::FunctionLabel(const char *labelString)
    : LabelArgument(INSTRUCTION_ARGUMENT_TYPE_INSTUCTION_LABEL), labelString_(0)
{
    setLabelString(labelString);
}

FunctionLabel::~FunctionLabel()
{
    delete [] labelString_;
}

void FunctionLabel::setLabelString(const char *labelString)
{
    if(this->labelString_)
    {
        delete [] this->labelString_;
        this->labelString_ = 0;
    }

    if(labelString)
    {
        this->labelString_ = new char[strlen(labelString)+1];
        strcpy(labelString_, labelString);
    }
}

char *FunctionLabel::getLabelString() const
{
    return this->labelString_;
}

void FunctionLabel::debug(CodeGeneratorDebugger * codeGeneratorDebugger)
{
 stringstream strValue;

    strValue << endl <<  labelString_ << ':' << endl << endl;
    codeGeneratorDebugger->debugCode(strValue.str().c_str());
}

void FunctionLabel::debug(ostream &out)
{
 stringstream strValue;

    strValue << endl <<  labelString_ << ':' << endl << endl;
    out << strValue.str().c_str();
}
