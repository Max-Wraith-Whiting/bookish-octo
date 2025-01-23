#include <iostream>
#include <limits>
#include <ranges>

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
    
    bool askQuestion(Question& q)
    {
        std::cout << q.multiplicand << " x " << q.multiplier << " = ";
        q.guess = getInput();
        bool isCorrect {(q.multiplicand * q.multiplier) == q.guess};

        std::cout << (isCorrect ? "Correct!" : "Incorrect!") << '\n';

        return isCorrect;
    }

    void playGame(int questionAmount) {
        int totalScore {0};
        for (int i : std::views::iota(1, questionAmount + 1)) {
            Question q {Random::get(1,12), Random::get(1,12)};
            std::cout << i << ". ";
            if (askQuestion(q)) {
                ++totalScore;
            }
        }
        std::cout << "You scored " << totalScore << " out of " << questionAmount << '\n';
    }
}

int main()
{
    MultiplyGame::playGame(4);
}