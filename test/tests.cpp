// Copyright 2022 UNN-IASR

#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "Automata.h"

TEST(AutomataTest, InitialState) {
    std::stringstream output;
    Automata automata(output);

    EXPECT_EQ(automata.getState(), STATE::OFF);
    EXPECT_EQ(automata.getCash(), 0);
}

TEST(AutomataTest, TurnOn) {
    std::stringstream output;
    Automata automata(output);

    automata.on();

    EXPECT_EQ(automata.getState(), STATE::WAIT);
}

TEST(AutomataTest, IllegalStateExceptionOnTurnOn) {
    std::stringstream output;
    Automata automata(output);

    automata.on();
    automata.on();

    std::string expected_output = "ILLEGAL STATE EXCEPTION\n";
    EXPECT_EQ(output.str(), expected_output);
}

TEST(AutomataTest, InsertCoin) {
    std::stringstream output;
    Automata automata(output);

    automata.on();
    automata.coin(100);
    EXPECT_EQ(automata.getState(), STATE::ACCEPT);
    EXPECT_EQ(automata.getCash(), 100);
}

TEST(AutomataTest, ChooseDrink) {
    std::stringstream output;
    Automata automata(output);

    automata.on();
    automata.coin(500);
    automata.choice("Coffe");

    EXPECT_EQ(automata.getState(), STATE::WAIT);
}

TEST(AutomataTest, NoSuchElementExceptionOnInvalidDrink) {
    std::stringstream output;
    Automata automata(output);

    automata.on();
    automata.coin(500);
    automata.choice("Water");

    std::string expected_output = "NO SUCH ELEMENT EXCEPTION";
    EXPECT_EQ(output.str().substr(0, expected_output.size()), expected_output);
}

TEST(AutomataTest, UnsupportedOperationExceptionOnInsufficientFunds) {
    std::stringstream output;
    Automata automata(output);

    automata.on();
    automata.coin(50);
    automata.choice("Coffe");

    std::string expected_output = "UNSUPPORTED OPERATION EXCEPTION: no such money\n";
    EXPECT_EQ(output.str(), expected_output);
}

TEST(AutomataTest, SuccessfulDrinkPreparation) {
    std::stringstream output;
    Automata automata(output);

    automata.on();
    automata.coin(500);
    automata.choice("Coffe");

    std::string expected_output = "INFO: start cooking...\nINFO: complete cooking\n";
    EXPECT_EQ(output.str().substr(
        output.str().find("INFO: start cooking..."),
        expected_output.size()
    ), expected_output);
    EXPECT_EQ(automata.getState(), STATE::WAIT);
}

TEST(AutomataTest, Cancel) {
    std::stringstream output;
    Automata automata(output);

    automata.on();
    automata.coin(500);
    automata.cancel();
    EXPECT_EQ(automata.getState(), STATE::WAIT);
}

TEST(AutomataTest, TurnOff) {
    std::stringstream output;
    Automata automata(output);

    automata.on();
    automata.off();
    EXPECT_EQ(automata.getState(), STATE::OFF);
}
