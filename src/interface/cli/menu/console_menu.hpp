#pragma once

#include <string>
#include <vector>
#include "interface/cli/menu/menu_item.hpp"

using namespace std;

class ConsoleMenu {

public:
    ConsoleMenu(wstring title, wstring subtitle);

    void show();
    void addItem(MenuItem item);

private:
    vector<MenuItem> m_items;
    wstring title;
    wstring subtitle;
};