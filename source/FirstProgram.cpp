#include <iostream>
#include <string>

using namespace std;

void Log(string);
void QueryAndPrint();
string Query();
double Calc(double, double, int);

int main()
{
    Log("first C++ program!");

    Log("enter a number");
    double x = stod(Query());
    Log("enter a second number");
    double y = stod(Query());
    Log("enter an operation 1 for +, 2 for -, and so on");
    int op = stoi(Query());

    double result = Calc(x, y, op);

    Log(to_string(result));

    cin.get();
    return 0;
}