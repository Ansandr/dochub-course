#include "interface/cli/menu/menu_item.hpp"

#include <iostream>


MenuItem::MenuItem(wstring text) {
    this->text = text;
}

void MenuItem::show(int index) {
    this->index = index + 1;
    wcout << " " << index+1 << " - " << text << "\n";
}