#include <iostream>
#include <fstream>

int main() {
    // Resolution
    constexpr int width { 480 };
    constexpr int height { 270 };

    // Output file
    std::ofstream out("output.ppm", std::ios::out);
    if (!out) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    // PPM Header
    out << "P3\n";
    out << width << " " << height << "\n";
    out << "255\n";

    out.close();

    return 0;
}