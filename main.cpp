#include "Operands.h"
#include "Operator.h"
#include "OperatorFactory.h"

#include <string>
#include <vector>
#include <stack>
#include <memory>
#include <cctype>
#include <stdexcept>
#include <iostream>

using std::unique_ptr;

Token * parseNumber(const std::string & s, size_t & i){
    size_t start = i;
    bool isFloat = false;
    while(i < s.size() && (std::isdigit((unsigned char)s[i]) || s[i] == '.')){
        if(s[i] == '.') isFloat = true;
        ++i;
    }
    std::string num = s.substr(start, i - start);
    if(isFloat) return new FloatOperand(std::stod(num));
    return new IntegerOperand(std::stoll(num));
}


std::vector<Token*> toPostfix(const std::string & expr){
    std::vector<Token*> output;
    std::stack<Operator*> ops;   

    size_t i = 0;
    while(i < expr.size()){
        char c = expr[i];
        if(std::isspace((unsigned char)c)){ ++i; continue; }

        if(std::isdigit((unsigned char)c) || c == '.'){
            output.push_back(parseNumber(expr, i));
        }
        else if(c == '('){
            ops.push(nullptr);
            ++i;
        }
        else if(c == ')'){
            while(!ops.empty() && ops.top() != nullptr){
                output.push_back(ops.top());
                ops.pop();
            }
            if(ops.empty()) throw std::runtime_error("Mismatched parentheses");
            ops.pop();
            ++i;
        }
        else if(OperatorFactory::isOperator(c)){
            Operator * curr = OperatorFactory::get(c);
            while(!ops.empty() && ops.top() != nullptr){
                Operator * top = ops.top();
               
                bool popTop =
                    (top->getPrecedence() < curr->getPrecedence()) ||
                    (top->getPrecedence() == curr->getPrecedence() &&
                     curr->getAssociativity() == Associativity::LEFT);
                if(!popTop) break;
                output.push_back(top);
                ops.pop();
            }
            ops.push(curr);
            ++i;
        }
        else{
            throw std::runtime_error(std::string("Invalid char: ") + c);
        }
    }
    while(!ops.empty()){
        if(ops.top() == nullptr) throw std::runtime_error("Mismatched parentheses");
        output.push_back(ops.top());
        ops.pop();
    }
    return output;
}


unique_ptr<Operands> evalPostfix(std::vector<Token*> & postfix){
    std::stack<Operands*> st;   

    for(Token * tok : postfix){
        if(!tok->isOperator()){
            st.push(static_cast<Operands*>(tok));
        } else {
            if(st.size() < 2) throw std::runtime_error("Malformed expression");
            Operands * right = st.top(); st.pop();   
            Operands * left  = st.top(); st.pop();  

            
            unique_ptr<Operands> result = static_cast<Operator*>(tok)
                                              ->operate(*left, *right);

            delete left;   
            delete right;

            st.push(result.release());  
        }
    }
    if(st.size() != 1) throw std::runtime_error("Malformed expression");
    return unique_ptr<Operands>(st.top());  
}

unique_ptr<Operands> evaluate(const std::string & expr){
    std::vector<Token*> postfix = toPostfix(expr);
    return evalPostfix(postfix);
}

int main(){
    const char * tests[] = {
        "3 + 4 * 2",        // 11
        "(3 + 4) * 2",      // 14
        "10 / 4",           // 2   
        "10.0 / 4",         // 2.5 
        "2 + 3.5 * 2",      // 9
        "100 - 20 - 5"      // 75  
    };

    for(const auto & t : tests){
        try{
            unique_ptr<Operands> result = evaluate(t);
            std::cout << t << " = ";
            result->printValue();
            std::cout << "\n";
        } catch(const std::exception & e){
            std::cout << t << " -> Error: " << e.what() << "\n";
        }
    }
    return 0;
}
