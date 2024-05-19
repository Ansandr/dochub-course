#include "core/domain/document/certificate.hpp"

#include <iostream>

Certificate::Certificate() : Document()
{
    connectedDoc = -1;
    specification = L"";
}

Certificate::Certificate(const int certId, const int docId, const wstring date, const wstring spec)
    : Document(certId, date)
{
    connectedDoc = docId;
    specification = spec;
}

int Certificate::getConnectedDoc() const
{
    return connectedDoc;
}

wstring Certificate::getSpecitifcation() const
{
    return specification;
}

void Certificate::printInfo() const
{
    wcout << L"Атестат:\n";
    wcout << L"Спеціальність: " << specification << "\n";
    wcout << L"Дата випуску: " << date << "\n";
    wcout << L"Номер: " << id << "\n";
}

wstring Certificate::writeRow() const
{
    wstringstream ss;
    ss << getId() << L',' << getConnectedDoc() << L',' << getDateString() << L',' << getSpecitifcation();
    return ss.str();
}

wostream &operator<<(wostream &os, const Certificate &cert)
{
    os << cert.getId() << L',' << cert.getConnectedDoc() << L',' << cert.getDateString() << L',' << cert.getSpecitifcation();
    return os;
}
