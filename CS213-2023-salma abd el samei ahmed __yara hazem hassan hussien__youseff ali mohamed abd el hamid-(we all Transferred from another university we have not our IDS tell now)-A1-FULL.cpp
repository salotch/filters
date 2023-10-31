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
#include "func_name.h"
using namespace std;
unsigned char image[SIZE][SIZE];
unsigned char image1[SIZE][SIZE];
int n;
bool EXIT=false;
bool SAVE=true;
int main()
{
  loadImage();
  do {
      doSomethingForImage();
  }while(SAVE);
  if(EXIT)
      return 0;
  saveImage();
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
    readGSBMP(imageFileName, image1);
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

// This function we called it in main to make user select filter that he wanted and call the function of the filter.
void doSomethingForImage()
{
    cout<<"1-Black & White Filter\n"<<"2-Invert Filter\n"<<"3-Merge Filter\n";
    cout<<"4-Flip Image\n"<<"5-Darken and Lighten Image\n"<<"6-Rotate Image\n";
    cout<<"7-Detect Image Edges\n"<<"8-Enlarge Image\n"<<"9-Shrink Image\n";
    cout<<"a-Mirror 1/2 Image\n"<<"b-Shuffle Image\n"<<"c-Blur Image\n";
     cout<<"d-Crop Image\n"<<"e-Skew Image Right\n"<<"f-Skew Image Up\n";
    cout<<"s-Save the image to a file\n"<<"0-Exit\n";
    cout<<"Please select a filter to apply or 0 to exit: ";
    string x;
    cin>>x; // this variable that make user select no. of filter that he wanted
    if(x=="1")
    {
        black_white();
    }
    else if(x=="2")
    {
        invert_filter();
    }
    else if(x=="3")
    {
        merge();
    }
    else if (x=="4")
    {
        cout << "Do you want to flip (h)horizontally or (v)vertically ?"<<endl;
        char f;
        cin >> f;// make user select h or v
        if (f=='h'||f=='H')
        {
            flip_image_horizontally();
        }
        else if (f=='v'||f=='V')
        {
            flip_image_vertically();
        }
    }
    else if(x=="5")
    {
        light_dark();
    }
    else if(x=="6")
    {
        cout<<"Rotate (90), (180) or (270) degrees? ";
        cin>>n; // user select the degree of rotate that he want to happen in photo.
        if(n==90) {
            rotate_90();
        }
        else if(n==180)// we call function rotate 90 two times 90*2=180
        { rotate_90();
            rotate_90();

        }
        else if(n==270) // we call function rotate 90 three times 90*3=270
        {
            rotate_90();
            rotate_90();
            rotate_90();
        }
    }
    else if(x=="b"||x=="B")
    {
        Shuffle_image();
    }
    else if(x=="e"||x=="E")
    {
        Skew_Horizontally();
    }
    else if (x =="a"||x=="A")
    {
        char f;
        cout<<"Mirror (l)eft, (r)ight, (u)pper, (d)own side?"<<endl;
        cin>>f;
        if (f=='u'||f=='U')
            upper_mirror();
        else if (f=='d'||f=='D')
            lower_mirror();
        else if(f=='l'||f=='L')
            left_mirror();
        else if (f=='r'||f=='R')
            right_mirror();
    }
    else if (x=="d"||x=="D") {
        crop_image();
    }
    else if (x=="7") {
        edges();
    }
    else if(x=="8")
    { Enlarge_image();

    }
    else if(x=="9"){
        shrink();
    }
    else if (x=="c"||x=="C")
    {
        blur();
        blur();
        blur();
    }
    else if (x=="f"||x=="F") {
        Skew_Vertically();
    }
    else if(x=="s"||x=="S")
    {
        SAVE=false;
    }
    else if(x=="0")
    { EXIT=true;
    SAVE=false;}
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
           image[i][j]=255-image[i][j];//to get the opposite gray scale
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
            image[i][j]=image[i][255-j];//switching the first column with the last column
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
            image[i][j]=image[255-i][j];//switching the first row with the last row
            image[255-i][j]=temp;
        }
    }

}
// this filter rotate photo 90 degree.
void rotate_90()
{
    for (int i = 0; i <SIZE ; ++i) {
        for (int j = 0; j <SIZE ; ++j) {
            image1[i][j]=image[i][j];//to save the rotate_image in (image)
        }
    }

    for (int i = 255; i >=0; i--)
    {
        for (int j = 0; j< SIZE; j++)
        {
            image[j][i]=image1[255-i][j];// transpose the image from right to left
        }
    }

}

// this function contain two function one make photo lighter and other darker.
void light_dark() {
    char y;
    cout<<"Do you want to (d)darken or (l)lighten ?";
    cin>>y; //this variable make user select what he wants to do in photo .
    if (y== 'l')// make photo lighter
    {
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {int y= 255-image [i][j];
                y=y/2;
                image [i][j]+=y;// reduce the dark of the image by adding y
            }
        }
    }
    else if (y== 'd' )//make photo darker.
    {
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                image [i][j]/=2;// reduce the light of the image by adding y

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
                image[i][j] = image[i][j] / 2 + image1[i][j] / 2;
            }

        }
    }

void Enlarge_image ()
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
    int k=0,z;//
    for (int i = 0; i <SIZE ; ++i) {
        for (int j = 0; j <SIZE ; ++j) {
                image1[i][j]=image[i][j];//copy image into image1
        }
    }
    for (int i = sr; i <=sr+127 ; ++i)
    {
        z=0;
        for (int j = sc ; j <= sc+127 ; ++j)
        {
        image[k][z]=image1[i][j];
        image[k+1][z]=image1[i][j];
        image[k][z+1]=image1[i][j];
        image[k+1][z+1]=image1[i][j];
        z+=2;
        }
        k+=2;
    }
//here every pixel in the quarter is copied to 4 pixels in the enlarge image
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
   }//to get valid values
for(int ii=0;3>=ii;ii++)
{
    int k,z,sc=0,sr=0;//sc is for start column ,sr for the start row of the quarter the user have chose
    int sr1=0,sc1=0;//for  the index of image1(the new order image)
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
    k=sr1;
    for (int i = sr; i <=sr+127 ; ++i)
    {
        z=sc1;
        for (int j = sc ; j <= sc+127 ; ++j)
        {
            image1[k][z]=image[i][j];
        z++;
        }
        k++;
    }
}
    for (int i = 0; i <SIZE ; ++i) {
        for (int j = 0; j <SIZE ; ++j) {
            image[i][j]=image1[i][j];
        }
    }

}
void Skew_Horizontally()
{cout<<"Please enter degree to skew right :";
    double angle;
cin>>angle;
angle=(angle*22)/(180*7);
int xx = 256 / ( 1 + ( 1 / tan(angle) ) );//the base of the skew image
for(int i=0;SIZE>i;i++)
{
    for (int j = 0; j < SIZE ; ++j)
    {
       image1[i][(j*xx)/SIZE]=image[i][j];//(xx)/SIZE is the rate of the new base to old base to shrink the image

    }
}
   for(int i=0;i<SIZE;i++)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            image[i][j]=255;
        }
    }
    double step=SIZE-xx;
    double move=step/SIZE;
    for(int i=0;i<SIZE;i++)
    {
        for (int j = 0 ; j < xx; ++j)
        {
           image[i][j+(int)step]= image1[i][j];
        }step-=move;
    }

}
void upper_mirror()
{
    for (int i=127;i<SIZE;i++)
    {
        for(int j=0;j<SIZE;j++)
        {
            image[i][j]=image[255-i][j];
        }
    }
}
void lower_mirror()
{
    for (int i=0;i<127;i++)
    {
        for(int j=0;j<SIZE;j++)
        {
            image[i][j]=image[255-i][j];
        }
    }
}
void left_mirror()
{
    for (int j=127;j<SIZE;j++)
    {
        for(int i=0;i<SIZE;i++)
        {
            image[i][j]=image[i][255-j];
        }
    }
}
void right_mirror()
{
    for (int j=0;j<127;j++)
    {
        for(int i=0;i<SIZE;i++)
        {
            image[i][j]=image[i][255-j];
        }
    }
}
void crop_image()
{
    int x,y,l,w;
    cout<< "Please Enter x & y the postion you want and Enter length and width:"<<endl;
    cout<<"Enter x: "<<endl;
    cin>>x;
    cout<<"Enter y: "<<endl;
    cin>>y;
    cout<<"Enter length: "<<endl;
    cin>>l;
    cout<<"Enter width: "<<endl;
    cin>>w;
    for (int i=0;i<SIZE;i++)
    {
        for(int j=0;j<SIZE;j++)
        {
            if (((i >= x) && (i <= x + l)) && (j >= y && (j <= y + w)))
                continue;
            else
                image[i][j]=255;
        }
    }
}
void edges()
{
    int  t = 0;
    for (int i=0;i<SIZE;i++)
    {
        for(int j=0;j<SIZE;j++)
        {
            image1[i][j]=255;
            t += image[i][j];
        }
    }
    t /= (256*256);

    for (int i=0;i<SIZE;i++)
    {
        for(int j=0;j<SIZE;j++)
        {
            if ( image[i][j]>t && (image [i][j-1]<t || image[i][j+1]<t || image[i-1][j]<t || image[i+1][j]<t))
            {
                image1[i][j]=0;
            }
            if ( image[i][j]<t && (image [i][j-1]>t || image[i][j+1]>t || image[i-1][j]>t || image[i+1][j]>t))
            {
                image1[i][j]=0;
            }
        }
    }
    for (int i = 0; i <SIZE ; ++i)
    {
        for (int j = 0; j <SIZE ; ++j) {
            image[i][j]=image1[i][j];
        }
    }
}
void blur(){
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++)
            if ((i-1)>0&&(j-1)>0)
            {image [i][j]=((image [i-1][j-1]+image [i-1][j]+image [i-1][j+1]+image [i][j-1]+image [i][j+1]+image [i+1][j+1]+image [i+1][j]+image[i+1][j+1])/8);

            }
    }

}

void shrink() {
    cout<<"choose the size you want to shrink \n" << "1- for 1/2 \n" <<  "2- for 1/3\n" << "3- for 1/4 :";
    int z;
    cin >>z;
    z++;
    int x=256/z;


    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            image[i/z][j/z] =image[i][j];
        }
    }
    for (int i=x; i < SIZE; i++)//to make the rest of the image white
    {
        for (int j=0 ; j < SIZE; j++)
        {
            image[i][j]=255;
        }
    }
    for (int i = 0; i < SIZE; i++)//to make the rest of the image white
    {
        for (int j = 255 / z; j < SIZE; j++)
        {
            image[i][j] = 255;
        }
    }
}
void Skew_Vertically() {
    cout << "Please enter degree to skew up :";
    double angle;
    cin >> angle;
    angle = (angle * 22) / (180 * 7);
    int xx = 256 / (1 + (tan(angle)));//the base of the skew image
    for (int i = 0; SIZE > i; i++) {
        for (int j = 0; j < SIZE; ++j) {
            image1[(i * xx) /SIZE][j] = image[i][j];//(xx)/SIZE is the rate of the new base to old base to shrink the image

        }
    }

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; ++j) {
            image[i][j] = 255;
        }
    }
    double step = SIZE - xx;
    double move = step / SIZE;
    for (int j = 0; j < SIZE; ++j)
    {
        for (int i = 0; i < xx; i++){
                image[i + (int) step][j] = image1[i][j];
        }
        step -= move;
    }
}
