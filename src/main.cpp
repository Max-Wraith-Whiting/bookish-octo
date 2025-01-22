#include <iostream>
#include <limits>

#include "random.hpp"

bool cleanInput()
{
    if (!std::cin) {
        if (std::cin.eof()) {
            std::exit(0);
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return true;
    }
    return false;
}

int getInput()
{
    int x {};
    do {
        std::cin >> x;
    } while (cleanInput());
    return x;
}

namespace MultiplyGame {
    struct Question {
        int multiplicand {};
        int multiplier {};
        int guess {};
    };
    
    void askQuestion(Question& q)
    {
        std::cout << q.multiplicand << " x " << q.multiplier << " = ";
        q.guess = getInput();

        std::string result {((q.multiplicand * q.multiplier) == q.guess) ? "true" : "false"};

        std::cout << q.multiplicand << " x " << q.multiplier << " = " << q.guess << " is " << result << ".\n";
    }
}

int main()
{
    MultiplyGame::Question q {Random::get(1,12), Random::get(1,12)};
    MultiplyGame::askQuestion(q);
}