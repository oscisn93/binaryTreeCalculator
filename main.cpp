#include <string>
#include "Calc.h"
#include "utils.h"


int main()
{
    std::string welcome_msg{"Arithmetic calculator\nType \'q\' to quit"};
    std::string exit_msg{"Thanks for trying out my calculator\nGoodbye!"};

    printf("%s\n", &welcome_msg);
    // create the calculator object.
    Calc *c = new Calc();
    // expr stores the string representation of the expression
    std::string expr;
    // continuous feedback loop
    while (true)
    {
        printf("Enter Arithmetic Expression: ");
        scanf("%s", &expr);
        // exit loop if q was typed
        if(exitCode(expr))
            break;
        // create the BET using a postfix version
        // of the input prefix expression
        node* exp_tree = c->expressionTree(expr);
        // evaluate the BET
        double n = c->evaluate(exp_tree);
        // print value of expression
        printf(" = %f", n);
    }

    printf("%s\n", &exit_msg);
    return 0;
}
