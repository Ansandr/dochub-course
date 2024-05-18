#include "services/persistence/document_object_repository.hpp"
#include "document_object_repository.hpp"

void DocumentObjectRepository::createDocument(const Document& document) {

    m_documents.push_back(document);
}

Document *DocumentObjectRepository::readDocument(int id) {
    if (id >= 0 && id < static_cast<int>(m_documents.size())) {
        return &(m_documents[id]);
    }
    return nullptr;
}

void DocumentObjectRepository::updateDocument(int id, const Document &document) {
    if (id >= 0 && id < static_cast<int>(m_documents.size())) {
        m_documents[id] = document;
    }
}

void DocumentObjectRepository::deleteDocument(int id) {
    if (id >= 0 && id < static_cast<int>(m_documents.size())) {
        m_documents.erase(m_documents.begin() + id);
    }
}

int DocumentObjectRepository::getLenght()
{
    return m_documents.size();
}