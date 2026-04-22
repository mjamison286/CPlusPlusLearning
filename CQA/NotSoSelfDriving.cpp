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
        getline(std::cin, input);

        std::string s1 = input.substr(0, input.find(":"));
        std::string s2 = input.substr(input.find(":") + 1);

        float f1 = std::stof(s1);
        float f2 = std::stof(s2);

        float result;

        if(f1 != 0)
        {
            result = f2/f1;
        }
        else 
        {
            result = 1000;
        }

        if(result <= 1)
        {
            std::cout << "SWERVE" << std::endl;
        } 
        else if(result < 5)
        {
            std::cout << "BRAKE" << std::endl;
        }
        else
        {
            std::cout << "SAFE" << std::endl;
        }
    }

    return 0;
}