//
// Created by Oscar Cisneros on 12/07/19.
//

#ifndef CALC_CALC_H
#define CALC_CALC_H

#include <string>

struct node {
    std::string data;
    node *left = nullptr;
    node *right = nullptr;
    bool isLeaf = false;
};

class Calc {
public:
    double evaluate(node *exp_tree);
    node *expressionTree(std::string expr);
private:
    std::string prefixToPostfix(std::string s);
    double operations(std::string op_code, double a, double b, int f);
};


#endif //CALC_CALC_H
