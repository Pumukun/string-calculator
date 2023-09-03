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
    Calculator calc("12 - 13 / (4.2 * 3.323) - 2 * 3 -  3.5 * 54 - 16 * 7 + 2");

    vector<Lexeme> xd = calc.lexemes;

    for (auto& i : xd) {
        cout << i.value << " ";
    } cout << "\n\n";
    
    show_stack(calc.number_stack);
    show_stack(calc.operator_stack);

    return 0;
}
