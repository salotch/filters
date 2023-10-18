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
double pi=3.1415927;
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
void Enlarge_image ();
void Shuffle_image();
void Skew_Horizontally ();
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
  else if(x=="8")
  {
      saveImage1();
      return 0;
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

    cout<<"1-Black & White Filter\n"<<"2-Invert Filter\n"<<"3-Merge Filter\n";
    cout<<"4-Flip Image\n"<<"5-Darken and Lighten Image\n"<<"6-Rotate Image\n";
    cout<<"7-Detect Image Edges\n"<<"8-Enlarge Image\n"<<"9-Shrink Image\n";
    cout<<"a-Mirror 1/2 Image\n"<<"b-Shuffle Image\n"<<"c-Blur Image\n";
     cout<<"d-Crop Image\n"<<"e-Skew Image Right\n"<<"f-Skew Image Up\n";
    cout<<"s-Save the image to a file\n"<<"0-Exit\n";
    cout<<"Please select a filter to apply or 0 to exit: ";
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
        cout << "Do you want to flip (h)horizontally or (v)vertically ?"<<endl;
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
    else if(x=="8")
    { Enlarge_image();

    }
    else if(x=="b"||x=="B")
    {
        Shuffle_image();
    }
    else if(x=="e"||x=="E")
    {
        Skew_Horizontally();
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
    char y;
    cout<<"Do you want to (d)darken or (l)lighten ?";
    cin>>y; //this variable make user select what he wants to do in photo .
    if (y== 'l')// make photo lighter
    {
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {int y=255-image [i][j];
                y=y/2;
                image [i][j]+=y;
            }
        }
    }
    else if (y== 'd' )//make photo darker.
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
    for (int i = sr; i <=sr+127 ; ++i)
    {
        z=0;
        for (int j = sc ; j <= sc+127 ; ++j)
        {
        image1[k][z]=image[i][j];
        image1[k+1][z]=image[i][j];
        image1[k][z+1]=image[i][j];
        image1[k+1][z+1]=image[i][j];
        z+=2;
        }
        k+=2;
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
    int k,z,sc=0,sr=0;
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
    n=90;
}
void Skew_Horizontally()
{cout<<"Please enter degree to skew right:";
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
