/************************************************************************************************************************/
/** A Compiler for a subset of Oberon                                                                                  **/
/** authors:                                                                                                           **/
/**   ROCHA, Rodrigo Caetano de Oliveira (rcor)                                                                        **/
/**   FERREIRA, Wallace Dias                                                                                           **/
/************************************************************************************************************************/

#ifndef GLOBAL_H
#define GLOBAL_H

#include "../oberonc/oberonc.h"

#include "../symbol_table/identifier_information.h"
#include "../symbol_table/scope.h"

#include "../symbol_table/identifier_category/module_information.h"
#include "../symbol_table/identifier_category/function_information.h"
#include "../symbol_table/identifier_category/variable_information.h"
#include "../symbol_table/identifier_category/formal_parameter_information.h"

#include "../ast/declaration/declaration_node.h"
#include "../ast/declaration/skip_declaration_node.h"
#include "../ast/declaration/declaration_sequence_node.h"
#include "../ast/declaration/function_node.h"
#include "../ast/declaration/formal_parameter_node.h"
#include "../ast/declaration/formal_parameter_list_node.h"
#include "../ast/declaration/module_node.h"
#include "../ast/declaration/variable_node.h"

#include "../ast/expression/expression_node.h"
#include "../ast/expression/actual_parameter_list_node.h"
#include "../ast/expression/and_node.h"
#include "../ast/expression/arithmetic_node.h"
#include "../ast/expression/boolean_literal_node.h"
#include "../ast/expression/identifier_node.h"
#include "../ast/expression/integer_literal_node.h"
#include "../ast/expression/function_call_node.h"
#include "../ast/expression/negation_node.h"
#include "../ast/expression/not_node.h"
#include "../ast/expression/or_node.h"
#include "../ast/expression/relational_node.h"
#include "../ast/expression/string_literal_node.h"

#include "../ast/statement/statement_node.h"
#include "../ast/statement/skip_statement_node.h"
#include "../ast/statement/assignment_node.h"
#include "../ast/statement/break_node.h"
#include "../ast/statement/conditional_node.h"
#include "../ast/statement/continue_node.h"
#include "../ast/statement/procedure_call_node.h"
#include "../ast/statement/read_node.h"
#include "../ast/statement/pre_test_loop_node.h"
#include "../ast/statement/post_test_loop_node.h"
#include "../ast/statement/for_loop_node.h"
#include "../ast/statement/return_node.h"
#include "../ast/statement/statement_sequence_node.h"
#include "../ast/statement/write_line_node.h"
#include "../ast/statement/write_node.h"

// Declaração de variáveis compartilhadas.
extern OberonC oberonc;

#endif
