#pragma once

#include "interface/cli/cli.hpp"
#include "core/features/document_service.hpp"
#include "core/domain/document/certificate.hpp"
#include "core/domain/document/document.hpp"
#include "core/features/document_service.hpp"
#include "core/features/certificate_service.hpp"

class AdminCLI : public CommandLineInterface {
public:
    AdminCLI(
        DocumentService& documentService,
        CertificateService& certificateService
        );

    void displayMenu() override;
    void action() override;
    
private:
    DocumentService& m_documentService;
    CertificateService& m_certificateService;

    void createDoc();
    void readDoc();
    void updateDoc();
    void deleteDoc();
};