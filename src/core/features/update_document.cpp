#include "core/features/document_features.hpp"

UpdateDocumentFeature::UpdateDocumentFeature(DocumentRepository & documentRepository) 
    : m_documentRepository(documentRepository)
{}

int UpdateDocumentFeature::execute(int id, wstring date) {
    Document* doc = m_documentRepository.readDocument(id);
    doc->setDateString(date);
    if (doc) {
        m_documentRepository.updateDocument(id, *doc);
        return 0;
    }
    return 1;
}

int UpdateDocumentFeature::execute(Document doc)
{
    m_documentRepository.updateDocument(doc.getId(), doc);
    return 0;
}