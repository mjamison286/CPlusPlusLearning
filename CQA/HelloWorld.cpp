#include <iostream>
#include <string>

int main()
{
    int cases;

    std::cin >> cases;
    std::string s;
    getline(std::cin, s);

    for(int i = 0; i < cases; i++)
    {
        std::string text;
        getline(std::cin, text);
        std::cout << text << std::endl;
    }

    return 0;
}