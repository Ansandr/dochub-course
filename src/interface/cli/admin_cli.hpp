#pragma once

#include "interface/cli/cli.hpp"
#include "core/features/document_features.hpp"

class AdminCLI : public CommandLineInterface {
public:
    AdminCLI(
        CreateDocumentFeature& createDocumentFeature,
        ReadDocumentFeature& readDocumentFeature,
        UpdateDocumentFeature& updateDocumentFeature,
        DeleteDocumentFeature& deleteDocumentFeature);

    void displayMenu() override;
    void action() override;
    
private:
    CreateDocumentFeature& m_createDocumentFeature;
    ReadDocumentFeature& m_readDocumentFeature;
    UpdateDocumentFeature& m_updateDocumentFeature;
    DeleteDocumentFeature& m_deleteDocumentFeature;

    void createDoc();
    void readDoc();
    void updateDoc();
    void deleteDoc();
};