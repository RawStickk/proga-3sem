#include <iostream>
#include <new>

template <typename T>
class Array
{
public:
    // ������ ��������:
    //
    explicit Array(size_t size_, const T& value):
        m_size(size_),
        m_data(static_cast<T*>(operator new [](size_ * sizeof(T)))) {

        for (unsigned i = 0; i < size_; i++) {
            new (m_data + i) T(value);
        }
        std::cout << "Object is created. \n";
    }
    //   ����������� ������, ������� �������
    //   Array ������� size, ����������� ����������
    //   value ���� T. ��� ���� T ����������� �����������
    //   �����������, ��� ����������� �� ��������� �
    //   �������� ������������ ����������.
    //

    Array (const Array &src): Array(src.m_size, 0) {
        for (unsigned i = 0; i < m_size; i++) {
            new (m_data + i) T(src.m_data[i]);
        }
    }
    //   ����������� �����������, ������� �������
    //   ����� ���������. ��������, ��� ��� ����
    //   T �� ��������� �������� ������������.
    //
    Array(Array &&src) {
        swap(src);
    }
    //   ����������� �����������
    //
    ~Array() {
        std::cout << "Object deleted! \n";
        m_data -> ~T();
        operator delete[] (m_data);
        m_data = nullptr;
    }
    //   ����������, ���� �� ��� ���������.
    //
    Array& operator=(const Array &src) {
        if (&src == this) return *this;
        Array tmp(src);
        this -> swap(tmp);
        return *this;
    }
    //   �������� ����������� ������������.
    //
    Array& operator=(Array && src) {
        swap(src);
        return *this;
    }
    //   �������� ������������� ������������.
    //
    size_t size_() const {
        return m_size;
    }
    //   ���������� ������ ������� (����������
    //                              ���������).
    //
    T& operator[](size_t idx) {
        return m_data[idx];
    }
    const T& operator[](size_t idx) const {
        return m_data[idx];
    }
    //   ��� ������ ��������� ������� �� �������.

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
    // ���� ���������� ����
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
