#include <print>
#include <cmath>
#include <cstddef>
#include <cstring>
#include <stdexcept>

template <typename T>
class Vector {
private:
    size_t capacity;
    size_t len;
    T *ptr;

public:
    Vector(size_t cap): capacity { std::max(capacity, 1uz) } , len { 0 } {
        ptr = new T[cap];
    }

    void push(T t) {
        insert(len, t);
    }

    T pop() {
        return remove(len - 1);
    }

    void resize(size_t size) {
        if (size == len) {
            return;
        }
        const auto old_len = len;
        capacity = size;
        if (size < old_len) {
            len = size;
        }
        auto new_ptr = new T[capacity];
        std::memcpy((void *)new_ptr, ptr, std::min(len, old_len) * sizeof(T));
        delete[] ptr;
        ptr = new_ptr;
    }

    void insert(size_t pos, T t) {
        if (pos > len) {
            throw std::out_of_range("idx is more than length");
        }

        if (len == capacity) {
            resize(len * 2);
        }

        std::memmove(ptr + pos + 1, ptr + pos, (len - pos) * sizeof(T));
        len++;

        ptr[pos] = t;
    }

    T remove(size_t pos) {
        if (pos >= len) {
            throw std::out_of_range("idx is more than length");
        }

        auto copy = std::move(ptr[pos]);
        ptr[len].~T();
        std::memmove(ptr + pos, ptr + pos + 1, (len - pos) * sizeof(T));
        len--;
        return copy;
    }
    
    std::optional<size_t> find(T t1) const {
        return find([&](T t2) -> bool {
            return t1 == t2;
        });
    }

    std::optional<size_t> find(const auto &check) const {
        for (size_t i = 0; i < len; i++) {
            if (check(ptr[i])) {
                return i;
            }
        }

        return std::nullopt;
    }

    std::optional<size_t> binary_search(const T &t) const {
        size_t min = 0;
        size_t max = len - 1;
        while (min <= max) {
            int i = std::floor((min + max) / 2);
            if (t == ptr[i]) {
                return i;
            } else if (t > ptr[i]) {
                min = i + 1;
            } else if (t < ptr[i]) {
                max = i - 1;
            }
        }

        return std::nullopt;
    }

    T *begin() {
        return ptr;
    }

    T *end() {
        return ptr + len;
    }

    const T *cbegin() const {
        return ptr;
    }

    const T *cend() const {
        return ptr + len;
    }

    size_t size() const {
        return len;
    }

    T &operator[](size_t idx) {
        if (idx >= len) {
            throw std::out_of_range("idx is more than length");
        }
        return ptr[idx];
    }

    T &operator[](size_t idx) const {
        if (idx >= len) {
            throw std::out_of_range("idx is more than length");
        }
        return ptr[idx];
    }
};

template <typename T>
struct std::formatter<Vector<T>> : std::formatter<T> {
    constexpr auto parse(std::format_parse_context& ctx) {
        auto it = ctx.begin();
        if (it != ctx.end() && *it != '}') {
            throw std::format_error("invalid format for Vector");
        }
        return it;
    }

    auto format(const Vector<T>& vec, std::format_context& ctx) const {
        auto out = ctx.out();
        out = std::format_to(out, "[");
        for (size_t i = 0; i < vec.size(); i++)
        {
            ctx.advance_to(out);
            out = std::formatter<T>::format(vec[i], ctx);
            if (i != vec.size() - 1)
            {
                ctx.advance_to(out);
                out = std::format_to(out, ", ");
            }
        }
        return std::format_to(out, "]");
    }
};

int main() {
    Vector<int> vec(5);

    vec.push(5);
    vec.push(10);
    vec.push(9);

    std::sort(vec.begin(), vec.end(), std::less());

    std::println("{}", vec);
    std::println("{}", vec.binary_search(5).value());
}