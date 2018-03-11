/////////////////////////////////////////////
//
//                  CS303
//             Od P and Liam F
//     Project 1A - Infix Expression Parser
//
/////////////////////////////////////////////
#include "infixEval.h"
#include <string>
#include <stack>

const int infixEval::ORDER[] = { 1, 1, 2, 2, 2, -1, -1, -1, -1, -1, -1 };
const string infixEval::OPERATORS = "+-*/%()[]{}";

bool infixEval::isOperator(char op){
    //return 1 if op exists in operators string, 0 if not
    return OPERATORS.find(op) != string::npos;
}

int infixEval::precedence(char op){
    //return the value at order index of op in operator string
    return ORDER[OPERATORS.find(op)];
}

int infixEval::evalOperands(char operate){
/*
    pop top two from operands
    throw error if stack is empty
    depending on operator, return result of operand1 operator operand2
*/


}

int infixEval::eval(const string& infixEx){
/*
while characters to read are left:
    if char is operand or ( , push to stack

    else if char is operator:
        while top operator is larger precedence to char
            pop top of operators
            pop top two from operands
            push result of operands and operator to operand stack

    else if ):
        while top operand is not (
            pop top of operators
            pop top two from operands
            push result of operands and operator to operand stack

return top operand
*/


}