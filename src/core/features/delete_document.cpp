#include "core/features/document_features.hpp"

DeleteDocumentFeature::DeleteDocumentFeature(DocumentRepository & documentRepository) 
    : m_documentRepository(documentRepository)
{}

void DeleteDocumentFeature::execute(int id) {
    m_documentRepository.deleteDocument(id);
}