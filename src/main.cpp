#include <iostream>
#include <limits>
#include <ranges>
#include <vector>

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

    struct Game {
        int totalScore {0};
        int questionCount {0};
        std::vector<Question> questionVector {};
    };

    Game& generateQuestions(Game& game, const int questionAmount)
    {
        for ([[maybe_unused]] int i : std::views::iota(1, questionAmount + 1)) {
            game.questionVector.push_back(Question {Random::get(1,12), Random::get(1,12)});
        }
        game.questionCount = questionAmount;
        return game;
    }
    
    void printQuestion(const Question& q)
    {
        std::cout << q.multiplicand << " x " << q.multiplier << " = ";
    }

    bool askQuestion(Question& q)
    {
        printQuestion(q);
        q.guess = getInput();
        bool isCorrect {(q.multiplicand * q.multiplier) == q.guess};

        std::cout << (isCorrect ? "Correct!" : "Incorrect!") << '\n';

        return isCorrect;
    }

    void playGame(const int questionAmount) {
        Game game {};

        game = generateQuestions(game, questionAmount);
        for (Question& q : game.questionVector) {
            if (askQuestion(q))
                game.totalScore++;
        }
        
        std::cout << "You scored " << game.totalScore << " out of " << questionAmount << '\n';
    }
}

int main()
{
    MultiplyGame::playGame(4);
}