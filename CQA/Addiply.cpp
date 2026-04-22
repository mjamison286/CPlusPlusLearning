#include <iostream>
#include <string>

int main()
{
    int cases;
    std::cin >> cases;
    std::string s;
    std::getline(std::cin, s);

    for(int i = 0; i < cases; i++)
    {
        std::string input;
        std::getline(std::cin, input);

        int num1 = std::stoi(input.substr(0, input.find(" ")));
        int num2 = std::stoi(input.substr(input.find(" ") + 1));

        std::cout << (num1 + num2) << " " << (num1 * num2) << std::endl;
    }


    return 0;
}