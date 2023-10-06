// FCAI – OOP Programming – 2023 - Assignment 1
// Program Name:				xxxxxx.cpp
// Last Modification Date:	xx/xx/xxxx
// Author1 and ID and Group:	xxxxx xxxxx
// Author2 and ID and Group:	xxxxx xxxxx
// Author3 and ID and Group:	xxxxx xxxxx
// Teaching Assistant:		xxxxx xxxxx
// Purpose:..........

#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"

using namespace std;
unsigned char image[SIZE][SIZE];
string x;
void loadImage ();
void saveImage ();
void doSomethingForImage ();
void black_white();
void invert_filter();
int main()
{
  loadImage();
  doSomethingForImage();
  if(x=="0")
      return 0;
  saveImage();
  return 0;
}

//_________________________________________
void loadImage () {
   char imageFileName[100];

   // Get gray scale image file name
   cout << "Enter the source image file name: ";
   cin >> imageFileName;

   // Add to it .bmp extension and load image
   strcat (imageFileName, ".bmp");
   readGSBMP(imageFileName, image);
}

//_________________________________________
void saveImage () {
   char imageFileName[100];

   // Get gray scale image target file name
   cout << "Enter the target image file name: ";
   cin >> imageFileName;

   // Add to it .bmp extension and load image
   strcat (imageFileName, ".bmp");
   writeGSBMP(imageFileName, image);
}

//_________________________________________
void doSomethingForImage() {
    cout<<"Please select a filter to apply or 0 to exit: \n";
    cout<<"1-Black & White Filter\n"<<"2-Invert Filter\n"<<"3-Merge Filter\n";
    cout<<"4-Flip Image\n"<<"5-Darken and Lighten Image\n"<<"6-Rotate Image\n";
    cout<<"7-Detect Image Edges\n"<<"8-Enlarge Image\n"<<"9-Shrink Image\n";
    cout<<"a-Mirror 1/2 Image\n"<<"b-Shuffle Image\n"<<"c-Blur Image\n";
    cout<<"d-Crop Image\n"<<"e-Skew Image Right\n"<<"f-Skew Image Up\n";
    cout<<"s-Save the image to a file\n"<<"0-Exit\n";

    cin>>x;
    if(x=="1")
        black_white();
    else if(x=="2")
        invert_filter();



}
void black_white()
{
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {

            if (image[i][j] > 127)
                image[i][j] = 255;
            else
                image[i][j] = 0;

        }
    }

}
void invert_filter()
{
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {

           image[i][j]=255-image[i][j];

        }
    }
}