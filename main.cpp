#include <iostream>
#include <fstream>
#include <string>

using namespace std;
int ITERATION = 1;


void writeNumToFileTrunc(string* num, string fileName, int mode) {
    ofstream write(fileName.substr(0, fileName.length() - 4) + "_temp" + to_string(mode % 2) + ".txt", ios::trunc);
    write << *num << endl; write.close();
}

void writeNumToFile(string* num, string fileName, int mode) {
    ofstream write(fileName.substr(0, fileName.length() - 4) + "_temp" + to_string(mode % 2) + ".txt", ios::app);
    write << *num << endl; write.close();
}

void mergeSortFiles(string fileName) {
    ifstream temp1(fileName.substr(0, fileName.length() - 4) + "_temp0" + ".txt");
    ifstream temp2(fileName.substr(0, fileName.length() - 4) + "_temp1" + ".txt");
    ofstream writeOut(fileName.substr(0, fileName.length() - 4) + "_out" + ".txt", ios::app);
    string sNum1, sNum2; getline(temp1, sNum1); getline(temp2, sNum2);
    while (!sNum1.empty() || !sNum2.empty()) {

        if (sNum1.empty()) {
            writeOut << sNum2 << endl; getline(temp2, sNum2);
        }
        else if (sNum2.empty()) {
            writeOut << sNum1 << endl; getline(temp1, sNum1);
        }
        else{
            int iNum1 = stoi(sNum1); int iNum2 = stoi(sNum2);
            if (iNum1 < iNum2) {
                writeOut << sNum1 << endl; getline(temp1, sNum1);
            }
            else {
                writeOut << sNum2 << endl; getline(temp2, sNum2);
            }
        }

    }
    temp1.close(); temp2.close(); writeOut.close();
    ofstream temper1(fileName.substr(0, fileName.length() - 4) + "_temp0" + ".txt", ios::trunc);
    ofstream temper2(fileName.substr(0, fileName.length() - 4) + "_temp1" + ".txt", ios::trunc);
    temper1.close(); temper2.close();
}

int main() {

    string fileName;
    cout << "Enter file name: " << endl;
    cin >> fileName;

    bool checker = true;
    while (checker) {
        ifstream fileRead(fileName);
        if (fileRead.is_open()) {
            string sNum; string sLastNum = "START"; int mode = 0; string empty = ""; checker = false;

            while (getline(fileRead, sNum)) {
                if (!sNum.empty()) {
                    if (sLastNum == "START") {
                        sLastNum = sNum;
                        writeNumToFileTrunc(&sNum, fileName, mode);
                        ofstream write(fileName.substr(0, fileName.length() - 4) + "_temp" + to_string((mode + 1) % 2) +
                                       ".txt", ios::trunc);
                        write.close();
                        ofstream writeOut(fileName.substr(0, fileName.length() - 4) + "_out" + ".txt", ios::trunc);
                        writeOut << empty;
                        writeOut.close();
                    } else {
                        int iNum = stoi(sNum);
                        int iLastNum = stoi(sLastNum);

                        if (iNum < iLastNum) {
                            checker = true;
                            if (mode) {
                                mergeSortFiles(fileName); mode = 0;
                            }
                            else {
                                mode++;
                            }
                            writeNumToFile(&sNum, fileName, mode);

                        } else {
                            writeNumToFile(&sNum, fileName, mode);
                        }

                        sLastNum = sNum;
                    }
                }
            }
            fileRead.close();

            mergeSortFiles(fileName);

            ifstream reader(fileName.substr(0, fileName.length() - 4) + "_out" + ".txt");
            ofstream writer(fileName); string temp;
            while (getline(reader, temp)){
                writer << temp << endl;
            }
            reader.close(); temp = "";

            ifstream remaining(fileName.substr(0, fileName.length() - 4) + "_temp" + to_string(mode % 2) + ".txt");
            while(getline(remaining, temp)){
                writer << temp << endl;
            }

            ifstream sprawdzanko(fileName.substr(0, fileName.length() - 4) + "_out.txt"); string temporary_test;
            cout << "Iteration number: " << ITERATION << endl; ITERATION++;
            while(getline(sprawdzanko, temporary_test)) {
                cout << temporary_test << " ";

            }
            cout << endl << endl;
        }
        else {
            cout << "File couldn't be opened." << endl;
        }
        ofstream clearOut(fileName.substr(0, fileName.length() - 4) + "_out" + ".txt", ios::trunc); clearOut.close();
    }

    return 0;
}