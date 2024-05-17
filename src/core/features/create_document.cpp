#include "core/features/document_features.hpp"
#include "document_features.hpp"

CreateDocumentFeature::CreateDocumentFeature(DocumentRepository& documentRepository)
    : m_documentRepository(documentRepository) {
        m_lastId = m_documentRepository.getLenght();
    }


void CreateDocumentFeature::execute(const std::wstring& date, const wstring& pin) {
    Document document(m_lastId++, date, pin);
    m_documentRepository.createDocument(document);
}

void CreateDocumentFeature::execute(Document& doc) {
    m_documentRepository.createDocument(doc);
}

void CreateDocumentFeature::setLastId(int id)
{
    m_lastId = id;
}
