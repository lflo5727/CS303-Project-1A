/////////////////////////////////////////////
//
//                  CS303
//             Od P and Liam F
//     Project 1A - Infix Expression Parser
//
/////////////////////////////////////////////

#ifndef INFIXEVAL_H
#define INFIXEVAL_H
#include <string>
#include <stack>

using namespace std;

class infixEval
{
    private:
        //Data
        stack<char> operatorStack;
        stack<char> operandStack;
        static const int ORDER[];
        static const string OPERATORS;


        //Functions
        bool isOperator(char ch);
        int evalOperands(char operate);
        int precedence(char op);



    public:
        int eval(const string& infixEx);

};

#endif // INFIXEVAL_H
