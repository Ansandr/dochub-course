#include "core/features/document_service.hpp"
#include "core/features/document_features.hpp"
#include "document_service.hpp"

DocumentService::DocumentService(DocumentRepository& repository)
    : createFeature(CreateDocumentFeature(repository)),
    readFeature(ReadDocumentFeature(repository)),
    updateFeature(UpdateDocumentFeature(repository)),
    deleteFeature(DeleteDocumentFeature(repository))
{}

CreateDocumentFeature DocumentService::getCreateFeature()
{
    return createFeature;
}

ReadDocumentFeature DocumentService::getReadFeature()
{
    return readFeature;
}

UpdateDocumentFeature DocumentService::getUpdateFeature()
{
    return updateFeature;
}

DeleteDocumentFeature DocumentService::getDeleteFeature()
{
    return deleteFeature;
}
