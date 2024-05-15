#pragma once

#include "interface/cli/menu/menu_item.hpp"

#include <functional>

using namespace std;

class FunctionItem : public MenuItem {

public:
    FunctionItem(wstring title, function<void()> cmd);

    void action();

private:
    function<void()> command;
};