#pragma once

#include "interface/persistence/certificate_repository.hpp"
#include "core/domain/document/certificate.hpp"

class CertificateService {
public:
    CertificateService(CertificateRepository& certificateRepository);

    void create(Certificate certificate);
    Certificate read(int id);
    Certificate getCertificateByDocId(int id);
    void sign(int id, const Certificate& certificate);
    int update(int id, const Certificate& certificate);
    void remove(int id);
private:
    CertificateRepository& m_certificateRepository;
};