#include <iostream>

using namespace std;

void Log(const char* message)
{
    cout << message << endl;
}

void Log(string message)
{
    cout << message << endl;
}