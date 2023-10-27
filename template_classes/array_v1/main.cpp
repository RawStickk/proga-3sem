#include <iostream>

template <typename T>
class Array
{
public:
    // ������ ��������:
    //
    explicit Array(size_t size_, const T& value): m_size(size_), m_data(new T[size_]) {
        for (unsigned i = 0; i < size_; i++) {
            m_data[i] = value;
        }
        std::cout << "Object is created. \n";
    }
    //   ����������� ������, ������� �������
    //   Array ������� size, ����������� ����������
    //   value ���� T. �������� ��� � ���� T ����
    //   �����������, ������� ����� ������� ���
    //   ��� ����������, ���� �� ��� �� �����.
    //
    Array(const Array &other):m_size(other.m_size), m_data(new T[m_size]) {
        for (int i = 0; i < m_size; i++) {
            m_data[i] = other.m_data[i];
        }
    }
    //   ����������� �����������, ������� �������
    //   ����� ���������. ��������, ��� ��� ����
    //   T ��������� �������� ������������.
    //
    Array(Array && other) {
        swap(other);
    }
    //   ����������� �����������
    //
    ~Array() {
        delete[] m_data;
    }
    //   ����������, ���� �� ��� ���������.
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
    //   �������� ����������� ������������.
    //
    Array& operator=(Array && other) {
        swap(other);
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
        //std::cout << "non-const\n";
        return m_data[idx];
    }
    const T& operator[](size_t idx) const {
        //std::cout << "const \n";
        return m_data[idx];
    }
    //   ��� ������ ��������� ������� �� �������.
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
