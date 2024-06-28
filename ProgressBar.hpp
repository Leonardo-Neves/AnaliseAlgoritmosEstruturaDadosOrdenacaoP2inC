#ifndef PROGRESSBAR_HPP
#define PROGRESSBAR_HPP

#include <iostream>
#include <string>

class ProgressBar {
public:
    ProgressBar(int total, int width = 70) : total(total), width(width), current(0) {}

    void update() {
        current++;
        int progress = (current * width) / total;
        std::cout << "[";
        for (int i = 0; i < progress; ++i) std::cout << "=";
        for (int i = progress; i < width; ++i) std::cout << " ";
        std::cout << "] " << (current * 100) / total << "%\r";
        std::cout.flush();
    }

private:
    int total;
    int width;
    int current;
};

#endif // PROGRESSBAR_HPP
