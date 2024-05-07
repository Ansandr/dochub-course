#include "core/features/document_features.hpp"

CreateDocumentFeature::CreateDocumentFeature(DocumentRepository& documentRepository)
    : m_documentRepository(documentRepository) {}


void CreateDocumentFeature::execute(const std::wstring& date) {
    Document document(m_lastId++, date);
    m_documentRepository.createDocument(document);
}