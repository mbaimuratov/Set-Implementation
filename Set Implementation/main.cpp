#include <random>
#include <iostream>
#include <sstream>

#include "set.h"

std::string create(std::string str, int x) {
    std::stringstream ss;
    ss << str << x;
    return ss.str();
}

int main(int argc, char* argv[]) {
    
    set kaz;

    kaz.insert("aqtobe");
    kaz.insert("atyrau");

    std::cout << kaz.contains("Aqtobe") << "\n";
    std::cout << kaz.contains("AqToBe") << "\n";
    // Or not to be, that's the question.

    kaz.insert("SHYMKENT");
    std::cout << kaz.contains("szymkent") << "\n";

    kaz.insert("Almaty");
    kaz.insert("Taraz");
    kaz.insert("Qaraghandy");
    kaz.insert("Qostanay");
    kaz.insert("Kokshetau");

    std::cout << "before removal\n";
    std::cout << kaz << "\n";
    kaz.remove("qostanay");
    std::cout << "after removal\n";

    std::cout << kaz << "\n";
    std::cout << kaz.size() << "\n";

    auto kaz2 = kaz; // Copy constructor.
    std::cout << kaz2 << "\n";
    std::cout << kaz2.size() << "\n";
    kaz2 = kaz;      // Assignment.
    kaz = kaz;       // Self assignment.

    
    set someset1;

    for (size_t k = 0; k != 8000; ++k) {
        someset1.insert(std::string("aa") + std::to_string(rand()));
        someset1.insert(std::string("bb") + std::to_string(rand()));
    }
    auto someset2 = someset1;

    std::cout << someset1 << std::endl;
    std::cout << someset2 << std::endl;
    std::cout << someset1.size() << std::endl;
    std::cout << someset2.size() << std::endl;
    
    double sddev = someset1.standarddev();
    std::cout << sddev << std::endl;

    return 0;
}

