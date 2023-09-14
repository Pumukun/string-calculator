#include <iostream>

#include "Calculator.hpp"

using namespace std;

void show_stack(stack<Lexeme> lex_stack) {
    while (!lex_stack.empty()) {
        cout << lex_stack.top().value << " ";
        lex_stack.pop();
    } cout << "\n\n";
}

int main() {
    Calculator calc;
    string input;
    
    cout << "Enter expression:\nPossible operators: {+, -, *, /}\n";
    
    while (input != "quit") {
        cout << ">>> ";
        cin >> input;

        calc.set_expression(input);
        cout << calc.get_result() << "\n";
        input = "";
    }

    return 0;
}
