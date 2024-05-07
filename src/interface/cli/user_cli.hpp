#pragma once

#include "interface/cli/cli.hpp"

class UserCLI : public CommandLineInterface {
public:
    UserCLI();

    void displayMenu() override;
    void action() override;
    
private:

};