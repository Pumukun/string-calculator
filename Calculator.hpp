#pragma once

#include <iostream>
#include <stack>
#include <vector>
#include <cmath>

using namespace std;

struct Lexeme {
    string value;
    char type;
    int priority
};

class Calculator {
public:

    string expression;
    
    vector<Lexeme> lexemes;

    stack<Lexeme> operator_stack, number_stack;

    Calculator(): expression("") {}

    Calculator(string expression): expression(expression) {
        parse_expression();
    }

    ~Calculator() {}

private:
    
    bool is_number(char c) { return c >= '0' && c <= '9'; }
    bool is_operator(char c) { return c == '+ || c == '-' || c == '*' || c == '/'; }

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

                while (pos < (int)expression.length() && is_number(c)) {
                    tmp_str += expression[pos];
                    pos++;
                }

                lexeme.value = tmp_str;
                lexeme.type = 'n';
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
                lexeme.type = 'o';
                
                return lexeme;
            }
        }

        lexeme.value = tmp_str;
        lexeme.type = 'e';
        lexeme.priority = 0;

        return lexeme;
    }

    void parse_expression() {
        Lexeme lexeme; 
        int pos = 0;

        do {
            lexeme = next_lexeme(pos);
            lexemes.push_back(lexeme);
        } while (lexeme.type != 'e');
    }

};
