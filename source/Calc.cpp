double Calc (double num1, double num2, int operation)
{
    switch(operation)
    {
        case 1: 
            return num1 + num2;
        case 2: 
            return num1 - num2;
        case 3: 
            return num1 * num2;
        case 4: 
            return num1 / num2;
    }

    return -1;
}