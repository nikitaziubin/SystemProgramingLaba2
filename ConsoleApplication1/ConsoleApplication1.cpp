#include <iostream>
#include <fstream>
#include <set>

struct Transition {
    int state;
    char letter;
    int nextState;
};

struct FiniteAutomaton {
    int numberOfLetters;
    int numberOfStates;
    int initialState;
    int numberOfFinalStates;
    int* finalStates;
    Transition* transitions;
};

FiniteAutomaton readAutomatonFromFile(const std::string& fileName) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Can not open file " << fileName << "\n";
        exit(1);
    }

    FiniteAutomaton automaton;

    file >> automaton.numberOfLetters;
    file >> automaton.numberOfStates;
    file >> automaton.initialState;
    file >> automaton.numberOfFinalStates;

    if (automaton.numberOfFinalStates <= 0 || automaton.numberOfFinalStates > automaton.numberOfStates) {
        std::cerr << "Некоректна кількість заключних станів!\n";
        exit(1);
    }

    if (automaton.numberOfStates <= 0 || automaton.numberOfLetters <= 0) {
        std::cerr << "Некоректні дані автомата!\n";
        exit(1);
    }

    automaton.finalStates = new int[automaton.numberOfFinalStates];
    for (int i = 0; i < automaton.numberOfFinalStates; i++) {
        file >> automaton.finalStates[i];
    }

    int transitionCount = automaton.numberOfStates * automaton.numberOfLetters;
    automaton.transitions = new Transition[transitionCount];

    for (int i = 0; i < transitionCount && !file.eof(); i++) {
        file >> automaton.transitions[i].state;
        file >> automaton.transitions[i].letter;
        file >> automaton.transitions[i].nextState;
    }

    file.close();
    return automaton;
}

void unusedLetters(const FiniteAutomaton& automaton) {
    std::set<char> usedLetters;

    for (int i = 0; i < automaton.numberOfStates * automaton.numberOfLetters; i++) {
        usedLetters.insert(automaton.transitions[i].letter);
    }

    std::cout << "Unused letters:";
    for (char c = 'a'; c < 'a' + automaton.numberOfLetters; c++) {
        if (usedLetters.find(c) == usedLetters.end()) {
            std::cout << " " << c;
        }
    }
    std::cout << "\n";
}

int main() {
    FiniteAutomaton automaton = readAutomatonFromFile("C:\\Users\\nikit\\source\\repos\\SystemProgramingLaba2\\TextFile2.txt");
    unusedLetters(automaton);

    delete[] automaton.finalStates;
    delete[] automaton.transitions;

    return 0;
}
