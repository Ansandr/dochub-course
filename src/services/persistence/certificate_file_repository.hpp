#pragma once

#include "interface/persistence/certificate_repository.hpp"
#include "core/domain/document/document.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

class CertificateFileRepository : public CertificateRepository {
public:
    CertificateFileRepository(const string& fileName);

    void createCertificate(Certificate cert) override;
    Certificate* readCertificate(int id) override;
    int getIdByDoc(int docId) override;
    void updateCertificate(int id, const Certificate& cert) override;
    void deleteCertificate(int id) override;

    int getLenght() override;
private:
    string fileName;
    int lastId;
};