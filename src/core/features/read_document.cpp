#include "core/features/document_features.hpp"

ReadDocumentFeature::ReadDocumentFeature(DocumentRepository & documentRepository) 
    : m_documentRepository(documentRepository)
{}

Document ReadDocumentFeature::execute(int id) {
    Document* document = m_documentRepository.readDocument(id);
    if (document) {
        return *document;
    }
    return Document();
}