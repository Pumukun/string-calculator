#include <iostream>

#include "Calculator.hpp"

using namespace std;

int main() {
    Calculator calc;
    string input = "";
    
    cout << "Enter expression:\nPossible operators: {+, -, *, /, ^}\nPress 'q' to quit.\n";
    
    while (1) {
        cout << ">>> ";
        input = "";
        getline(cin, input);
        
        if (input == "q") {
            break;
        }

        calc.set_expression(input);
        calc.calculate();
        cout << calc.get_result() << "\n";
    }

    return 0;
}
