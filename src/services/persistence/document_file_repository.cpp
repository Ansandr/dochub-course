#include "services/persistence/document_file_repository.hpp"

DocumentFileRepository::DocumentFileRepository(const std::string &fileName)
: fileName(fileName)
{}

void DocumentFileRepository::createDocument(const Document &document) {
    wofstream outFile(fileName);
    if (outFile.is_open()) {
        outFile << document << "\n";
        outFile.close();
        wcout << L"Документ збережений\n";
    }
}

Document *DocumentFileRepository::readDocument(int id) {
    return nullptr;
}

void DocumentFileRepository::updateDocument(int id, const Document &document) {

}

void DocumentFileRepository::deleteDocument(int id) {

}
