#pragma once

#include <string>
#include <functional>

using namespace std;

class MenuItem {
public:
    MenuItem(wstring text);

    void show(int index);
    void action();

private:
    wstring text;
    int index;
    function<void()> command;
};