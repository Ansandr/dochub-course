#include "core/features/document_service.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <codecvt>

DocumentService::DocumentService(DocumentRepository& documentRepository)
        : m_documentRepository(documentRepository)
    {}

void DocumentService::DocumentService::create(Document document)
{
    m_documentRepository.createDocument(document);
}

Document DocumentService::DocumentService::read(int id)
{
    Document* document = m_documentRepository.readDocument(id);
    if (document) {
        return *document;
    }
    return Document();
}

int DocumentService::DocumentService::update(int id, const Document &document)
{
    m_documentRepository.updateDocument(document.getId(), document);
    return 0;
}

void DocumentService::DocumentService::remove(int id)
{
    m_documentRepository.deleteDocument(id);
}

void DocumentService::sign(const Document &document)
{
    ostringstream ss;
    ss << document.getId() << "-document.txt";

    wofstream outFile(ss.str(), ios_base::app);
    if (outFile.is_open()) {

        locale utf8_locale(locale(), new codecvt_utf8<wchar_t>);
        outFile.imbue(utf8_locale);

        outFile << document.toString();
        outFile.close();
        wcout << L"Документ підписан\n";
    }
}
