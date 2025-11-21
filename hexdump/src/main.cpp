#include <print>
#include <fstream>
#include <vector>
#include <iostream>


int main(int argc, char **argv) {
    if (argc < 2) {
        std::println(stderr, "need file path");
        return -1;
    }
    
    std::string path(argv[1]);
    std::ifstream file(path, std::ios::binary);

    int counter = 0;
    std::string ascii = "";
    std::print("0x{:X}. ", counter);
    for (int c = file.get(); c != EOF; c = file.get()) {
        counter++;
        ascii += std::isprint(c) ? c : '.';
        using namespace std::string_literals;
        std::print("{:02X}{}", c, counter % 8 == 0 ? " " : "");
        if (counter % 16 == 0) {
            std::println("| {}", ascii);
            ascii = "";
            std::print("0x{:X}. ", counter);
        }
    }
}