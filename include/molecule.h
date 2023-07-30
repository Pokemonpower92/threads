#pragma once
#include <thread>
#include <mutex>
#include <vector>
#include <deque>

class Molecule {
protected:
    const int H = 2;
    const int O = 1;

public:
    typedef std::thread::id thread_id;
    typedef std::tuple<thread_id, thread_id, thread_id> bond;

    void hydrogen();
    void oxygen();

    [[nodiscard]] std::vector<bond> get_molecules() const;

private:
    std::mutex mux;
    std::condition_variable cond;

    std::vector<bond> molecules;
    std::deque<thread_id> h;
    std::deque<thread_id> o;

    void bond_if_able();
};
