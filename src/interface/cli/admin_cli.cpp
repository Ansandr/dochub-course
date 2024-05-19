#include "interface/cli/admin_cli.hpp"
#include "interface/cli/menu/console_menu.hpp"
#include "interface/cli/menu/menu_item.hpp"
#include "core/domain/document/document.hpp"
#include "core/domain/document/certificate.hpp"
#include "core/features/document_service.hpp"
#include "core/features/certificate_service.hpp"

#include <iostream>
#include <limits>
#include <sstream>

using namespace std;

void AdminCLI::createDoc()
{   
    wchar_t type;
    wcout << L"Який тип документа створити? (d, c)\n";
    wcin >> type;

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

    switch (type) {
        case 'd': {
            wstring name;
            wcout << L"Введіть ім'я: \n";
            getline(wcin, name);

            wstring pin;
            wcout << L"Створіть пін: (Не менше 4х чисел) \n";
            getline(wcin, pin);

            // перевірка введення
            if (pin.length() < 4) {
                wcout << L"Код має містити від 4 символів\n";
                return;
            }

            Document doc = Document(-1, date, pin, name);
            m_documentService.create(doc);
            wcout << L"Документ створений\n";
            break;
        }
        case 'c': {
            int docId;
            wstring spec;

            wcout << L"До якого документа прив'язати: \n";
            wcin >> docId;

            wcin.ignore();

            wcout << L"Спеціалізація: \n";
            getline(wcin, spec);

            Certificate cert = Certificate(-1, docId, date, spec);
            m_certificateService.create(cert);
            wcout << L"Атестат створений\n";
            break;
        }
    }
}

void AdminCLI::readDoc()
{
    wchar_t type;
    wcout << L"Який тип документа переглянути? (d, c)\n";
    wcin >> type;

    int id;

    wcout << L"Введіть номер документа: \n";
    wcin >> id;

    switch (type) {
        case 'd': {
            Document doc = m_documentService.read(id);

            if (doc.getId() == -1) {
                wcout << L"Документа не існує\n";
                return;
            }
    
            doc.printInfo();
            break;
        }
        case 'c': {
            Certificate cert = m_certificateService.read(id);

            if (cert.getId() == -1) {
                wcout << L"Документа не існує\n";
                return;
            }
    
            cert.printInfo();
            break;
        }
    }
}

void AdminCLI::updateDoc()
{
    int id;
    wstring date;
    wcout << L"Введіть номер документа: \n";
    wcin >> id;

    Document doc = m_documentService.read(id);
    if (doc.getId() == -1) {
        wcout << L"Документа не існує\n";
        return;
    }

    wcout << L"Введіть нову дату: \n";
    wcin >> date;
    doc.setDateString(date);

    if (m_documentService.update(id, doc) == 0)
        wcout << L"Дані оновлено\n";
    else   
        wcout << L"Дані не оновлено. Документа не існує\n";
    
}

void AdminCLI::deleteDoc()
{  
    int id; 
    wchar_t type;
    wcout << L"Який тип документа видалити? (d, c)\n";
    wcin >> type;

    wcout << L"Введіть номер документа: \n";
    wcin >> id;

    switch (type) {
        case 'd': {
            Document doc = m_documentService.read(id);

            if (doc.getId() == -1) {
                wcout << L"Документа не існує\n";
                return;
            }
    
            m_documentService.remove(id);
            wcout << L"Документ видалено\n";
            break;
        }
        case 'c': {
            Certificate cert = m_certificateService.read(id);

            if (cert.getId() == -1) {
                wcout << L"Документа не існує\n";
                return;
            }
    
            m_certificateService.remove(id);
            wcout << L"Сертифікат видалено\n";
            break;
        }
    }
}

AdminCLI::AdminCLI(
    DocumentService& documentService,
    CertificateService& certificateService
    ) : m_documentService(documentService), m_certificateService(certificateService)
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
                m_documentService.create(Document(-1, L"2022-07-15", L"1234", L"John Doe"));
                m_documentService.create(Document(-1, L"2020-03-27", L"4312", L"Jane Doe"));
                m_documentService.create(Document(-1, L"2024-11-05", L"9645", L"John Smith"));
                m_documentService.create(Document(-1, L"2021-01-19", L"5555", L"Jane Smith"));

                Certificate* cert = new Certificate(0, 12, L"2027-06-30", L"Computer Engieneer");
                m_certificateService.create(*cert);
                break;
            }
        }
        
        wcout << L"Enter щоб продовжити\n";
        std::wcin.get();

    } while (choice != 5);
    
}