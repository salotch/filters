//
// Created by yara2 on 10/18/2023.
//
#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"
#include "func_name.h"
using namespace std;
unsigned char image[SIZE][SIZE][RGB];
unsigned char image1[SIZE][SIZE][RGB];

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

void doSomethingForImage() {
    cout<<"1-Black & White Filter\n"<<"2-Invert Filter\n"<<"3-Merge Filter\n";
    cout<<"4-Flip Image\n"<<"5-Darken and Lighten Image\n"<<"6-Rotate Image\n";
    cout<<"7-Detect Image Edges\n"<<"8-Enlarge Image\n"<<"9-Shrink Image\n";
    cout<<"a-Mirror 1/2 Image\n"<<"b-Shuffle Image\n"<<"c-Blur Image\n";
    cout<<"d-Crop Image\n"<<"e-Skew Image Right\n"<<"f-Skew Image Up\n";
    cout<<"s-Save the image to a file\n"<<"0-Exit\n";
    cout<<"Please select a filter to apply or 0 to exit: ";
    string x;
    cin>>x;
    if(x=="1")
        black_white();
    else if(x=="2")
        invert_filter();
    else if(x=="3")
        merge();
    else if(x=="6")
    {
        cout<<"Rotate (90), (180) or (270) degrees? ";
        cin>>n; // user select the degree of rotate that he want to happen in photo.
        if(n==90)
            rotate_90();
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
    else if(x=="7")
         edges();
    else if(x=="8")
        Enlarge_image();
    else if(x=="b"||x=="B")
        Shuffle_image();
    else if(x=="e"||x=="E")
        Skew_Horizontally();
    else if(x=="f"||x=="F")
        Skew_Vertically();
    else if(x=="c"||x=="C") {
        blur();
        blur();
        blur();
        blur();
    }
    else if(x=="9")
       shrink();
    if(x=="5")
        light_dark();
    else if (x =="a")
    {
        char f;
        cout<<"Mirror (l)eft, (r)ight, (u)pper, (d)own side?"<<endl;
        cin>>f;
        if (f=='u')
            upper_mirror();
        else if (f=='d')
            lower_mirror();
        else if(f=='l')
            left_mirror();
        else if (f=='r')
            right_mirror();
    }
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
    else if (x=="d")
        crop_image();
    else if (x=="7")
        edges();
    else if(x=="s"||x=="S")
    {
        SAVE=false;
    }
    else if(x=="0")
        EXIT=true;
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
void invert_filter()
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
void Enlarge_image()
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
    for (int i = 0; i <SIZE ; ++i) {
        for (int j = 0; j <SIZE ; ++j) {
            for (int k = 0; k < RGB; ++k)
            {
                image1[i][j][k]=image[i][j][k];//copy image to image 1
            }
        }
    }
    for (int k = 0; k < RGB; ++k) {
        int l=0,z;
        for (int i = sr; i <= sr + 127; ++i) {
            z = 0;
            for (int j = sc; j <= sc + 127; ++j) {


                image[l][z][k] = image1[i][j][k];
                image[l + 1][z][k] = image1[i][j][k];
                image[l][z + 1][k] = image1[i][j][k];
                image[l + 1][z + 1][k] = image1[i][j][k];
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
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            for (int k = 0; k < RGB; ++k) {
                image[i][j][k]=image1[i][j][k];
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
void Skew_Vertically() {

    cout << "Please enter degree to skew right: ";
    double angle;
    cin >> angle;
    angle = (angle * 22) / (180 * 7);
    int xx = 256 / (1 + (tan(angle)));//the base of the skew image
    for(int k=0;k<RGB;k++)
    for (int i = 0; SIZE > i; i++) {
        for (int j = 0; j < SIZE; ++j) {
            image1[(i * xx) /SIZE][j] [k]= image[i][j][k];//(xx)/SIZE is the rate of the new base to old base to shrink the image

        }
    }
    for(int k=0;k<RGB;k++)
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; ++j) {
            image[i][j][k] = 255;
        }
    }
    double step = SIZE - xx;
    double move = step / SIZE;
    for(int j=0;j<SIZE;j++)
    {
        for (int i = 0 ; i < xx; ++i)
        {
            for (int k = 0; k <RGB ; ++k)
                image[i+(int)step][j][k]= image1[i][j][k];
        }
        step-=move;
    }
}
void blur(){
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++)
            for(int k=0;k<RGB;k++)
            if ((i-1)>0&&(j-1)>0)
            {
                image [i][j][k]=((image [i-1][j-1][k]+image [i-1][j][k]+image [i-1][j+1][k]+image [i][j-1][k]+image [i][j+1][k]+image [i+1][j+1][k]+image [i+1][j][k]+image[i+1][j+1][k])/8);
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
            for (int k = 0; k < RGB; ++k)
            {
            image[i/z][j/z][k] =image[i][j][k];
            }
        }
    }
    for (int i=x; i < SIZE; i++)//to make the rest of the image white
    {
        for (int j=0 ; j < SIZE; j++)
        {
            for (int k = 0; k < RGB; ++k)
        {
                image[i][j][k] = 255;
        }
        }
    }
    for (int i = 0; i < SIZE; i++)//to make the rest of the image white
    {
        for (int j = 255 / z; j < SIZE; j++)
        {
            for (int k = 0; k < RGB; ++k)
            {
                image[i][j][k] = 255;
            }
        }
    }
}
void rotate_90()
{
    for (int i = 0; i <SIZE ; ++i) {
        for (int j = 0; j <SIZE ; ++j) {
            for (int k = 0; k < RGB; ++k)
            {
            image1[i][j][k]=image[i][j][k];
            }
        }
    }

    for (int i = 255; i >=0; i--)
    {
        for (int j = 0; j< SIZE; j++) {
            for (int k = 0; k < RGB; ++k) {
                image[j][i][k] = image1[255 - i][j][k];
            }
        }
    }

}
void light_dark()
{
    char x;
    cout<<"Do you want to (d)arken or (l)ighten ?";
    cin>>x;
    if (x== 'l')
    {
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                for(int k=0;k<RGB;k++)
                {
                    int x = 255 - image[i][j][k];
                    x = x / 2;
                    image[i][j][k] += x;
                }
            }
        }
    }
    else if (x== 'd' )
    {
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                for(int k=0;k<RGB;k++) {

                    image[i][j][k] /= 2;
                }

            }
        }
    }

}
void upper_mirror()
{
    for (int i=127;i<SIZE;i++)
    {
        for(int j=0;j<SIZE;j++)
        {
            for(int k=0;k<RGB;k++) {
                image[i][j][k] = image[255 - i][j][k];
            }
        }
    }
}
void lower_mirror()
{
    for (int i=0;i<127;i++)
    {
        for(int j=0;j<SIZE;j++)
        {
            for(int k=0;k<RGB;k++) {

                image[i][j][k] = image[255 - i][j][k];
            }
        }
    }
}
void left_mirror()
{
    for (int j=127;j<SIZE;j++)
    {
        for(int i=0;i<SIZE;i++)
        {
            for(int k=0;k<RGB;k++) {
                image[i][j][k] = image[i][255 - j][k];
            }
        }
    }
}
void right_mirror()
{
    for (int j=0;j<127;j++)
    {
        for(int i=0;i<SIZE;i++)
        {
            for(int k=0;k<RGB;k++) {
                image[i][j][k] = image[i][255 - j][k];
            }
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
            for (int k=0;k<RGB;++k) {
                temp = image[i][j][k];
                image[i][j][k] = image[i][255 - j][k];
                image[i][255 - j][k] = temp;
            }
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
            for(int k=0;k<RGB;k++) {
                temp = image[i][j][k];
                image[i][j][k] = image[255 - i][j][k];
                image[255 - i][j][k] = temp;
            }
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
            for (int k=0;k<RGB;++k) {
                if (((i >= x) && (i <= x + l)) && (j >= y && (j <= y + w)))
                    continue;
                else
                    image[i][j][k] = 255;
            }
        }
    }
}

void edges() {

    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            for (int k = 0; k < RGB; ++k) {
                image1[i][j][k] = image[i][j][k];//copy image to image 1
                image[i][j][k] =255;
            }
        }
    }
    for (int i = 0; i < SIZE ; i++) {
        for (int j = 0; j < SIZE ; j++) {
            for (int k = 0; k < RGB; k++) {
                for (int l = -1; l <= 1; ++l) {
                    for (int m = -1; m <= 1; ++m) {
                        if ((image1[i][j][k] - image1[i + l][j + m][k]) >= 30)
                            image[i][j][k] = 0;

                    }
                }

            }
        }
    }
black_white();
}