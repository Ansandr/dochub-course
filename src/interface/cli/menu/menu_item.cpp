#include "interface/cli/menu/menu_item.hpp"

#include <iostream>
#include "menu_item.hpp"


MenuItem::MenuItem(wstring text) {
    this->text = text;
}

void MenuItem::show(int index) {
    this->index = index + 1;
    wcout << " " << index+1 << " - " << text << "\n";
}