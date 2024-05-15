#include "services/persistence/document_file_repository.hpp"

DocumentFileRepository::DocumentFileRepository(const std::string &fileName)
: fileName(fileName)
{}

void DocumentFileRepository::createDocument(const Document &document) {
    wofstream outFile(fileName, ios_base::app);
    if (outFile.is_open()) {
        outFile << document.getId() << "\t" << document << "\n"; //id document
        outFile.close();
        wcout << L"Документ збережений\n";
    }
}

Document *DocumentFileRepository::readDocument(int id) {
    int cid;
    wstring date;

    wifstream inFile(fileName);
    if (inFile.is_open()) {
        wstring line;
        while (getline(inFile, line)) {
            inFile >> cid;
            inFile >> date;

            if(cid == id) {
                Document* doc = new Document(cid, date);
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
            int cid;

            wistringstream ss(line);
            
            ss >> cid;

            wostringstream output_string;
            if(cid == id) { // якщо знайдено айді таке ( число)
                output_string << id << "\t" << newDocument; // переписати стрічку, лишивши айді
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
            int cid;

            wstringstream ss(line);

            ss >> cid;

            if(cid != id) { // якщо це не айді
                lines.push_back(line); // Додати в вектор лінію
            } else {
                found = true;
            }
            
        }
        file.close();
    }

    // Створюєм тимчасовий файл для перезапису, якщо знайдено
    if (found) {
        wofstream tempFile("temp.txt", ios_base::app);
        if (tempFile.is_open()) {//завжди фалс
            for (wstring l : lines) {
                tempFile << l << "\n";
            }
            tempFile.close();

            remove(fileName.c_str());
            rename("temp.txt", fileName.c_str());
        }
    }
}
