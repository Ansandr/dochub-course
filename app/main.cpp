#include "interface/cli/cli.hpp"
#include "interface/cli/admin_cli.hpp"
#include "services/persistence/document_object_repository.hpp"
#include "services/persistence/document_file_repository.hpp"

#include <iostream>
#include <io.h>
#include <fcntl.h>

using namespace std;

int main()
{
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin),  _O_U16TEXT);
    _setmode(_fileno(stderr), _O_U16TEXT);

    wcout << L"СТАРТ\n";

    //DocumentObjectRepository documentRepository;
    DocumentFileRepository documentRepository("documents.txt");


    CreateDocumentFeature createDocumentFeature(documentRepository);
    ReadDocumentFeature readDocumentFeature(documentRepository);
    UpdateDocumentFeature updateDocumentFeature(documentRepository);
    DeleteDocumentFeature deleteDocumentFeature(documentRepository);

   
    CommandLineInterface* cli = new AdminCLI(
        createDocumentFeature, 
        readDocumentFeature, 
        updateDocumentFeature,
        deleteDocumentFeature
    );

    cli->action();

    getchar();getchar();getchar();getchar();getchar();getchar();getchar();
    return 0;
}