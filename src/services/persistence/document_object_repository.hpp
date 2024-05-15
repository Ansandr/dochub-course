#pragma once

#include "interface/persistence/document_repository.hpp"

#include <vector>

class DocumentObjectRepository : public DocumentRepository {
public:
    int getLenght() override;

    void createDocument(const Document& document) override;
    Document* readDocument(int id) override;
    void updateDocument(int id, const Document& document) override;
    void deleteDocument(int id) override;

private:
    std::vector<Document> m_documents;
};