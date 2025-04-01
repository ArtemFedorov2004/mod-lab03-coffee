#pragma once

// Copyright 2022 UNN-IASR
#include <map>
#include <ostream>
#include <string>

enum class STATE {
    OFF,
    WAIT,
    ACCEPT,
    CHECK,
    COOK
};

class Automata {
public:
    Automata(std::ostream& output) : out(output), cash(0), state(STATE::OFF) {
        menu = {
            {"Coffe", 500},
            {"Tea", 40},
            {"Juice", 160}
        };
    }

    void on();
    void off();
    void coin(int money);
    void choice(std::string drink);
    void cancel();
    STATE getState();
    void logMenu();
    int getCash();

private:
    std::ostream& out;
    int cash;
    std::map<std::string, int> menu;
    STATE state;
    void check(std::string drink);
    void cook();
    void finish();
};
