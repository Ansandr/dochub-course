#include "core/domain/document/certificate.hpp"

#include <iostream>

Certificate::Certificate(const int docId, const int certId, const wstring date, const wstring spec)
    : Document(docId, date)
{
    certificateId = certId;
    specification = spec;
}

int Certificate::getCertificateId() const
{
    return certificateId;
}

wstring Certificate::getSpecitifcation() const
{
    return specification;
}

void Certificate::printInfo() const
{
    wcout << "Атестат:\n";
    wcout << "id: " << id << "\n";
    wcout << "Дата випуску: " << date << "\n";
    wcout << "Спеціальність: " << specification << "\n";
}

wstring Certificate::writeRow() const
{
    wstringstream ss;
    ss << "\t" << getId() << "\t" << getCertificateId() << "\t" << getDateString() << "\t" << getSpecitifcation();
    return ss.str();
}

wostream &operator<<(wostream &os, const Certificate &cert)
{
    os << "\t" << cert.getId() << "\t" << cert.getCertificateId() << "\t" << cert.getDateString() << "\t" << cert.getSpecitifcation();
    return os;
}
