#include "interface/cli/user_cli.hpp"
#include "interface/cli/menu/console_menu.hpp"
#include "interface/cli/menu/menu_item.hpp"

#include <iostream>

using namespace std;

UserCLI::UserCLI(
    DocumentService<Document>& documentService,
    DocumentService<Certificate>& certificateService,
    int userId
    ) : m_documentService(documentService), m_certificateService(certificateService)
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
                Document doc { m_documentService.read(userId) };
                doc.printInfo();
                break;
            }
            case 2: {
                Document doc { m_documentService.read(userId) };

                wstring pin;

                wcout << L"Введіть новий пін: \n";
                wcin >> pin;

                doc.setPin(pin);
                m_documentService.update(userId, doc);

                wcout << L"Дані оновлено: \n";
                break;
            }
        }
        
        wcout << L"Enter щоб продовжити\n";
        std::wcin.get();

    } while (choice != 3);
}