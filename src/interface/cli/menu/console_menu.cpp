#include "interface/cli/menu/console_menu.hpp"
#include "interface/cli/menu/menu_item.hpp"

#include <iostream>
#include <iomanip>

static int calculate_border_width()
{
    return 100;
}

static void print_horizontals()
{   

    int width = 50;
    wcout.fill('-');
    wcout << '+' << setw(width) << '+' << endl;
}

void func() {

}

ConsoleMenu::ConsoleMenu(wstring title, wstring subtitle) {
    this->title = title;
    this->subtitle = subtitle;
}

void ConsoleMenu::show() {
    print_horizontals();

    // exit
    MenuItem exit(L"Вихід");
    m_items.push_back(exit);

    // print
    wcout << "\n";

    wcout << title << "\n\n";
    wcout << subtitle << "\n\n\n";

    for (int i = 0; i < m_items.size(); i++)
    {
        m_items.at(i).show(i);
    }

    wcout << "\n";

    print_horizontals();
    wcout << ">> ";
}

void ConsoleMenu::addItem(MenuItem item) {
    m_items.push_back(item);
}