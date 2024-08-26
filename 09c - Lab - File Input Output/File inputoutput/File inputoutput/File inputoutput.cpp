// File inputoutput.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

/*
Reasources used
https://www.w3schools.com/cpp/cpp_files.asp
https://www.tutorialspoint.com/reading-and-writing-binary-file-in-c-cplusplus
*/

#include <iostream>
#include <fstream>

struct person {
    char Initial;
    int Age;
    float Height;
};

void printPerson(person);

void writeFile(std::string file, person p);

person readFile(std::string);

int main()
{
    person Ben{
        'B',
        22,
        6.1
    };

    writeFile("person.dat", Ben); //ios::binary makes file type binary
    person Ben2 = readFile("person.dat");
    printPerson(Ben2);
}

void printPerson(person p){
    std::cout << "Initial; " << p.Initial << " Age; " << p.Age << " Height; " << p.Height << "\n";
};

void writeFile(std::string file, person p) {
    std::ofstream wFile(file, std::ios::binary);
    if (!wFile) { //  checks file is valid
        std::cout << "ERROR FILE INVALID\n";
    }
    else {
        std::cout << "File created\n";
    }
    wFile.write((char*)&p, sizeof(person)); //size of input used for size of data needed to be written
    //ofstream.write uses binary writing and not string/char values, avoid using << when not needed
    wFile.close();
}

person readFile(std::string file) {
    std::ifstream rFile;
    rFile.open(file, std::ios::binary);
    if (!rFile) { //  checks file is valid
        std::cout << "ERROR, NO FILE FOUND\n";
    }
    else {
        std::cout << "File found :D\n";
    }
    person temp;
    rFile.read(reinterpret_cast<char*>(&temp), sizeof(temp)); //does a cast to find dat
    rFile.close();
    return temp;
}