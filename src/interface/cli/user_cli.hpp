#pragma once

#include "interface/cli/cli.hpp"
#include "core/features/document_features.hpp"

class UserCLI : public CommandLineInterface {
public:
    UserCLI(
        ReadDocumentFeature& readDocumentFeature,
        UpdateDocumentFeature& updateDocumentFeature,
        int userId
    );

    void displayMenu() override;
    void action() override;
    
private:
    ReadDocumentFeature& m_readDocumentFeature;
    UpdateDocumentFeature& m_updateDocumentFeature;
    int userId;
};