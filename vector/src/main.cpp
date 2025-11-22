#include <print>
#include <cstddef>
#include <cstring>
#include <stdexcept>

template <typename Type>
class Vector {
    private:
    std::size_t capacity;
    std::size_t len;
    Type *ptr;

    public:
    Vector(size_t cap): capacity { std::max(capacity, 1uz) } , len { 0 } {
        ptr = new Type[cap];
    }

    void push(Type t) {
        insert(len, t);
    }

    Type pop() {
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
        auto new_ptr = new Type[capacity];
        std::memcpy((void *)new_ptr, ptr, std::min(len, old_len) * sizeof(Type));
        delete[] ptr;
        ptr = new_ptr;
    }

    void insert(size_t pos, Type t) {
        if (pos > len) {
            throw std::out_of_range("idx is more than length");
        }

        if (len == capacity) {
            resize(len * 2);
        }

        std::memmove(ptr + pos + 1, ptr + pos, (len - pos) * sizeof(Type));
        len++;

        ptr[pos] = t;
    }

    Type remove(size_t pos) {
        if (pos >= len) {
            throw std::out_of_range("idx is more than length");
        }

        auto copy = std::move(ptr[pos]);
        ptr[len].~Type();
        std::memmove(ptr + pos, ptr + pos + 1, (len - pos) * sizeof(Type));
        len--;
        return copy;

    }

    size_t size() const {
        return len;
    }

    Type &operator[](std::size_t idx) {
        if (idx >= len) {
            throw std::out_of_range("idx is more than length");
        }
        return ptr[idx];
    }
};

int main() {
    Vector<int> vec(5);

    vec.push(5);
    vec.push(5);
    vec.push(5);
    vec.resize(10);
    vec.insert(2, 9);

    auto size = vec.size();
    for (size_t i = 0; i < size; i++) {
        std::println("1 {}", vec[i]);
    }
    std::println("2 {}", vec.remove(2));

    auto s = vec.size();
    for (size_t i = 0; i < s; i++) {
        std::println("3 {}", vec[i]);
    }
}