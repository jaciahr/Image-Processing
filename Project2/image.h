#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
using namespace std;



struct Header {
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

struct Pixel {
    //Member functions
    Pixel(unsigned char blue, unsigned char green, unsigned char red)
    {
        this->red = red;
        this->green = green;
        this->blue = blue;
    }
    // Member variables
    unsigned char red;
    unsigned char green;
    unsigned char blue;
};

class Image {
    string fileName;
    Header header;
    size_t imgSize;
    //vector (with a getter; return by reference)
    char* img;
    vector <Pixel> pixels;
public:
    Image(string fn); // Open existing image
    Image(string fn, short w, short h); // Create empty image
    ~Image();
    void readPixelData(ifstream& file);
    const string &getFileName();
    const Header &getHeader();
    const size_t getImgSize();
    char* getImg();
    void setFileName(string fn);
    void write(string output);
    void multiply(Image &i1);
    bool compare(Image& i1);
};