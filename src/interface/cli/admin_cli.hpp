#pragma once

#include "interface/cli/cli.hpp"
#include "core/features/document_features.hpp"
#include "interface/cli/menu/console_menu.hpp"
#include "interface/cli/menu/menu_item.hpp"
#include "interface/cli/menu/function_item.hpp"

class AdminCLI : public CommandLineInterface {
public:
    AdminCLI(CreateDocumentFeature& createDocumentFeature,
            ReadDocumentFeature& readDocumentFeature,
            UpdateDocumentFeature& updateDocumentFeature,
            DeleteDocumentFeature& deleteDocumentFeature);

    void displayMenu() override;
    void action() override;
    
private:
    ConsoleMenu menu;
    CreateDocumentFeature& m_createDocumentFeature;
    ReadDocumentFeature& m_readDocumentFeature;
    UpdateDocumentFeature& m_updateDocumentFeature;
    DeleteDocumentFeature& m_deleteDocumentFeature;

    void createDoc();
    void readDoc();
    void updateDoc();
    void deleteDoc();
};