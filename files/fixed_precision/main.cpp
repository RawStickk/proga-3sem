#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

int main()
{
    std::ifstream file("input.txt");
    std::string s;
    while(std::getline(file, s)) {
        std::cout.precision(3);
        std::cout << std::fixed << std::stod(s) << std::endl;
    }
    return 0;
}
