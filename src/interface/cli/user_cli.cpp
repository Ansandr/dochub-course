#include "interface/cli/user_cli.hpp"
#include "interface/cli/menu/console_menu.hpp"
#include "interface/cli/menu/menu_item.hpp"

#include <iostream>

UserCLI::UserCLI(
    ReadDocumentFeature &readDocumentFeature,
    UpdateDocumentFeature &updateDocumentFeature,
    int userId) : CommandLineInterface(),
        m_readDocumentFeature(readDocumentFeature),
        m_updateDocumentFeature(updateDocumentFeature)
{
    this->userId = userId;
}

void UserCLI::displayMenu()
{
    ConsoleMenu menu(L"DocHub", L"Меню користувача");
    
    MenuItem item_read(L"Відкрити повну інформарцію");
    MenuItem item_update(L"Змінити пароль");

    menu.addItem(item_read);
    menu.addItem(item_update);

    menu.show();
}

void UserCLI::action()
{
    int choice;
    
    do {
        displayMenu();
        wcin >> choice;
        std::wcin.get();
        switch (choice) {
            case 1: {
                Document doc { m_readDocumentFeature.execute(userId) };
                doc.printInfo();
                break;
            }
            case 2: {
                Document doc { m_readDocumentFeature.execute(userId) };

                wstring pin;

                wcout << L"Введіть новий пін: \n";
                wcin >> pin;

                doc.setPin(pin);

                m_updateDocumentFeature.execute(doc);

                wcout << L"Дані оновлено: \n";
                break;
            }
        }
        
        wcout << L"Enter щоб продовжити\n";
        std::wcin.get();

    } while (choice != 3);
}