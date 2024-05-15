#include "interface/cli/menu/function_item.hpp"

#include <functional>
#include <string>

FunctionItem::FunctionItem(wstring title, function<void()> cmd) 
    : MenuItem(title) , command(cmd)
{}

void FunctionItem::action()
{
    command();
}