#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>

class ReadCSV {
public:
    ReadCSV() = delete;

    ReadCSV(std::string const &file): m_fileName(file) {
        std::ifstream fin(m_fileName);

        std::string s;

        std::getline(fin, s, ' ');
        m_rows = std::stoi(s);

        std::getline(fin, s);
        m_columns = std::stoi(s);

        for (int i = 0; i < m_rows; i++) {
            std::getline(fin, s);
            std::istringstream is(s);
            for (int j = 0; j < m_columns; j++) {
                std::getline(is, s, ',');
                m_data.push_back(s);
            }
        }
    }

    void output() {
        for (int i = 0; i < m_rows; i++) {
            for (int j = 0; j < m_columns; j++) {
                std::cout << std::setw(m_width) << m_data[i * m_columns + j];
                if (j != m_columns - 1) std::cout << " ";
            }
            std::cout << std::endl;
        }
    }

private:
    std::string m_fileName;
    int m_rows, m_columns;
    int m_width = 10;
    std::vector<std::string> m_data;
};

int main()
{
    ReadCSV file("file.txt");
    file.output();
    return 0;
}
