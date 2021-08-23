// Project2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
using namespace std;

struct Header{
    char idLength;
    char colorMapType;
    char dataTypeCode;
    short colorMapOrigin;
    short colorMapLength;
    char colorMapDepth;
    short xOrigin;
    short yOrigin;
    short width;
    short height;
    char bitsPerPixel;
    char imageDescriptor;
};

int main(){
    Header headerObject;
    ifstream file("pattern1.tga", ios_base::binary);
    file.read(&headerObject.idLength, sizeof(headerObject.idLength));
    cout << headerObject.idLength;
    file.read(&headerObject.colorMapType, sizeof(headerObject.colorMapType));
    ofstream differentFile("testing.txt, ios_base::binary");
    differentFile.write(&headerObject.idLength, sizeof(headerObject.idLength));

}
