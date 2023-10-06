// FCAI – OOP Programming – 2023 - Assignment 1
// Program Name:				filters.cpp
// Last Modification Date:	/10/2023
// Author1 and ID and Group:
// Author2 and ID and Group:
// Author3 and ID and Group:
// Teaching Assistant:
// Purpose:..........

#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"

using namespace std;
unsigned char image[SIZE][SIZE];
unsigned char image1[SIZE][SIZE];
int n;
string x;
void loadImage ();
void saveImage ();
void doSomethingForImage ();
void black_white();
void invert_filter();
void rotate_90();
void rotate_180();
void rotate_270();
void  saveImage1();
void flip_image_horizontally();
void flip_image_vertically();
int main()
{
  loadImage();
  doSomethingForImage();
  if(x=="0")
      return 0;
  else if(x=="6")
  {if(n==90||n==270)
      { saveImage1();
          return 0;}
  }
    saveImage();
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
void saveImage1 () {
    char imageFileName[100];

    // Get gray scale image target file name
    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    writeGSBMP(imageFileName, image1);
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
    else if (x=="4")
    {
        cout << "Do you want to flip (h)orizontally or (v)ertically ?"<<endl;
        char f;
        cin >> f;
        if (f=='h')
            flip_image_horizontally();
        else if (f=='v')
        flip_image_vertically();
    }
    else if(x=="5")
    {
        cout<<"Do you want to (d)arken or (l)ighten ?";
       char f;
        cin>>f;


    }
    if(x=="6")
    {
        cout<<"Rotate (90), (180) or (270) degrees? ";
        cin>>n;
        if(n==90)
            rotate_90();
        else if(n==180)
            rotate_180();
        else if(n==270)
        {
            rotate_180();
            rotate_90();
        }
    }
}
void black_white()
{
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (image[i][j] > 127)
                image[i][j] = 255;
            else
                image[i][j] = 0;
        }
    }
}
void invert_filter()
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j< SIZE; j++)
        {
           image[i][j]=255-image[i][j];
        }
    }
}
void flip_image_horizontally()
{
    int temp =0;
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j< SIZE/2; j++)
        {
            temp = image[i][j];
            image[i][j]=image[i][255-j];
            image[i][255-j]=temp;
        }
    }
}
void flip_image_vertically()
{
    int temp =0;
    for (int i = 0; i < SIZE/2; i++)
    {
        for (int j = 0; j< SIZE; j++)
        {
            temp = image[i][j];
            image[i][j]=image[255-i][j];
            image[255-i][j]=temp;
        }
    }

}
void rotate_90()
{ for (int i = 255; i >=0; i--) {
        for (int j = 0; j< SIZE; j++) {
            image1[j][i]=image[255-i][j];
        }
    }

}
void rotate_180()
{ for (int i = 0; i < SIZE/2; i++) {
        for (int j = 0; j< SIZE; j++) {
            int t=image[i][j];
            image[i][j]=image[255-i][255-j];
            image[255-i][255-j]=t;
        }
    }

}
