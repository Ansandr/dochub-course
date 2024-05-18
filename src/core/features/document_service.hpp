#pragma once

#include "interface/persistence/document_repository.hpp"
#include "core/features/document_features.hpp"

class DocumentService {
public:
    DocumentService(DocumentRepository& repository);

    CreateDocumentFeature getCreateFeature();
    ReadDocumentFeature getReadFeature();
    UpdateDocumentFeature getUpdateFeature();
    DeleteDocumentFeature getDeleteFeature();
private:
    CreateDocumentFeature createFeature;
    ReadDocumentFeature readFeature;
    UpdateDocumentFeature updateFeature;
    DeleteDocumentFeature deleteFeature;
};