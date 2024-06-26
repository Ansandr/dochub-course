#include "services/persistence/document_file_repository.hpp"
#include "document_file_repository.hpp"

#include <vector>

DocumentFileRepository::DocumentFileRepository(const std::string &fileName)
: fileName(fileName)
{
    lastId = getLenght();
}

void DocumentFileRepository::createDocument(Document document) {
    wofstream outFile(fileName, ios_base::app);
    if (outFile.is_open()) {
        document.setId(++lastId);
        outFile << document << L'\n'; //id document
        outFile.close();
        wcout << L"Документ збережений\n";
    }
}

Document *DocumentFileRepository::readDocument(int id) {
    wifstream inFile(fileName);
    if (inFile.is_open()) {
        wstring line;
        while (getline(inFile, line)) {
            wstring docId;
            wistringstream ss(line);

            getline(ss, docId, L',');

            if(stoi(docId) == id) {
                wstring date;
                wstring pin;
                wstring name;

                getline(ss, date, L',');
                getline(ss, pin, L',');
                getline(ss, name, L',');

                Document* doc = new Document(stoi(docId), date, pin, name);
                inFile.close();
                return doc;
            }
        }
        inFile.close();
    }
    return nullptr;
}

void DocumentFileRepository::updateDocument(int id, const Document &newDocument) {
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

            wostringstream output_string;
            if(stoi(docId) == id) { // якщо знайдено айді таке ( число)
                output_string << newDocument; // переписати стрічку, лишивши айді
                line = output_string.str();
                found = true;
            }

            lines.push_back(line); // Додати в вектор лінію
        }
        file.close();
    }

    // Створюєм тимчасовий файл для перезапису, якщо знайдено
    if (found) {
        wofstream tempFile("temp.txt");
        if (tempFile.is_open()) {
            for (wstring l : lines) {
                tempFile << l << "\n";
            }
            tempFile.close();

            remove(fileName.c_str());
            rename("temp.txt", fileName.c_str());
        }
    }
}

void DocumentFileRepository::deleteDocument(int id) {
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

int DocumentFileRepository::getLenght()
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
