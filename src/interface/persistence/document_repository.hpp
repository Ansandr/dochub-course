#pragma once

#include "core/domain/document/document.hpp"

class DocumentRepository {
public:
    virtual ~DocumentRepository() = default;
    virtual void createDocument(const Document& document) = 0;
    virtual Document* readDocument(int id) = 0;
    virtual void updateDocument(int id, const Document& document) = 0;
    virtual void deleteDocument(int id) = 0;
};