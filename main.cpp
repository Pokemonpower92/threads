#include <iostream>
#include <vector>
#include <tuple>
#include <thread>

#include "molecule.h"

int main() {
    Molecule m;
    std::vector<std::thread> threads;

    std::string atoms = "HOHHHOOHH";

    for (auto &atom : atoms) {
        if (atom == 'H') {
            threads.emplace_back(&Molecule::hydrogen, &m);
        }
        if (atom == 'O') {
            threads.emplace_back(&Molecule::oxygen, &m);
        }
    }

    for (auto &thread : threads) {
        thread.join();
    }

    auto formedBonds = m.get_molecules();
    std::cout << "Molecules:\n";

    for(auto &bond : formedBonds) {
        std::cout << "\t h1: " << std::get<0>(bond) << std::endl;
        std::cout << "\t h2: " << std::get<1>(bond) << std::endl;
        std::cout << "\t o1: " << std::get<2>(bond) << std::endl;
    }

    return 0;
}
