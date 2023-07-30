#include "molecule.h"
#include <mutex>

void Molecule::hydrogen() {
    std::unique_lock guard(this->mux);
    this->cond.wait(guard, [&]{return h.size() < H && o.size() <= O;});
    this->h.push_back(std::this_thread::get_id());
    this->bond_if_able();
}

void Molecule::oxygen() {
    std::unique_lock guard(this->mux);
    this->cond.wait(guard, [&]{return h.size() <= H && o.size() < O;});
    this->o.push_back(std::this_thread::get_id());
    this->bond_if_able();
}

std::vector<Molecule::bond> Molecule::get_molecules() const {
    return this->molecules;
}

void Molecule::bond_if_able() {
    if (this->h.size() == this->H && this->o.size() == this->O) {
        auto h1 = this->h[0];
        auto h2 = this->h[1];
        auto o1 = this->o[0];

        this->h.pop_front();
        this->h.pop_front();
        this->o.pop_front();

        this->molecules.emplace_back(h1, h2, o1);

        this->cond.notify_all();
    }
}
