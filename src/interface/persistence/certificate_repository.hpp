#pragma once

#include "core/domain/document/certificate.hpp"

class CertificateRepository {
public:
    virtual ~CertificateRepository() = default;
    virtual void createCertificate(Certificate cert) = 0;
    virtual Certificate* readCertificate(int id) = 0;
    virtual int getIdByDoc(int docId) = 0;
    virtual void updateCertificate(int id, const Certificate& cert) = 0;
    virtual void deleteCertificate(int id) = 0;

    virtual int getLenght() = 0;
};