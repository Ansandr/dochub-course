#pragma once

#include "interface/cli/cli.hpp"
#include "core/features/document_service.hpp"
#include "core/domain/document/certificate.hpp"
#include "core/domain/document/document.hpp"

class AdminCLI : public CommandLineInterface {
public:
    AdminCLI(
        DocumentService<Document>& documentService,
        DocumentService<Certificate>& certificateService
        );

    void displayMenu() override;
    void action() override;
    
private:
    DocumentService<Document>& m_documentService;
    DocumentService<Certificate>& m_certificateService;

    void createDoc();
    void readDoc();
    void updateDoc();
    void deleteDoc();
};