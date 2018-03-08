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

class infixEval
{
    private:
        //Data
        std::stack<char> opStack;

        //Functions
        int evalOperator(char op);
        int precedence(char op);
        bool isOperator(char ch);


    public:
        infixEval();
};

#endif // INFIXEVAL_H
