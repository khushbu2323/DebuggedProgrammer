#include <iostream>
#include <vector>
#include <stack>
#include<stdio.h>
using namespace std;

// This function will check Precedence of input Operators
int GetOperatorPrecedence(std::string &Operator)
{
    if (Operator == "+" || Operator == "-")
        return 1;

    return 2;
}

//This will calculate values
int Calculator(int Operand1, int Operand2, const std::string &Operator)
{
    if (Operator == "+")
        return Operand1 + Operand2;
    if (Operator == "-")
        return Operand1 - Operand2;
    if (Operator == "*")
        return Operand1 * Operand2;
    if (Operator == "/")
        return Operand1 / Operand2;
    return -1;
}

// This function will pick the values and operator for calculation
void PerformCalculation(std::stack<int> &Operands, std::stack<std::string> &operators) {
    int val1 = Operands.top();
    Operands.pop();
    int val2 = Operands.top();
    Operands.pop();
    std::string Oprtr = operators.top();
    operators.pop();
    Operands.push(Calculator(val2, val1, Oprtr));
}

int ReversePolishNotation(std::vector<std::string> &Input) {

    std::stack<int> Operands;
    std::stack<std::string> operators;

    if (Input.empty())
        return 0;

    Operands.push(stoi(Input[0]));

    for (int i = 1; i < Input.size(); i+=2)
    {
        while (!operators.empty() && GetOperatorPrecedence(operators.top()) >= GetOperatorPrecedence(Input[i]))
            PerformCalculation(Operands, operators);

        Operands.push(std::stoi(Input[i+1]));
        operators.push(Input[i]);
    }

    while (!operators.empty())
        PerformCalculation(Operands, operators);

    return Operands.top();
}

std::vector<std::string> parse(const std::string& input)
{
    std::vector<std::string> Vectr;

    std::string Temp;

    for (char c : input)
    {
        if (isdigit(c))
            Temp += c;
        else if (c)
        {
            if (!Temp.empty())
            {
                Vectr.emplace_back(std::move(Temp));
                Temp = "";
            }

            if (c != ' ')
                Vectr.emplace_back(1, c);
        }
    }

    if (!Temp.empty())
        Vectr.push_back(std::move(Temp));

    return Vectr;
}

int main() {
    std::string input;
    std::cout<<"please Enter space seprated integer and operators for calculation"<<std ::endl;
    std::getline(std::cin, input);
    std::vector<std::string> Input = parse(input);
    std::cout<<"Result is : ";
    std::cout << ReversePolishNotation(Input) << '\n';
}