#pragma once

#include "interface/cli/cli.hpp"
#include "core/features/document_features.hpp"
#include "core/features/document_service.hpp"

class AdminCLI : public CommandLineInterface {
public:
    AdminCLI(
        DocumentService& documentService,
        DocumentService& certificateService
        );

    void displayMenu() override;
    void action() override;
    
private:
    DocumentService& m_documentService;
    DocumentService& m_certificateService;

    void createDoc();
    void readDoc();
    void updateDoc();
    void deleteDoc();
};