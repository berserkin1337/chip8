#include <iostream>
#include <string>
#include <fstream>
#include "Chip8.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }
    std::string filename = argv[1];
    // read data from file
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cout << "Cannot open file " << filename << std::endl;
        return 1;
    }
    const std::string data((std::istreambuf_iterator<char>(file)),
                     std::istreambuf_iterator<char>());
    // create a Chip8 instance
    Chip8 chip8;
    // load the game
    chip8.load(data);
    //close the file
    file.close();
//    std::cout << "closing the file" << std::endl;
    // emulate the Chip8
    while (chip8.is_running()) {
        chip8.emulate();
    }
    return 0;
}
