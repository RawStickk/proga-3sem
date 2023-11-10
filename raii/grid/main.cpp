#include <iostream>
#include <cassert>

template<typename T>
class Grid final
{
public:
    using value_type = T;
    using size_type = unsigned;

    Grid(T *data, size_type y_size , size_type x_size):
        data(data),
        y_size(y_size),
        x_size(x_size){}

    Grid(T const &t): Grid(new T[1]{t}, 1, 1) {}

    Grid(size_type y_size, size_type x_size):
        Grid(new T[y_size * x_size], y_size, x_size){}

    Grid(size_type y_size, size_type x_size, T const &t):
        Grid(y_size, x_size)
    {
        for (T* it = data; it != data + y_size * x_size; it++)
            *it = t;
    }

    Grid(Grid<T> const& src): Grid(new T[src.y_size * src.x_size], src.y_size, src.x_size) {
        for (int item = src.data; item != data + y_size * x_size; item++) {
            item = src.data[item - data];
        }
    }
    Grid(Grid<T> && src) {
        std::swap(this -> data, src.data);
        std::swap(this -> y_size, src.y_size);
        std::swap(this -> x_size, src.x_size);
    }
    Grid<T>& operator=(Grid<T> &src) {
        if(src == *this) return *this;
        Grid<T> tmp = src;
        std::swap(this -> data, tmp.data);
        std::swap(this -> y_size, tmp.y_size);
        std::swap(this -> x_size, tmp.x_size);
        return *this;
    }
    Grid<T>& operator=(Grid<T>&& src) {
        Grid<T> tmp = std::move(src);
        std::swap(this -> data, tmp.data);
        std::swap(this -> y_size, tmp.y_size);
        std::swap(this -> x_size, tmp.x_size);
        return *this;
    }

    ~Grid() {
        delete[] data;
        data = nullptr;
        y_size = 0;
        x_size = 0;
    }

    T operator()(size_type y_idx , size_type x_idx) const
    {
        return data[y_idx * x_size + x_idx];
    }

    T& operator()(size_type y_idx, size_type x_idx)
    {
        return data[y_idx * x_size + x_idx];
    }

    Grid<T>& operator=(T const& t)
    {
        for (auto it = data, end = data + x_size * y_size; it != end; ++it) *it = t;
        return *this;
    }

    class Row {
    public:
        Row(Grid<T> &grid, size_type row): grid_(grid), row_(row) {}

        T& operator[](size_type const &col) {
            return grid_(row_, col);
        }

    private:
        Grid<T> &grid_;
        size_type row_;
    };

    class ConstRow {
    public:
        ConstRow(Grid<T> &grid, size_type row): grid_(grid), row_(row) {}

        T operator[](size_type const &col) const {
            return grid_(row_, col);
        }

    private:
        Grid<T> const &grid_;
        size_type row_;
    };

    Row operator[](size_type row) {
        return Row(*this, row);
    }

    ConstRow operator[](size_type row) const {
        return Row(*this, row);
    }

    size_type get_y_size() const { return y_size; }
    size_type get_x_size() const { return x_size; }

    void output_data() const {
        for (T* it = data; it != data + y_size * x_size; it ++) {
            std::cout << *it << " ";
        }
    }

private:
    T* data;
    size_type y_size, x_size;
} ;

int main()
{
    Grid<float> g(3, 2, 0.0f);
    assert(3 == g.get_y_size());
    assert(2 == g.get_x_size());

    using gsize_t = Grid<int>::size_type;

    for(gsize_t y_idx = 0; y_idx != g.get_y_size(); ++y_idx) {
        for(gsize_t x_idx = 0; x_idx != g.get_x_size(); ++x_idx) {
            assert(0.0f == g[y_idx][x_idx]);
        }
    }

    for(gsize_t y_idx = 0; y_idx != g.get_y_size(); ++y_idx) {
        for(gsize_t x_idx = 0; x_idx != g.get_x_size(); ++x_idx) {
            g[y_idx][x_idx] = 1.0f;
        }
    }

    for(gsize_t y_idx = 0; y_idx != g.get_y_size(); ++y_idx) {
        for(gsize_t x_idx = 0; x_idx != g.get_x_size(); ++x_idx) {
            assert(1.0f == g(y_idx, x_idx));
        }
    }
    return 0;
}

