#include <iostream>
#include <vector>
#include <map>
#include <stack>
#include <string>
#include <cmath>
#include <cctype>

using namespace std;

bool applyOperator(char op, bool a, bool b = false) {
    if (op == '&') return a && b; 
    if (op == '|') return a || b; 
    if (op == '-') return !a || b; 
    if (op == '!') return !a; 
    return false;
}


bool evaluateExpression(const string &expr, const map<char, bool> &variables) {
    stack<bool> operands;  
    stack<char> operators; 

    for (size_t i = 0; i < expr.size(); ++i) {
        char c = expr[i];
        if (isspace(c)) continue;
        if (isalpha(c)) { 
            operands.push(variables.at(c));
        } else if (c == '(') { 
            operators.push(c);
        } else if (c == ')') { 
            while (!operators.empty() && operators.top() != '(') {
                char op = operators.top(); operators.pop();
                bool val2 = operands.top(); operands.pop();
                bool val1 = (op != '!') ? operands.top() : false;
                if (op != '!') operands.pop();
                operands.push(applyOperator(op, val1, val2));
            }
            operators.pop(); 
        } else if (c == '&' || c == '|' || c == '-' || c == '!') { 
            while (!operators.empty() && operators.top() != '(' && (c != '!' || operators.top() == '!')) {
                char op = operators.top(); operators.pop();
                bool val2 = operands.top(); operands.pop();
                bool val1 = (op != '!') ? operands.top() : false;
                if (op != '!') operands.pop();
                operands.push(applyOperator(op, val1, val2));
            }
            operators.push(c);
        }
    }

    while (!operators.empty()) { 
        char op = operators.top(); operators.pop();
        bool val2 = operands.top(); operands.pop();
        bool val1 = (op != '!') ? operands.top() : false;
        if (op != '!') operands.pop();
        operands.push(applyOperator(op, val1, val2));
    }

    return operands.top();
}


void generateTruthTable(const string &expr, const vector<char> &variables) {
    int numVariables = variables.size();
    int numRows = pow(2, numVariables);


    for (int i = 0; i < numVariables; ++i) {
        cout << variables[i] << "\t";
    }
    cout << "Ket qua\n";


    for (int i = 0; i < numRows; ++i) {
        map<char, bool> assignment;
        for (int j = 0; j < numVariables; ++j) {
            assignment[variables[j]] = (i & (1 << (numVariables - j - 1))) != 0;
            cout << (assignment[variables[j]] ? "T" : "F") << "\t";
        }

        bool result = evaluateExpression(expr, assignment);
        cout << (result ? "T" : "F") << endl;
    }
}

int main() {
    string expression;
    cout << "Nhap bieu thuc logic (vi du: (A & B) -> C): ";
    getline(cin, expression);

    int numVariables;
    cout << "Nhap so luong bien: ";
    cin >> numVariables;

    vector<char> variables(numVariables);
    for (int i = 0; i < numVariables; ++i) {
        cout << "Nhap ten bien thu " << i + 1 << ": ";
        cin >> variables[i];
    }
    generateTruthTable(expression, variables);

    return 0;
}
