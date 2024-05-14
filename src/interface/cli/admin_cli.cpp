#include "interface/cli/admin_cli.hpp"
#include "interface/cli/menu/console_menu.hpp"
#include "interface/cli/menu/menu_item.hpp"

#include <iostream>
#include <limits>

using namespace std;

void AdminCLI::createDoc()
{   
    wstring date;

    wcout << L"Введіть дату: (YYYY-MM-dd) \n";
    wcin >> date;

    m_createDocumentFeature.execute(date);
    wcout << L"Документ створений\n";
}

void AdminCLI::readDoc()
{
    int id;

    wcout << L"Введіть номер документа: \n";
    wcin >> id;

    Document doc = m_readDocumentFeature.execute(id);

    if (doc.getId() == -1) {
        wcout << L"Документа не існує\n";
        return;
    }
    
    wcout << "Document:\n";
    wcout << "id: " << doc.getId() << "\n";
    wcout << "date: " << doc.getDateString() << "\n";
}

void AdminCLI::updateDoc()
{
    int id;
    wstring date;
    wcout << L"Введіть номер документа: \n";
    wcin >> id;

    Document doc = m_readDocumentFeature.execute(id);
    if (doc.getId() == -1) {
        wcout << L"Документа не існує\n";
        return;
    }

    wcout << L"Введіть нову дату: \n";
    wcin >> date;

    if (m_updateDocumentFeature.execute(id, date) == 0)
        wcout << L"Дані оновлено\n";
    else   
        wcout << L"Дані не оновлено. Документа не існує\n";
    
}

void AdminCLI::deleteDoc()
{   
    int id;
    wcout << L"Введіть номер документа: \n";
    wcin >> id;

    Document doc = m_readDocumentFeature.execute(id);
    if (doc.getId() == -1) {
        wcout << L"Документа не існує\n";
        return;
    }

    m_deleteDocumentFeature.execute(id);
    wcout << L"Документ видалено\n";
}

AdminCLI::AdminCLI(
    CreateDocumentFeature& createDocumentFeature,
    ReadDocumentFeature& readDocumentFeature,
    UpdateDocumentFeature& updateDocumentFeature,
    DeleteDocumentFeature& deleteDocumentFeature)
    : CommandLineInterface(),
        m_createDocumentFeature(createDocumentFeature),
        m_readDocumentFeature(readDocumentFeature),
        m_updateDocumentFeature(updateDocumentFeature),
        m_deleteDocumentFeature(deleteDocumentFeature)
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
        wcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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
                m_createDocumentFeature.execute(L"2022-07-15");
                m_createDocumentFeature.execute(L"2020-03-27");
                m_createDocumentFeature.execute(L"2024-11-05");
                m_createDocumentFeature.execute(L"2021-01-19");
                break;
            }
        }
        wcout << L"Enter щоб продовжити\n";
        std::wcin.get();

    } while (choice != 5);
    
}