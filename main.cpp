//
// Created by yara2 on 10/18/2023.
//
#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"

using namespace std;
unsigned char image[SIZE][SIZE][RGB];
unsigned char image1[SIZE][SIZE][RGB];
unsigned char imagem[SIZE][SIZE][RGB];
void loadImage ();
void loadImage1();
void saveImage ();
void saveImage1 ();
void doSomethingForImage ();
void invert();
int n;
string x;
void black_white();
void merge();
void enlarge();
void Shuffle_image ();
void Skew_Horizontally();
int main()
{
    loadImage();
    doSomethingForImage();
    saveImage();
    return 0;
}

//_________________________________________
void loadImage () {
    char imageFileName[100];

    // Get colour scale image file name
    cout << "Enter the source image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    readRGBBMP(imageFileName, image);
}
void loadImage1 () {
    char imageFileName[100];

    // Get colour scale image file name
    cout << "Enter the source image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    readRGBBMP(imageFileName, image1);
}
void saveImage () {
    char imageFileName[100];

    // Get colour scale image target file name
    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    writeRGBBMP(imageFileName, image);
}
void saveImage1 () {
    char imageFileName[100];

    // Get colour scale image target file name
    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    writeRGBBMP(imageFileName, image1);
}
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
        invert();
    else if(x=="3")
        merge();
    else if(x=="8")
         enlarge();
    else if(x=="b"||x=="B")
        Shuffle_image();
    else if(x=="e"||x=="E")
        Skew_Horizontally();
}
void black_white()
{
    int av=0;
    for(int i=0;i<SIZE;i++)
    {
        for(int j=0;j<SIZE;j++)
        {
            for(int k=0;k<RGB;k++)
            {
                av += image[i][j][k];

            }
            av /=3;
            for(int k=0;k<RGB;k++)
            {
                if(av<127)
                    image[i][j][k]=0;
                else
                    image[i][j][k]=255;

            }
            av=0;

        }
    }
}
void invert()
{
    for(int i=0;i<SIZE;i++)
    {
        for(int j=0;j<SIZE;j++)
        {
            for(int k=0;k<RGB;k++)
            {
                image[i][j][k]=255-image[i][j][k];

            }
        }
    }
}
void merge()
{
    loadImage1();
    for(int i=0;i<SIZE;i++)
    {
        for(int j=0;j<SIZE;j++)
        {
            for(int k=0;k<RGB;k++)
            {
                image[i][j][k]=(image1[i][j][k]+image[i][j][k])/2;


            }
        }
    }
}
void enlarge()
{//user will choose  one number of the four quarters to enlarge the image into a separate new image.
    int choice=0,sc=0,sr=0; //sc is for start column ,sr for the start row of the quarter the user have chose
    do{
        cout << "Which quarter to enlarge 1, 2, 3 or 4?\n";
        cin >> choice;
        if (choice == 2) {
            sc = 128;
        } else if (choice == 3) {

            sr = 128;
        } else if (choice == 4) {
            sr = 128;
            sc = 128;
        }
    }while(choice!=1&&choice!=2&&choice!=3&&choice!=4);
    //
    for (int k = 0; k < RGB; ++k) {
        int l=0,z;
        for (int i = sr; i <= sr + 127; ++i) {
            z = 0;
            for (int j = sc; j <= sc + 127; ++j) {


                image1[l][z][k] = image[i][j][k];
                image1[l + 1][z][k] = image[i][j][k];
                image1[l][z + 1][k] = image[i][j][k];
                image1[l + 1][z + 1][k] = image[i][j][k];
                z += 2;
            }
            l += 2;
        }
    }
}
void Shuffle_image()
{
    cout<<"New order of quarters ? ";
    int choice[4],nn=0;
    while(nn!=4)
    {
        cin>>choice[nn];
        if(choice[nn]!=1&&choice[nn]!=2&&choice[nn]!=3&&choice[nn]!=4)
        { cout<<"enter valid values";
            nn=0;
        }
        else
        {
            nn++;
        }
    }
    for(int ii=0;3>=ii;ii++)
    {
        int l,z,sc=0,sr=0;
        int sr1=0,sc1=0;//for  the index of image1 sc is for start column ,sr for the start row of the quarter the user have chose
        if(ii==1||ii==3)
        {
            sc1=128;
        }
        if(ii==2||ii==3)
        {
            sr1=128;
        }
        if (choice[ii] == 2||choice[ii] == 4)
        {
            sc = 128;
        }
        if (choice[ii] == 3||choice[ii] == 4)
        {
            sr = 128;
        }

        for (int k = 0; k <RGB ; ++k) {
            l=sr1;
        for (int i = sr; i <=sr+127 ; ++i)
        {
            z=sc1;
            for (int j = sc ; j <= sc+127 ; ++j)
            {
                image1[l][z][k]=image[i][j][k];
                z++;
            }
            l++;
        }
        }
    }

}
void Skew_Horizontally()
{cout<<"Please enter degree to skew right:";
    double angle;
    cin>>angle;
    angle=(angle*22)/(180*7);
    int xx = 256 / ( 1 + ( 1 / tan(angle) ) );//the base of the skew image
    for (int k = 0; k <RGB ; ++k)
        for(int i=0;SIZE>i;i++)
        {
            for (int j = 0; j < SIZE ; ++j)
            {
                image1[i][(j*xx)/SIZE][k]=image[i][j][k];//(xx)/SIZE is the rate of the new base to old base to shrink the image

            }
        }
    for (int k = 0; k <RGB ; ++k)
        for(int i=0;i<SIZE;i++)
        {
            for (int j = 0; j < SIZE; ++j)
            {
                image[i][j][k]=255;
            }
        }
    double step=SIZE-xx;
    double move=step/SIZE;

    for(int i=0;i<SIZE;i++)
    {
        for (int j = 0 ; j < xx; ++j)
        {
            for (int k = 0; k <RGB ; ++k)
                image[i][j+(int)step][k]= image1[i][j][k];
        }
        step-=move;
    }

}