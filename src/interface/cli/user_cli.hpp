#pragma once

#include "interface/cli/cli.hpp"
#include "core/features/document_service.hpp"
#include "core/domain/document/certificate.hpp"
#include "core/domain/document/document.hpp"

class UserCLI : public CommandLineInterface {
public:
    UserCLI(
        DocumentService<Document>& documentService,
        DocumentService<Certificate>& certificateService,
        int userId
    );

    void displayMenu() override;
    void action() override;
    
private:
    DocumentService<Document>& m_documentService;
    DocumentService<Certificate>& m_certificateService;

    int userId;
};