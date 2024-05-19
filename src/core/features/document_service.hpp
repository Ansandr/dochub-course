#pragma once

#include "interface/persistence/document_repository.hpp"
#include "core/domain/document/document.hpp"

class DocumentService {
public:
    DocumentService(DocumentRepository& documentRepository);

    void create(Document document);
    Document read(int id);
    int update(int id, const Document& document);
    void remove(int id);

    void sign(int id, const Document& document);
private:
    DocumentRepository& m_documentRepository;
};