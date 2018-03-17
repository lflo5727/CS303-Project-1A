/////////////////////////////////////////////
//
//                  CS303
//             Od P and Liam F
//     Project 1A - Infix Expression Parser
//
/////////////////////////////////////////////

#include <iostream>
#include <string>
#include <stack>
#include "infixEval.h"

using namespace std;

int main()
{
    string expression;
    infixEval evaluator;
    cout << "Please input infix expression to evaluate: \n";
    getline(cin, expression);
    cout << evaluator.eval(expression) << endl;
    return 0;

}
