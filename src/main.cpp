#include <iostream>
#include <limits>
#include <ranges>
#include <vector>
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

    class Game
    {
    private:
        int totalScore {};
        int questionAmount {};
        std::vector<Question> questionVector {};

        void printQuestion(const Question& q)
        {
            std::cout << q.multiplicand << " x " << q.multiplier << " = ";
        }

        void generateQuestions()
        {
            for ([[maybe_unused]] int i : std::views::iota(1, questionAmount + 1)) {
                questionVector.push_back(Question {Random::get(1,12), Random::get(1,12)});
            }
            return;
        }

        // Would be better as a pure function. (Question struct needs to lose guess field.)
        bool askQuestion(Question& q)
        {
            printQuestion(q);
            q.guess = getInput();
            bool isCorrect {(q.multiplicand * q.multiplier) == q.guess};

            std::cout << (isCorrect ? "Correct!" : "Incorrect!") << '\n'; // TODO: Replace this with something not bad.

            return isCorrect;
        }

    public:
        Game() = default;

        Game(int qCount) {
            questionAmount = qCount;
        }

        ~Game() = default;

        void playGame() 
        {
            generateQuestions();
            for (Question& q : questionVector) {
                if (askQuestion(q))
                    totalScore++;
            }
            
            std::cout << "You scored " << totalScore << " out of " << questionAmount << '\n';
        }
    };
}

int main()
{
    MultiplyGame::Game game {5};
    game.playGame();
}