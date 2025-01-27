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
    };

    class Game
    {
    private:
        int m_totalScore {};
        int m_questionAmount {5};
        std::vector<Question> m_questionVector {};

        void printQuestion(const Question& q)
        {
            std::cout << q.multiplicand << " x " << q.multiplier << " = ";
        }

        void generateQuestions()
        {
            for ([[maybe_unused]] int i : std::views::iota(1, m_questionAmount + 1)) {
                m_questionVector.push_back(Question {Random::get(1,12), Random::get(1,12)});
            }
            return;
        }

        bool askQuestion(const Question& q)
        {
            printQuestion(q);
            int guess = getInput();
            bool isCorrect {(q.multiplicand * q.multiplier) == guess};

            std::cout << (isCorrect ? "Correct!" : "Incorrect!") << '\n'; // TODO: Replace this with something not bad.

            return isCorrect;
        }

    public:
        Game(int qCount) : m_questionAmount {qCount}
        {
        }

        void playGame() 
        {
            generateQuestions();
            for (Question& q : m_questionVector) {
                if (askQuestion(q))
                    m_totalScore++;
            }
            
            std::cout << "You scored " << m_totalScore << " out of " << m_questionAmount << '\n';
        }
    };
}

int main()
{
    MultiplyGame::Game game {5};
    game.playGame();
}