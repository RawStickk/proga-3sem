#include <iostream>
#include <new>

template <typename T>
class Array
{
public:
    // Список операций:
    //
    explicit Array(size_t size_, const T& value):
        m_size(size_),
        m_data(static_cast<T*>(operator new [](size_ * sizeof(T)))) {

        for (unsigned i = 0; i < size_; i++) {
            new (m_data + i) T(value);
        }
        std::cout << "Object is created. \n";
    }
    //   конструктор класса, который создает
    //   Array размера size, заполненный значениями
    //   value типа T. Для типа T опредеделен конструктор
    //   копирования, про конструктор по умолчанию и
    //   оператор присваивания неизвестно.
    //

    Array (const Array &src): Array(src.m_size, 0) {
        for (unsigned i = 0; i < m_size; i++) {
            new (m_data + i) T(src.m_data[i]);
        }
    }
    //   конструктор копирования, который создает
    //   копию параметра. Считайте, что для типа
    //   T не определен оператор присваивания.
    //
    Array(Array &&src) {
        swap(src);
    }
    //   конструктор перемещения
    //
    ~Array() {
        std::cout << "Object deleted! \n";
        m_data -> ~T();
        operator delete[] (m_data);
        m_data = nullptr;
    }
    //   деструктор, если он вам необходим.
    //
    Array& operator=(const Array &src) {
        if (&src == this) return *this;
        Array tmp(src);
        this -> swap(tmp);
        return *this;
    }
    //   оператор копирующего присваивания.
    //
    Array& operator=(Array && src) {
        swap(src);
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
        return m_data[idx];
    }
    const T& operator[](size_t idx) const {
        return m_data[idx];
    }
    //   две версии оператора доступа по индексу.

    void output() {
        for (unsigned i = 0; i < m_size; i++)
            std::cout << m_data[i] << " ";
        std::cout << "\n";
    }
private:
    void swap(Array& src) {
        std::swap(m_size, src.m_size);
        std::swap(m_data, src.m_data);
    }

    size_t m_size = 0;
    T* m_data = nullptr;
    // поля определите сами
};

int main()
{
    Array<int> a(5, 0);
    a.output();
    for (int i = 0; i < 5; i++) {
        a[i] = (i + 1) * i - 1;
    }
    a.output();
    Array<int> b(std::move(a));
    b.output();
    Array<int> c(5, 0);
    c = std::move(b);
    b.output();
    c.output();
    std::cout << c[0] << std::endl;
}
