#include "Automata.h"

#include <string>
#include <chrono>
#include <thread>

void Automata::on() {
    if (state != STATE::OFF) {
        out << "ILLEGAL STATE EXCEPTION\n";
        return;
    }

    state = STATE::WAIT;
}

void Automata::off() {
    if (state != STATE::WAIT) {
        out << "ILLEGAL STATE EXCEPTION\n";
        return;
    }

    state = STATE::OFF;
}

void Automata::coin(int money) {
    if (state != STATE::WAIT && state != STATE::ACCEPT) {
        out << "ILLEGAL STATE EXCEPTION\n";
        return;
    }

    cash += money;
    state = STATE::ACCEPT;
}

void Automata::choice(std::string drink) {
    if (state != STATE::ACCEPT) {
        out << "ILLEGAL STATE EXCEPTION\n";
        return;
    }

    if (menu.find(drink) == menu.end()) {
        out << "NO SUCH ELEMENT EXCEPTION";
        cancel();
    }
    else {
        state = STATE::CHECK;
        check(drink);
    }
}

void Automata::cancel() {
    if (state == STATE::OFF) {
        out << "ILLEGAL STATE EXCEPTION\n";
        return;
    }

    state = STATE::WAIT;
}

STATE Automata::getState() {
    return state;
}

int Automata::getCash() {
    return cash;
}

void Automata::logMenu() {
    for (auto item : menu) {
        std::string drink = item.first;
        int price = item.second;

        out << "INFO: DRINK: " << drink << " - PRICE: " << price << "\n";
    }
}

void Automata::check(std::string drink) {
    if (state != STATE::CHECK) {
        out << "ILLEGAL STATE EXCEPTION\n";
        return;
    }

    if (cash < menu[drink]) {
        out << "UNSUPPORTED OPERATION EXCEPTION: no such money\n";
        cancel();
    }
    else {
        cash -= menu[drink];
        cook();
    }
}

void Automata::cook() {
    state = STATE::COOK;
    out << "INFO: start cooking...\n";
    std::this_thread::sleep_for(std::chrono::seconds(10));
    out << "INFO: complete cooking\n";
    finish();
}

void Automata::finish() {
    state = STATE::WAIT;
}