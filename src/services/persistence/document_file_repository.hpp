#pragma once

#include "interface/persistence/document_repository.hpp"
#include "core/domain/document/document.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

class DocumentFileRepository : public DocumentRepository {
public:
    DocumentFileRepository(const string& fileName);

    void createDocument(Document document) override;
    Document* readDocument(int id) override;
    void updateDocument(int id, const Document& document) override;
    void deleteDocument(int id) override;

    int getLenght() override;
private:
    string fileName;
    int lastId;
};