#include "core/features/certificate_service.hpp"
#include "certificate_service.hpp"

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
