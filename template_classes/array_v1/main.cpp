#include <iostream>

template <typename T>
class Array
{
public:
    // Список операций:
    //
    explicit Array(size_t size_, const T& value): m_size(size_), m_data(new T[size_]) {
        for (unsigned i = 0; i < size_; i++) {
            m_data[i] = value;
        }
        std::cout << "Object is created. \n";
    }
    //   конструктор класса, который создает
    //   Array размера size, заполненный значениями
    //   value типа T. Считайте что у типа T есть
    //   конструктор, который можно вызвать без
    //   без параметров, либо он ему не нужен.
    //
    Array(const Array &other):m_size(other.m_size), m_data(new T[m_size]) {
        for (int i = 0; i < m_size; i++) {
            m_data[i] = other.m_data[i];
        }
    }
    //   конструктор копирования, который создает
    //   копию параметра. Считайте, что для типа
    //   T определен оператор присваивания.
    //
    Array(Array && other) {
        swap(other);
    }
    //   конструктор перемещения
    //
    ~Array() {
        delete[] m_data;
    }
    //   деструктор, если он вам необходим.
    //
    void swap(Array& arr) {
        std::swap(m_size, arr.m_size);
        std::swap(m_data, arr.m_data);
    }

    Array& operator=(const Array &other) {
        if (this == &other) return *this;
        Array tmp = other;
        swap(tmp);
        return *this;
    }
    //   оператор копирующего присваивания.
    //
    Array& operator=(Array && other) {
        swap(other);
        return *this;
    }
    //   оператор перемещающего присваивания.
    //
    size_t size_() const {
        return m_size;
    }
    //   возвращает размер массива (количество
    //                              элементов).
    //
    T& operator[](size_t idx) {
        //std::cout << "non-const\n";
        return m_data[idx];
    }
    const T& operator[](size_t idx) const {
        //std::cout << "const \n";
        return m_data[idx];
    }
    //   две версии оператора доступа по индексу.
private:
    size_t m_size = 0;
    T* m_data = nullptr;
};

int main()
{
    const Array<int> arr(3, 1);
    for (unsigned i = 0; i < arr.size_(); i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";
    std::cout << arr.size_() << "\n";
    Array<int> arr1(5, 2);
    Array<int> arr2 = std::move(arr1);
    for (unsigned i = 0; i < arr2.size_(); i++) {
        std::cout << arr2[i] << " ";
    }
    std::cout << "\n";
    std::cout << arr2.size_() << "\n";
}
