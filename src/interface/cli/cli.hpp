#pragma once

class CommandLineInterface {
public:
    virtual void displayMenu() = 0;
    virtual void action() = 0;
};