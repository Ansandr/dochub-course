#include "interface/cli/admin_cli.hpp"
#include "interface/cli/menu/console_menu.hpp"
#include "interface/cli/menu/menu_item.hpp"
#include "core/domain/document/document.hpp"
#include "core/domain/document/certificate.hpp"

#include <iostream>
#include <limits>
#include <sstream>

using namespace std;

void AdminCLI::createDoc()
{   
    wstring date;
    
    wcout << L"Введіть дату: (YYYY-MM-dd) \n";
    wcin >> date;

    // перевірка введення
    wistringstream ss(date);
    int year;
    int month;
    int day;
    wchar_t d;
    
    if (ss >> year >> d >> month >> d >> day)
    {
        if (year < 0 || month < 1 || month > 12 || day < 1 || day > 31) {
            wcout << L"Неправильний ввід дати\n";
            return;
        } 
    }

    wstring pin;
    wcout << L"Створіть пін: (Не менше 4х чисел) \n";
    wcin >> pin;

    // перевірка введення
    if (pin.length() < 4) {
        wcout << L"Код має містити від 4 символів\n";
        return;
    }
    m_documentService.getCreateFeature().execute(date, pin);
    wcout << L"Документ створений\n";
}

void AdminCLI::readDoc()
{
    int id;

    wcout << L"Введіть номер документа: \n";
    wcin >> id;

    Document doc = m_documentService.getReadFeature().execute(id);

    if (doc.getId() == -1) {
        wcout << L"Документа не існує\n";
        return;
    }
    
    doc.printInfo();
}

void AdminCLI::updateDoc()
{
    int id;
    wstring date;
    wcout << L"Введіть номер документа: \n";
    wcin >> id;

    Document doc = m_documentService.getReadFeature().execute(id);
    if (doc.getId() == -1) {
        wcout << L"Документа не існує\n";
        return;
    }

    wcout << L"Введіть нову дату: \n";
    wcin >> date;

    if (m_documentService.getUpdateFeature().execute(id, date) == 0)
        wcout << L"Дані оновлено\n";
    else   
        wcout << L"Дані не оновлено. Документа не існує\n";
    
}

void AdminCLI::deleteDoc()
{   
    int id;
    wcout << L"Введіть номер документа: \n";
    wcin >> id;

    Document doc = m_documentService.getReadFeature().execute(id);
    if (doc.getId() == -1) {
        wcout << L"Документа не існує\n";
        return;
    }

    m_documentService.getDeleteFeature().execute(id);
    wcout << L"Документ видалено\n";
}

AdminCLI::AdminCLI(
    DocumentService& documentService,
    DocumentService& certificateService
    ) : CommandLineInterface(),
    m_documentService(documentService),
    m_certificateService(certificateService)
{}

void AdminCLI::displayMenu()
{

    ConsoleMenu menu(L"DocHub", L"Меню адміністратора");
    MenuItem item_create(L"Додати документ");
    MenuItem item_read(L"Відкрити документ");
    MenuItem item_update(L"Редагути документ");
    MenuItem item_delete(L"Видалити документ");

    menu.addItem(item_create);
    menu.addItem(item_read);
    menu.addItem(item_update);
    menu.addItem(item_delete);
    menu.show();
}

void AdminCLI::action()
{
    int choice;
    
    do {
        displayMenu();
        wcin >> choice;
        switch (choice) {
            case 1: {
                createDoc();
                break;
            }
            case 2: {
                readDoc();
                break;
            }
            case 3: {
                updateDoc();
                break;
            }
            case 4: {
                deleteDoc();
                break;
            }
            case 5: {
                continue;
            }
            case 11: {
                CreateDocumentFeature create = m_documentService.getCreateFeature();
                create.execute(L"2022-07-15", L"1234");
                create.execute(L"2020-03-27", L"4312");
                create.execute(L"2024-11-05", L"9645");
                create.execute(L"2021-01-19", L"5555");

                CreateDocumentFeature createCert = m_certificateService.getCreateFeature();
                Certificate* cert = new Certificate(0, 12, L"2027-06-30", L"Computer Engieneer");
                createCert.execute(*cert);
                break;
            }
        }
        
        wcout << L"Enter щоб продовжити\n";
        std::wcin.get();

    } while (choice != 5);
    
}