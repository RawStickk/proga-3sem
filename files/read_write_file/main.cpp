#include <iostream>
#include <fstream>
#include <string>

int main()
{
    std::string s;
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");
    while (std::getline(fin, s)) {
        std::cout << s << std::endl;
        fout << s << '\n';
    }
    return 0;
}
