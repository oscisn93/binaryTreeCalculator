//
// Created by Oscar Cisneros on 12/07/19.
//

#include "Calc.h"
#include <stack>
#include "utils.h"

node *newNode(std::string value, bool isNum)
{
    node *treeNode = new node();
    treeNode->data = value;
    treeNode->isLeaf = isNum;
    return  treeNode;
}

node *Calc::expressionTree(std::string expr)
{
    std::stack<node *> sp;
    node *parent, *rightChild, *leftChild;
    int len = expr.length();
    for(int i=0; i<len; i++)
    {
        std::string s = castString(s[i]);
        if(isNum(s)) {
                // get whole num(including decimals) by aggregating onto str_c
                //  and changing the index to the last value
                int k = i+1;
                std::string n = castString(s[k]);
                while (isNum(n) || n == ".") {
                    i = k;
                    s += n;
                    k++;
                    n = castString(s[k]);
                }
                parent = newNode(s, false);
                sp.push(parent);
        } else {
            parent = newNode(s, true);
            leftChild = sp.top();
            sp.pop();
            rightChild = sp.top();
            sp.pop();

            parent->left = leftChild;
            parent->right = rightChild;

            sp.push(parent);
        }
    }
    parent = sp.top();
    sp.pop();

    return parent;
}

double Calc::evaluate(node *et)
{
    if(et != NULL)
    {
        if(et->isLeaf)
            return castDouble(et->data);
        double a = evaluate(et->left);
        double b = evaluate(et ->right);
        int f = findF(a, b);
        return operations(et->data, a, b, f);
    }
}

double Calc::operations(std::string op_code, double a, double b, int f)
{
    if (op_code =="*")
        return a * b;
    else if (op_code =="/")
        return a / b;
    else{
        a*=f;
        b*=f;
        if (op_code =="-")
            return (a-b)/f;
        else
            return (a+b)/f;
    }
}

std::string Calc::prefixToPostfix(std::string s)
{
    std::stack<std::string> sp;
    sp.push("#");
    std::string str_c;
    std::string new_str;
    int len = s.length();
    // c is a char- str_c is the string version(used by the stack)
    for(int i = 0; i< len; i++)
    {
        str_c = castString(s[i]);
        if(isNum(str_c)) {
            // get whole num(including decimals) by aggregating onto str_c
            //  and changing the index to the last value
            int k = i+1;
            std::string n = castString(s[k]);
            while (isNum(n) || n == ".") {
                i = k;
                str_c += n;
                k++;
                n = castString(s[k]);
            }
            // push the whole number onto the stack
            sp.push(str_c);
        }else{
            if(str_c == "(")
                sp.push("(");
            else if(str_c == ")")
            {
                while (sp.top() != "(" && sp.top() != "#'" ){
                    std::string b = sp.top();
                    sp.pop();
                    new_str += b;
                }
                if(sp.top() =="(")
                    sp.pop();
            }
            else {
                while(sp.top() != "#" && pemdas(str_c) <= pemdas(sp.top())){
                    std::string b = sp.top();
                    sp.pop();
                    new_str += b;
                }
                sp.push(str_c);
            }
        }
        while(sp.top() != "#")
        {
            std::string b = sp.top();
            sp.pop();
            new_str += b;
        }
        return new_str;
    }
}