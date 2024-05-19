#include "interface/cli/cli.hpp"
#include "interface/cli/admin_cli.hpp"
#include "interface/cli/user_cli.hpp"
#include "services/persistence/document_file_repository.hpp"
#include "services/persistence/certificate_file_repository.hpp"
#include "core/domain/document/certificate.hpp"
#include "core/domain/document/document.hpp"
#include "core/features/document_service.hpp"
#include "core/features/certificate_service.hpp"

#include <iostream>
#include <io.h>
#include <fcntl.h>

using namespace std;

bool handleAdminLogin();
bool handleUserLogin(Document document);

int main()
{
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin),  _O_U16TEXT);
    _setmode(_fileno(stderr), _O_U16TEXT);

    wcout << L"СТАРТ\n";

    //DocumentObjectRepository documentRepository;
    DocumentFileRepository documentRepository("documents.csv");
    CertificateFileRepository certificateRepository("certificates.csv");

    DocumentService documentService(documentRepository);
    CertificateService certificateService(certificateRepository);

    // Авторизація
    wcout << L"Авторизація\n";
    CommandLineInterface* cli;

    int attempts = 0;
    while (attempts < 3)
    {
        wcout << L"Зайти як Админ (a) чи Користувач (u)?\n";
        wchar_t mode;
        wcin >> mode;

        if (mode == 'a')
        {
            if (handleAdminLogin()) {
                cli = new AdminCLI(
                    documentService,
                    certificateService
                );
                break;
            }
        }
        else if (mode == 'u')
        {
            wcout << L"Enter id: ";
            int userId;
            wcin >> userId;

            Document* document = documentRepository.readDocument(userId);
            if (document) {
                if (handleUserLogin(*document)) {
                cli = new UserCLI(
                            documentService,
                            certificateService,
                            userId
                        );
                break;
                }
            }
            wcout << L"Такого айді не існує!\n";
        }
        else
        {
            wcout << L"Неправильний режим!";
        }

        attempts++;
    }
    

    cli->action();
    
    wcin.ignore();
    
    return 0;
}

bool handleAdminLogin()
{
    int attempts = 0;
    while (attempts < 3)
    {
        wstring password;

        wcout << L"Enter password: ";
        wcin >> password;

        if (password == L"admin") {
            wcout << L"Правильний пароль!\n";
            return true;
        } else {
            wcout << L"Неправильний пароль!\n";
            attempts++;
        }
    }

     wcout << L"Перевищено кількість спроб введення пароля.\n";
    return false;
}

bool handleUserLogin(Document document)
{
    int attempts = 0;

    while (attempts < 3) {
        wstring pin;

        wcout << L"Enter pin: ";
        wcin >> pin;

        if (pin != document.getPin()) {
            wcout << L"Неправильний пароль!\n";
            attempts++;
        } else {
            wcout << L"Правильний пароль!\n";
            return true;
        }
    }

    wcout << L"Перевищено кількість спроб введення пароля.\n";
    return false;
}