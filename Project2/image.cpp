#include "image.h"

Image::Image(string fn) {
    ifstream file(fn, ios_base::binary);
    fileName = fn;
    // Check if file is open
    if (!file.is_open()) {
        cerr << "File failed to open" << endl;
        img = nullptr;
        return;
    }
    // Read header data
    file.read((char*)&header.idLength, 1);
    file.read((char*)&header.colorMapType, 1);
    file.read((char*)&header.dataTypeCode, 1);
    file.read((char*)&header.colorMapOrigin, 2);
    file.read((char*)&header.colorMapLength, 2);
    file.read((char*)&header.colorMapDepth, 1);
    file.read((char*)&header.xOrigin, 2);
    file.read((char*)&header.yOrigin, 2);
    file.read((char*)&header.width, 2);
    file.read((char*)&header.height, 2);
    file.read((char*)&header.bitsPerPixel, 1);
    file.read((char*)&header.imageDescriptor, 1);

    imgSize = header.width * header.height;
    // Read pixel colors from the file
    for (int i = 0; i < header.width * header.height; i++) {
        unsigned char blue = 0;
        file.read((char*)&blue, 1);
        //blues.push_back(blue);
        unsigned char green = 0;
        file.read((char*)&green, 1);
        //greens.push_back(green);
        unsigned char red = 0;
        file.read((char*)&red, 1);
        //reds.push_back(red);
        pixels.push_back(Pixel(blue, green, red));
    }
}

Image::Image(string fn, short w, short h) {
    fileName = fn;
    header.idLength = 0;
    header.colorMapType = 0;
    header.dataTypeCode = 0;
    header.colorMapOrigin = 0;
    header.colorMapLength = 0;
    header.colorMapDepth = 0;
    header.xOrigin = 0;
    header.yOrigin = 0;
    header.width = w;
    header.height = h;
    header.bitsPerPixel = 24;
    header.imageDescriptor = 0;
    imgSize = w * h * 3;
    img = new char[imgSize];
}

void Image::write(string output) {
    ofstream differentFile(output, ios_base::binary);
    if (!differentFile.is_open()) {
        cerr << "An error has occurred opening '" << fileName << "' for write." << endl;
        return;
    }
    // Write header data
    differentFile.write((char*)&header.idLength, 1);
    differentFile.write((char*)&header.colorMapType, 1);
    differentFile.write((char*)&header.dataTypeCode, 1);
    differentFile.write((char*)&header.colorMapOrigin, 2);
    differentFile.write((char*)&header.colorMapLength, 2);
    differentFile.write((char*)&header.colorMapDepth, 1);
    differentFile.write((char*)&header.xOrigin, 2);
    differentFile.write((char*)&header.yOrigin, 2);
    differentFile.write((char*)&header.width, 2);
    differentFile.write((char*)&header.height, 2);
    differentFile.write((char*)&header.bitsPerPixel, 1);
    differentFile.write((char*)&header.imageDescriptor, 1);
    // Write pixel data
    for (int i = 0; i < header.width * header.height; i++) {
        differentFile.write((char*)&(pixels.at(i).blue), 1);
        differentFile.write((char*)&(pixels.at(i).green), 1);
        differentFile.write((char*)&(pixels.at(i).red), 1);
    }
}

bool Image::compare(Image& i1) {
    if (i1.getImgSize() != imgSize) {
        cerr << "Compare image size mismatch between '" << i1.getFileName() << "' and '" << fileName << "'." << endl;
        return false;
    }
    for (int i = 0; i < imgSize; i++) {
        if (((i1.pixels.at(i).blue) != (pixels.at(i).blue)) && ((i1.pixels.at(i).green) != (pixels.at(i).green)) && ((i1.pixels.at(i).red) != (pixels.at(i).red))) {
            return false;
        }
    }
    return true;
}

Image::~Image() {
    delete img;
}

const string& Image::getFileName() {
    return fileName;
}

const Header& Image::getHeader() {
    return header;
}

const size_t Image::getImgSize() {
    return imgSize;
}

char* Image::getImg() {
    return img;
}

void Image::setFileName(string fn) {
    fileName = fn;
}

void Image::multiply(Image& i1) {
    if (i1.getImgSize() != imgSize) {
        cerr << "Multiply image size mismatch between '" << i1.getFileName() << "' and '" << fileName << "'." << endl;
        return;
    }
    for (int i = 0; i < imgSize; i++) {
        float a = (((float)(i1.pixels.at(i).blue) * (float)(pixels.at(i).blue))/255) + 0.5f;
        float b = (((float)(i1.pixels.at(i).green) * (float)(pixels.at(i).green))/255) + 0.5f;
        float c = (((float)(i1.pixels.at(i).red) * (float)(pixels.at(i).red))/255) + 0.5f;
        pixels.at(i).blue = (unsigned char) a; 
        pixels.at(i).green = (unsigned char) b;
        pixels.at(i).red = (unsigned char) c;
    }

    /*char* c1 = i1.getImg();
    char* c2 = i2.getImg();

    for (size_t i = 0; i < imgSize; i++) {
        img[i] = (((c1[i] & 0xff) * (c2[i] & 0xff)) + 127) / 255;
        if (i == 2804) {
            cout << 0 + c1[i] << "= f1 " << 0 + c2[i] << "= f2 " << 0 + img[i] << "=me" << endl;
        }
    }*/
}

