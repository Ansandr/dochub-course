#include "certificate_file_repository.hpp"
#include "core/domain/document/certificate.hpp"

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

CertificateFileRepository::CertificateFileRepository(const std::string &fileName)
: fileName(fileName)
{
    lastId = getLenght();
}

void CertificateFileRepository::createCertificate(Certificate certificate) {
    wofstream outFile(fileName, ios_base::app);
    if (outFile.is_open()) {
        certificate.setId(++lastId);
        outFile << certificate.writeRow() << '\n'; //id certificate
        outFile.close();
        wcout << L"Документ збережений\n";
    }
}

int CertificateFileRepository::getIdByDoc(int docId) {
    wifstream inFile(fileName);
    if (inFile.is_open()) {
        wstring line;
        while (getline(inFile, line)) {
            wstring certId;
            wstring docIdStr;
            wistringstream ss(line);

            getline(ss, certId, L',');
            getline(ss, docIdStr, L',');

            if(stoi(docIdStr) == docId) {
                inFile.close();
                return stoi(certId);
            }
        }
        inFile.close();
    }
    return -1;
}

Certificate *CertificateFileRepository::readCertificate(int id) {
    wifstream inFile(fileName);
    if (inFile.is_open()) {
        wstring line;
        while (getline(inFile, line)) {
            wstring certId;
            wistringstream ss(line);

            getline(ss, certId, L',');

            if(stoi(certId) == id) {
                wstring docId;
                wstring date;
                wstring spec;
                
                getline(ss, docId, L',');
                getline(ss, date, L',');
                getline(ss, spec, L',');

                Certificate* doc = new Certificate(stoi(certId), stoi(docId), date, spec);
                inFile.close();
                return doc;
            }
        }
        inFile.close();
    }
    return nullptr;
}

void CertificateFileRepository::updateCertificate(int id, const Certificate &newCertificate) {
    vector<wstring> lines;
    bool found = false;

    // Читати файл повністю
    wfstream file(fileName, ios_base::in);
    if (file.is_open()) {
        wstring line;
        while (getline(file, line)) {
            wstring certId;
            wistringstream ss(line);

            getline(ss, certId, L',');

            wostringstream output_string;
            if(stoi(certId) == id) { // якщо знайдено айді таке ( число)
                output_string << id << "," << newCertificate; // переписати стрічку, лишивши айді
                line = output_string.str();
                found = true;
            }

            lines.push_back(line); // Додати в вектор лінію
        }
        file.close();
    }

    // Створюєм тимчасовий файл для перезапису, якщо знайдено
    if (found) {
        wofstream tempFile("temp.csv");
        if (tempFile.is_open()) {
            for (wstring l : lines) {
                tempFile << l << "\n";
            }
            tempFile.close();

            remove(fileName.c_str());
            rename("temp.csv", fileName.c_str());
        }
    }
}

void CertificateFileRepository::deleteCertificate(int id) {
    vector<wstring> lines;
    bool found = false;

    // Читати файл повністю
    wfstream file(fileName, ios_base::in);
    if (file.is_open()) {
        wstring line;
        while (getline(file, line)) {
            wstring docId;
            wistringstream ss(line);

            getline(ss, docId, L',');

            if(stoi(docId) != id) { // якщо це не айді
                lines.push_back(line); // Додати в вектор лінію
            } else {
                found = true;
            }
            
        }
        file.close();
    }

    // Створюєм тимчасовий файл для перезапису, якщо знайдено
    if (found) {
        wofstream tempFile("temp.csv", ios_base::app);
        if (tempFile.is_open()) {//завжди фалс
            for (wstring l : lines) {
                tempFile << l << "\n";
            }
            tempFile.close();

            remove(fileName.c_str());
            rename("temp.csv", fileName.c_str());
        }
    }
}

int CertificateFileRepository::getLenght()
{
    int lastId = 0;
    wfstream file(fileName);
    if (file.is_open()) {
        wstring line;
        while (getline(file, line)) {
            wstring docId;
            wistringstream ss(line);

            getline(ss, docId, L',');

            if (lastId < stoi(docId)) {
                lastId = stoi(docId);
            }
        }
        file.close();
    }
    return lastId;
}
