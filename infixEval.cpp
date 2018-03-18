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
const string infixEval::OPERATORS = "+-*%/()[]{}";
const string infixEval::OPENING = "([{";
const string infixEval::PAREN = "()[]{}";

bool infixEval::isOperator(char op){
    //return 1 if op exists in operators string, 0 if not
    return OPERATORS.find(op) != string::npos;
}

bool infixEval::isOpening(char pa){
    return OPENING.find(pa) != string::npos;
}

bool infixEval::isParen(char pa){
    return PAREN.find(pa) != string::npos;
}

int infixEval::precedence(char op){
    //return the value at order index of op in operator string
    return ORDER[OPERATORS.find(op)];
}

int infixEval::evalOperands(char operate){
//Evaluates a single operation using the current operator and the top two
//items from the operand stack
    if (operandStack.empty())
    {
        throw errorHandle("Stack is empty");
    }
    int result = 0;
    int rightOp = operandStack.top();
    operandStack.pop();
    if (operandStack.empty())
        throw errorHandle("Stack is empty");
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
            if (rightOp==0)
                throw errorHandle("Cannot divide by zero");
            result += leftOP / rightOp;
            break;
        case '%':
            result += leftOP % rightOp;
            break;
    }
    return result;

}

int infixEval::eval(const string& infixEx){

    stringstream tokens(infixEx);
    //use b char to avoid conflict with error handling that uses prev
    char next, prev = 'b', prev2='b';
    //Travel through tokens of string till end
    while(tokens >> noskipws >> next){
        if(!isOperator(next)){
            int num = next - '0';
            //Convert to int as otherwise it uses ASCII index for math
            if(prev==char(32) && !isOperator(prev2) && prev2!='b')
            {
                throw errorHandle("Two operands in a row.");
            }
            if(!isOperator(prev) && prev != 'b'){
                //Checks if previous token was an int so it can handle numbers with >1 digits
                int tens = (operandStack.top() * 10);
                operandStack.pop();

                int res = tens + num;
                operandStack.push(res);
            }
            else{
                operandStack.push(num);
            }

        }else if(next == '}' || next == ']' || next == ')'){
            //Switch to deal with parentheses
            if (operatorStack.empty()){
                throw errorHandle("Expression can't start with a closing parenthesis.");
            }
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
            if (isOperator(prev) && isParen(prev)){
                throw errorHandle("Can't have two binary operators in a row.");
            }
            else if(operatorStack.empty() || precedence(next) > precedence(operatorStack.top()) || isOpening(next)){
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
            prev2=prev;
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
