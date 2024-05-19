#include "core/features/document_service.hpp"

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
