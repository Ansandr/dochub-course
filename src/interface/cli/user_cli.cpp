#include "interface/cli/user_cli.hpp"
#include "interface/cli/menu/console_menu.hpp"
#include "interface/cli/menu/menu_item.hpp"
#include "core/features/document_service.hpp"
#include "core/features/certificate_service.hpp"

#include <iostream>

using namespace std;

UserCLI::UserCLI(
    DocumentService& documentService,
    CertificateService& certificateService,
    int userId
    ) : m_documentService(documentService), m_certificateService(certificateService)
{
    this->userId = userId;
}

void UserCLI::displayMenu()
{
    Document doc { m_documentService.read(userId) };
    doc.printInfo();

    ConsoleMenu menu(L"DocHub", L"Меню користувача");
    
    MenuItem item_read(L"Відкрити атестат про навчання");
    MenuItem item_update(L"Змінити пароль");
    MenuItem item_sign(L"Підписати документ");

    menu.addItem(item_read);
    menu.addItem(item_update);
    menu.addItem(item_sign);

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
                Certificate cert { m_certificateService.getCertificateByDocId(userId) };
                cert.printInfo();
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
            case 3: {
                wchar_t type;
                wcout << L"Який тип документа створити? (d, c)\n";
                wcin >> type;

                switch (type) {
                    case 'd': {
                        Document doc { m_documentService.read(userId) };
                        m_documentService.sign(userId, doc);
                        wcout << L"Документ підписано\n";
                        break;
                    }
                    case 'c': {
                        Certificate cert { m_certificateService.getCertificateByDocId(userId) };
                        m_certificateService.sign(userId, cert);
                        wcout << L"Сертифікат підписано\n";
                        break;
                    }
                }
                break;
            }
        }
        
        wcout << L"Enter щоб продовжити\n";
        std::wcin.get();

    } while (choice != 4);
}