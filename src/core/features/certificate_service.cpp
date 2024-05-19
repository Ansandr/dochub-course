#include "core/features/certificate_service.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <codecvt>

CertificateService::CertificateService(CertificateRepository& certificateRepository)
        : m_certificateRepository(certificateRepository)
    {}

void CertificateService::CertificateService::create(Certificate certificate)
{
    m_certificateRepository.createCertificate(certificate);
}

Certificate CertificateService::CertificateService::read(int id)
{
    Certificate* certificate = m_certificateRepository.readCertificate(id);
    if (certificate) {
        return *certificate;
    }
    return Certificate();
}

Certificate CertificateService::getCertificateByDocId(int id)
{
    int certId = m_certificateRepository.getIdByDoc(id);
    Certificate* certificate = m_certificateRepository.readCertificate(certId);
    if (certificate) {
        return *certificate;
    }
    return Certificate();
}
int CertificateService::CertificateService::update(int id, const Certificate &certificate)
{
    m_certificateRepository.updateCertificate(certificate.getId(), certificate);
    return 0;
}

void CertificateService::CertificateService::remove(int id)
{
    m_certificateRepository.deleteCertificate(id);
}

void CertificateService::sign(const Certificate &certificate)
{
    ostringstream ss;
    ss << certificate.getId() << "-certificate.txt";

    wofstream outFile(ss.str(), ios_base::app);
    if (outFile.is_open()) {

        locale utf8_locale(locale(), new codecvt_utf8<wchar_t>);
        outFile.imbue(utf8_locale);
        
        outFile << certificate.toString();
        outFile.close();
        wcout << L"Документ підписан\n";
    }
}
