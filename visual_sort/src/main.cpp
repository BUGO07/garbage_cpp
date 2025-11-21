#include <vector>
#include <print>
#include <ctime>
#include <random>
#include <algorithm>
#include <thread>

void quicksort(std::vector<int> &vec, size_t lo, size_t hi);
size_t partition(std::vector<int> &vec, size_t lo, size_t hi);

int main() {
    std::vector<int> vec(20);

    std::ranges::iota(vec, 0);

    std::random_device device;
    std::default_random_engine rand(device());
    
    std::ranges::shuffle(vec, rand);
    
    std::println("{}", vec);
    
    quicksort(vec, 0, vec.size() - 1);
}

void quicksort(std::vector<int> &vec, size_t lo, size_t hi) {
    if (lo < hi) {
        size_t p = partition(vec, lo, hi);

        quicksort(vec, lo, p);
        quicksort(vec, p + 1, hi);
    }
}

size_t partition(std::vector<int> &vec, size_t lo, size_t hi) {
    int pivot = vec[lo];

    size_t i = lo - 1;

    size_t j = hi + 1;

    while (true) {
        do i++; while (vec[i] < pivot);
        do j--; while (vec[j] > pivot);
        
        if (i >= j) {
            return j;
        }

        std::swap(vec[i], vec[j]);
        std::println("{}", vec);
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(200ms);
    }
}