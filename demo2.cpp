// FCAI – OOP Programming – 2023 - Assignment 1
// Program : demo2.cpp
// Last Modification Date:	10/10/2023
// Yara Hazem Hassan Hussien and NO ID (Transfered from another university).
// Salma Abd_Al_samie Ahmed Abd_Al_moaety and No ID (Transfered from another university).
// Youssef Ali  and No ID (Transfered from another university).
// Purpose: Making it easier for the user to modify images using any of the filters.

#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"

using namespace std;
unsigned char image[SIZE][SIZE];
unsigned char image1[SIZE][SIZE];
unsigned char imagem[SIZE][SIZE];
int n;
string x;
void loadImage1();
void loadImage ();
void saveImage ();
void doSomethingForImage ();
void black_white();
void invert_filter();
void rotate_90();
void rotate_180();
void  saveImage1();
void flip_image_horizontally();
void flip_image_vertically();
void light_dark();
void merge();

int main()
{
  loadImage();
  doSomethingForImage();
  if(x=="0")
      return 0;
  else if(x=="6")
  {
      if(n==90||n==270)
      {
          saveImage1();
          return 0;
      }
  }
    saveImage();
    return 0;
}

//Make user enter photo that he want to modify it.
void loadImage ()
{
   char imageFileName[100];

   cout << "Enter the source image file name: ";
   cin >> imageFileName;

   // Add to it .bmp extension and load image
   strcat (imageFileName, ".bmp");
   readGSBMP(imageFileName, image);
}
// To use it in merge filter allow user to enter second photo.
void loadImage1 ()
{
    char imageFileName[100];

    cout << "Enter the source image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    readGSBMP(imageFileName, imagem);
}
// Save image in another file after modification .
void saveImage ()
{
   char imageFileName[100];

   cout << "Enter the target image file name: ";
   cin >> imageFileName;

   // Add to it .bmp extension and load image
   strcat (imageFileName, ".bmp");
   writeGSBMP(imageFileName, image);
}
// We use this function in rotate filter to save image after rotation.
void saveImage1 ()
{
    char imageFileName[100];

    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    writeGSBMP(imageFileName, image1);
}

// This function we called it in main to make user select filter that he wanted and call the function of the filter.
void doSomethingForImage()
{
    cout<<"Please select a filter to apply or 0 to exit: \n";
    cout<<"1-Black & White Filter\n"<<"2-Invert Filter\n"<<"3-Merge Filter\n";
    cout<<"4-Flip Image\n"<<"5-Darken and Lighten Image\n"<<"6-Rotate Image\n";
    cout<<"s-Save the image to a file\n"<<"0-Exit\n";

    cin>>x; // this variable that make user select no. of filter that he wanted
    if(x=="1")
        black_white();
    else if(x=="2")
        invert_filter();
    else if(x=="3")
    {
        merge();
    }
    else if (x=="4")
    {
        cout << "Do you want to flip (h)orizontally or (v)ertically ?"<<endl;
        char f;
        cin >> f;// make user select h or v
        if (f=='h')
            flip_image_horizontally();
        else if (f=='v')
        flip_image_vertically();
    }
    else if(x=="5")
    {
        light_dark();
    }
    else if(x=="6")
    {
        cout<<"Rotate (90), (180) or (270) degrees? ";
        cin>>n; // user select the degree of rotate that he want to happen in photo.
        if(n==90)
            rotate_90();
        else if(n==180)
            rotate_180();
        else if(n==270) // we call function rotate 180 and rotate 90.
        {
            rotate_180();
            rotate_90();
        }
    }


}
// this function that turn the photo to black & white.
void black_white()
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (image[i][j] > 127)
                image[i][j] = 255;
            else
                image[i][j] = 0;
        }
    }
}
// this function that invert the photo .
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
// this function flip the image horizontally.
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
// this function flip the image vertically.
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
// this filter rotate photo 90 degree.
void rotate_90()
{
    for (int i = 255; i >=0; i--)
    {
        for (int j = 0; j< SIZE; j++)
        {
            image1[j][i]=image[255-i][j];
        }
    }

}
// this filter rotate photo 180 degree.
void rotate_180()
{
    for (int i = 0; i < SIZE/2; i++)
    {
        for (int j = 0; j< SIZE; j++)
        {
            int t=image[i][j];
            image[i][j]=image[255-i][255-j];
            image[255-i][255-j]=t;
        }
    }

}
// this function contain two function one make photo lighter and other darker.
void light_dark() {
    char x;
    cout<<"Do you want to (d)arken or (l)ighten ?";
    cin>>x; //this variable make user select what he wants to do in photo .
    if (x== 'l')// make photo lighter
    {
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {int x=255-image [i][j];
                x=x/2;
                image [i][j]+=x;
            }
        }
    }
    else if (x== 'd' )//make photo darker.
    {
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                image [i][j]/=2;

            }
        }
    }
}
//this function merge to photo together.
void merge()
{

    loadImage1();

        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                image[i][j] = image[i][j] / 2 + imagem[i][j] / 2;
            }

        }
    }