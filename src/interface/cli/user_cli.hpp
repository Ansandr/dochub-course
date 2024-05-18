#pragma once

#include "interface/cli/cli.hpp"
#include "core/features/document_features.hpp"
#include "core/features/document_service.hpp"

class UserCLI : public CommandLineInterface {
public:
    UserCLI(
        DocumentService& documentService,
        DocumentService& certificateService,
        int userId
    );

    void displayMenu() override;
    void action() override;
    
private:
    DocumentService& m_documentService;
    DocumentService& m_certificateService;

    int userId;
};