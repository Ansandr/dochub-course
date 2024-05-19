#pragma once

#include "interface/cli/cli.hpp"
#include "core/features/document_service.hpp"
#include "core/domain/document/certificate.hpp"
#include "core/domain/document/document.hpp"
#include "core/features/document_service.hpp"
#include "core/features/certificate_service.hpp"

class UserCLI : public CommandLineInterface {
public:
    UserCLI(
        DocumentService& documentService,
        CertificateService& certificateService,
        int userId
    );

    void displayMenu() override;
    void action() override;
    
private:
    DocumentService& m_documentService;
    CertificateService& m_certificateService;

    int userId;
};