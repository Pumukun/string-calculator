#pragma once

#include <iostream>
#include <stack>
#include <vector>
#include <cmath>

using namespace std;

enum Type {
    NUMBER,
    OPERATOR,
    OPENPH,
    CLOSEPH,
    END
};

struct Lexeme {
    string value;
    Type type;
    int priority;
};

class Calculator {
public:

    string expression;
    
    vector<Lexeme> lexemes;

    stack<Lexeme> operator_stack, number_stack;

    Calculator(): expression("") {}

    Calculator(string expression): expression(expression) {
        parse_expression();
        evaluate();
    }

    ~Calculator() {}

private:
    
    bool is_number(char c) { return c >= '0' && c <= '9' || c == '.'; }
    bool is_operator(char c) { return c == '+' || c == '-' || c == '*' || c == '/'; }
    bool is_ph_o(char c) { return c == '('; }
    bool is_ph_c(char c) { return c == ')'; }

    Lexeme next_lexeme(int &pos) {
        Lexeme lexeme;
        string tmp_str = "";

        while (pos < (int)expression.length()) {
            char c = expression[pos];

            if (c == ' ' || c == '\t' || c == '\r') {
                pos++;
                continue;
            }

            if (is_number(c)) {
                tmp_str += c;
                pos++;

                while (is_number(expression[pos]) && pos < (int)expression.length()) {
                    tmp_str += expression[pos];
                    pos++;
                }

                lexeme.value = tmp_str;
                lexeme.type = NUMBER;
                lexeme.priority = 0;

                return lexeme;
            }

            if (is_operator(c)) {
                tmp_str += c;
                pos++;

                if (c == '+' || c == '-') {
                    lexeme.priority = 1;
                } else {
                    lexeme.priority = 2;
                }

                lexeme.value = tmp_str;
                lexeme.type = OPERATOR;
                
                return lexeme;
            }

            if (is_ph_o(c)) {
                tmp_str += c;
                pos++;

                lexeme.value = tmp_str;
                lexeme.type = OPENPH;
                lexeme.priority = 0;

                return lexeme;
            }

            if (is_ph_c(c)) {
                tmp_str += c;
                pos++;

                lexeme.value = tmp_str;
                lexeme.type = CLOSEPH;
                lexeme.priority = 0;

                return lexeme;

            }
        }

        lexeme.value = tmp_str;
        lexeme.type = END;
        lexeme.priority = 0;

        return lexeme;
    }

    void parse_expression() {
        Lexeme lexeme; 
        int pos = 0;

        do {
            lexeme = next_lexeme(pos);
            lexemes.push_back(lexeme);
        } while (lexeme.type != END);
    }

    Lexeme eval_binary(float num_1, float num_2, char operation) {
        Lexeme res;
        switch (operation) {
            case '+':
                res.value = to_string(num_1 + num_2);
                res.type = NUMBER;
                res.priority = 0;
                return res;
            case '-':
                res.value = to_string(num_2 - num_1);
                res.type = NUMBER;
                res.priority = 0;
                return res;
            case '*':
                res.value = to_string(num_1 * num_2);
                res.type = NUMBER;
                res.priority = 0;
                return res;
            case '/':
                res.value = to_string(num_2 / num_1);
                res.type = NUMBER;
                res.priority = 0;
                return res;
        }
    }

    void evaluate() {
        for (Lexeme& lex : lexemes) {
            if (lex.type == NUMBER) {
                number_stack.push(lex);
            }

            if (lex.type == OPERATOR) {
                if (operator_stack.empty()) {
                    operator_stack.push(lex);
                } else {
                    while (!operator_stack.empty() && lex.priority <= operator_stack.top().priority) {
                        if (operator_stack.top().type == OPENPH) {
                            break;
                        }
                    
                        float num_1 = stof(number_stack.top().value); number_stack.pop();
                        float num_2 = stof(number_stack.top().value); number_stack.pop();

                        char operation = operator_stack.top().value[0]; operator_stack.pop();

                        Lexeme res = eval_binary(num_1, num_2, operation);
                        number_stack.push(res);
                    }
                    operator_stack.push(lex);
                }
            }

            if (lex.type == OPENPH) {
                operator_stack.push(lex);
            }

            if (lex.type == CLOSEPH) {
                while (!operator_stack.empty() && operator_stack.top().type != OPENPH) {
                    float num_1 = stof(number_stack.top().value); number_stack.pop();
                    float num_2 = stof(number_stack.top().value); number_stack.pop();

                    char operation = operator_stack.top().value[0]; operator_stack.pop();

                    Lexeme res = eval_binary(num_1, num_2, operation);
                    number_stack.push(res);
                }

                if (!operator_stack.empty() && operator_stack.top().type == OPENPH) {
                    operator_stack.pop();
                } else {
                    cout << "Error: Unmatched parentheses" << endl;
                    return;
                }
            }
        }

        while (!operator_stack.empty()) {
            if (operator_stack.top().type == OPENPH || operator_stack.top().type == CLOSEPH) {
                cout << "Error: Unmatched parentheses" << endl;
                return;
            }

            float num_1 = stof(number_stack.top().value); number_stack.pop();
            float num_2 = stof(number_stack.top().value); number_stack.pop();

            char operation = operator_stack.top().value[0]; operator_stack.pop();

            Lexeme res = eval_binary(num_1, num_2, operation);
            number_stack.push(res);
        }

        if (number_stack.size() == 1) {
            cout << "Result: " << number_stack.top().value << endl;
        } else {
            cout << "Error: Invalid expression" << endl;
        }
    }
    
};
