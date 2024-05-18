#pragma once

#include "interface/persistence/document_repository.hpp"
#include "core/domain/document/document.hpp"

#include <string>

class CreateDocumentFeature {
public:
    CreateDocumentFeature(DocumentRepository& documentRepository);

    void execute(const std::wstring& date, const std::wstring& pin);

    void execute(const Document& doc);
    
    void setLastId(int id);
    
private:
    DocumentRepository& m_documentRepository;
    int m_lastId;
};

class ReadDocumentFeature {
public:
    ReadDocumentFeature(DocumentRepository& documentRepository);

    Document execute(int id);

    ReadDocumentFeature& operator= (const ReadDocumentFeature& x)
    {
        return *this;
    }

private:
    DocumentRepository& m_documentRepository;
};

class UpdateDocumentFeature {
public:
    UpdateDocumentFeature(DocumentRepository& documentRepository);

    int execute(int id, wstring date);
    int execute(Document doc);

    UpdateDocumentFeature& operator= (const UpdateDocumentFeature& x)
    {
        return *this;
    }

private:
    DocumentRepository& m_documentRepository;
};

class DeleteDocumentFeature {
public:
    DeleteDocumentFeature(DocumentRepository& documentRepository);
    void execute(int id);

    DeleteDocumentFeature& operator= (const DeleteDocumentFeature& x)
    {
        return *this;
    }

private:
    DocumentRepository& m_documentRepository;
};
