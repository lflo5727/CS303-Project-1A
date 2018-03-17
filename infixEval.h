/////////////////////////////////////////////
//
//                  CS303
//             Od P and Liam F
//     Project 1A - Infix Expression Parser
//
/////////////////////////////////////////////

#ifndef INFIXEVAL_H
#define INFIXEVAL_H
#include "errorHandle.h"
#include <string>
#include <stack>

using namespace std;

class infixEval
{
    private:
        //Data
        stack<char> operatorStack;
        stack<int> operandStack;
        static const int ORDER[];
        static const string OPERATORS;
        static const string OPENING;
        static const string PAREN;


        //Functions
        bool isOperator(char ch);
        bool isOpening(char pa);
        bool isParen(char pa);
        int evalOperands(char operate);
        int precedence(char op);



    public:
        int eval(const string& infixEx);

};

#endif // INFIXEVAL_H
