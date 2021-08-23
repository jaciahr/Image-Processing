// Project2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "image.h"

int main(){
    Image image1("input/layer1.tga");
    /*image1.write("output/test1.tga");
    Image image2("output/test1.tga");
    image1.compare(image2);*/
    Image image3("input/pattern1.tga");
    image3.multiply(image1);
    image3.write("output/part1.tga");



    /*Image image2("input/pattern1.tga");
    
    Image image3("output/part1.tga", w, h);
    image3.multiply(image1, image2);
    image3.write();
    Image image4("examples/EXAMPLE_part1.tga");
    cout << "part1 images do " << (image3.compare(image4) ? "" : "not ") << "compare." << endl;
    */
    return 0;
}