#pragma once

#include "interface/persistence/document_repository.hpp"

template <typename DocType>
class DocumentService {
public:
    DocumentService(DocumentRepository& documentRepository)
        : m_documentRepository(documentRepository)
    {}

    void create(DocType document);
    DocType read(int id);
    int update(int id, const DocType& document);
    void remove(int id);
private:
    DocumentRepository& m_documentRepository;
};

template <typename DocType>
inline void DocumentService<DocType>::create(DocType document)
{
    m_documentRepository.createDocument(document);
}

template <typename DocType>
inline DocType DocumentService<DocType>::read(int id)
{
    DocType* document = m_documentRepository.readDocument(id);
    if (document) {
        return *document;
    }
    return DocType();
}

template <typename DocType>
inline int DocumentService<DocType>::update(int id, const DocType &document)
{
    m_documentRepository.updateDocument(document.getId(), document);
    return 0;
}

template <typename DocType>
inline void DocumentService<DocType>::remove(int id)
{
    m_documentRepository.deleteDocument(id);
}
