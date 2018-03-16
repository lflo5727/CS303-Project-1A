/////////////////////////////////////////////
//
//                  CS303
//             Od P and Liam F
//     Project 1A - Infix Expression Parser
//
/////////////////////////////////////////////
#include "infixEval.h"
#include "errorHandle.h"
#include <string>
#include <stack>
#include <sstream>

const int infixEval::ORDER[] = { 1, 1, 2, 2, 2, -1, -1, -1, -1, -1, -1 };
const string infixEval::OPERATORS = "+-*/%()[]{}";
const string infixEval::OPENING = "([{";

bool infixEval::isOperator(char op){
    //return 1 if op exists in operators string, 0 if not
    return OPERATORS.find(op) != string::npos;
}

bool infixEval::isOpening(char pa){
    return OPENING.find(pa) != string::npos;
}

int infixEval::precedence(char op){
    //return the value at order index of op in operator string
    return ORDER[OPERATORS.find(op)];
}

int infixEval::evalOperands(char operate){
//Evaluates a single operation using the current operator and the top two
//items from the operand stack
    int result = 0;
    int rightOp = operandStack.top();
    operandStack.pop();

    int leftOP = operandStack.top();
    operandStack.pop();

    switch(operate){
        case '+':
            result += leftOP + rightOp;
            break;
        case '-':
            result += leftOP - rightOp;
            break;
        case '*':
            result += leftOP * rightOp;
            break;
        case '/':
            result += leftOP / rightOp;
            break;
        case '%':
            result += leftOP % rightOp;
            break;
    }
    return result;

}

int infixEval::eval(const string& infixEx){

    istringstream tokens(infixEx);
    char next, prev = '+';
    //Travel through tokens of string till end
    while(tokens >> next){
        if(!isOperator(next)){
            int num = next - '0';
            //Convert to int as otherwise it uses ASCII index for math
            if(!isOperator(prev)){
                //Checks if previous token was an int so it can handle numbers with >1 digits
                int tens = (operandStack.top() * 10);
                operandStack.pop();

                int res = tens + num;
                operandStack.push(res);
            }
            else{
                operandStack.push(num);
            }

        }else if(next == '}' || next == '}' || next == ')'){
            //Switch to deal with parentheses
            switch(next){
                case '}':
                    while(!operatorStack.empty()){
                        if(operatorStack.top() == '{')
                           break;
                        char oper = operatorStack.top();
                        operatorStack.pop();

                        int result = evalOperands(oper);
                        operandStack.push(result);
                    }
                    operatorStack.pop();
                    break;
                case ']':
                    while(!operatorStack.empty()){
                        if(operatorStack.top() == '[')
                           break;
                        char oper = operatorStack.top();
                        operatorStack.pop();

                        int result = evalOperands(oper);
                        operandStack.push(result);
                    }
                    operatorStack.pop();
                    break;
                case ')':
                    while(!operatorStack.empty()){
                        if(operatorStack.top() == '(')
                           break;
                        char oper = operatorStack.top();
                        operatorStack.pop();

                        int result = evalOperands(oper);
                        operandStack.push(result);
                    }
                    operatorStack.pop();
                    break;
            }

        }else if(isOperator(next)){
            //Handle operators in the expression

            if(operatorStack.empty() || precedence(next) > precedence(operatorStack.top()) || isOpening(next)){
               operatorStack.push(next);
            }else{
                while(!operatorStack.empty()){
                    char oper = operatorStack.top();
                    operatorStack.pop();

                    int result = evalOperands(oper);
                    operandStack.push(result);
                }
                operatorStack.push(next);
            }
        }
        prev = next;
    }
    while(!operatorStack.empty()){
        char op = operatorStack.top();
        operatorStack.pop();

        int result = evalOperands(op);
        operandStack.push(result);
    }
    int evaluation = operandStack.top();
    operandStack.pop();
    return evaluation;

}
