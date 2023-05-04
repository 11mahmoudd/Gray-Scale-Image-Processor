// FCI – Programming 1 – 2022 - Assignment 3
// Program Name: CS112-2022-2nd-19-20210373-A3
// Last Modification Date: 24/4/2022
// Author1 , ID and Group: Mahmoud Mohamed Abd El-Moula -- 20210373 -- B
// Teaching Assistant: Eng. Yousra Ayman
// Purpose: Edit photos by applying some filters on it 

#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"

using namespace std;
unsigned char image[SIZE][SIZE];
unsigned char temp[SIZE][SIZE];
bool check;

void loadImage ();
void saveImage ();
void saveTemp ();
void blackAndWhite ();
void invertImage();
void mergeImages();
void darkerOrLighter();
void shrinkImage();
void enlarge();
void mirror();
void flip();

int main()
{
    bool run=true;
    int choice;
    cout<<"\nAhlan ya user ya habibi\n";
    loadImage();
    while(run && check==0)
    {
        cout<<"\n\nPlease select a filter to apply or 0 to exit:\n1- Black & White Filter\n2- Invert Filter\n3- Merge Filter\n";
        cout<<"4- Darken and Lighten Image\n5- Shrink Image\n6- Mirror Image\n7- Flip Image\n8- Enlarge Image\n0- Exit : ";
        cin>>choice;
        switch (choice)
        {
            case 0:
                cout<<"Salam, ya user ya habibi";
                run=false;
                break;
            case 1:
                blackAndWhite();
                saveImage();
                run=false;
                break;
            case 2:
                invertImage();
                saveImage();
                run=false;
                break;
            case 3:
                mergeImages();
                saveImage();
                run=false;
                break;
            case 4:
                darkerOrLighter();
                saveImage();
                run=false;
                break;
            case 5:
                shrinkImage();
                saveTemp();
                run=false;
                break;
            case 6:
                mirror();
                saveTemp();
                run=false;
                break;
            case 7:
                flip();
                saveTemp();
                run=false;
                break;
            case 8:
                enlarge();
                saveTemp();
                run=false;
                break;
            default:
                cout<<"\n***wrong choice***\n*Please enter your choice again*\n";
        }
    }
    return 0;
}

void loadImage () 
{
    bool run=true;
    char imageFileName[100];
    while(run)
    {
        cout << "\nPlease enter file name of the image to process: \n";
        cin >> imageFileName;
        strcat (imageFileName, ".bmp");
        check= readGSBMP(imageFileName, image);
        if(check==1)
        {
            cout<<"\nWrong name\nPlease reenter the name correctly ";
        }
        else
        {
            run=false;
        }
    }

}


void saveImage () {
    char imageFileName[100];

    cout << "\nEnter the target image file name: ";
    cin >> imageFileName;

    strcat (imageFileName, ".bmp");
    writeGSBMP(imageFileName, image);
}


void saveTemp () 
{
    char imageFileName[100];

    cout << "\nEnter the target image file name: ";
    cin >> imageFileName;

    strcat (imageFileName, ".bmp");
    writeGSBMP(imageFileName, temp);
}


void blackAndWhite() 
{
    long avg= 0;
        for (int i = 0; i < SIZE; i++) 
        {
            for (int j = 0; j< SIZE; j++) 
            {
                avg += image[i][j];
            }
        }
    avg /= (SIZE*SIZE);
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) 
        {
            if (image[i][j] > avg)
                image[i][j] = 255;
            else
                image[i][j] = 0;
        }
    }
}

// invert every pixel by subtract it from 255(white color)
void invertImage()
{
    for (int i = 0; i < SIZE; i++) 
    {
        for (int j = 0; j< SIZE; j++) 
        {
            image[i][j]=255-image[i][j];
        }
    }
}

// add value of 2 pixels and get its average to merge 2 photos 
void mergeImages()
{
    unsigned char mergedImage[SIZE][SIZE];
    char mergeImage[100];
    cout << "\nEnter the other source image file name to merge: ";
    cin>>mergeImage;
    strcat (mergeImage, ".bmp");
    readGSBMP(mergeImage, mergedImage);
    for (int i = 0; i < SIZE; i++) 
    {
        for (int j = 0; j< SIZE; j++) 
        {
            image[i][j] = (image[i][j]+ mergedImage[i][j]) / 2 ;
        }
    }
}

//decrease the degree of brightness of pixel or increase it by 50% by minus or add its half
void darkerOrLighter()
{
    bool run=true;
    int choice;
    while(run)
    {
        cout<<"\n1- Darken\n2- lighten : ";
        cin>>choice;
        switch (choice)
        {
            case 1:
                for (int i = 0; i < SIZE; i++) 
                {
                    for (int j = 0; j< SIZE; j++)
                    {
                        image[i][j]=image[i][j]-image[i][j]/2;
                    } 
                }
                run=false;
                break;
            case 2:
                for (int i = 0; i < SIZE; i++) 
                {
                    for (int j = 0; j< SIZE; j++)
                    {
                        if(image[i][j]+image[i][j]/2<=255)
                        {
                            image[i][j]=image[i][j]+image[i][j]/2;
                        }
                    }
                }
                run=false;
                break;
            default :
                    cout<<"\nwrong choice\nPlease enter your choice again\n";
        }
    }
}


void shrinkImage()
{
    bool run=true;
    int choice;
    while(run)
    {
        cout<<"\n1-shrink 1/2\n2-shrink 1/3\n3-shrink 1/4 : ";
        cin>>choice;
        switch(choice)
        {
            case 1:
                for (int i = 0; i < SIZE; i++) 
                {
                    for (int j = 0; j< SIZE; j++) 
                    {
                        if (i*2<=255 && j*2 <= 255)
                            temp[i][j]=image[i*2][j*2];
                        else
                        temp[i][j]=255;
                    }
                }
                run=false;
                break;
            case 2:
                for (int i = 0; i < SIZE; i++) 
                {
                    for (int j = 0; j< SIZE; j++) 
                    {
                        if (i*3<=255 && j*3 <= 255)
                            temp[i][j]=image[i*3][j*3];
                        else
                        temp[i][j]=255;
                    }
                }
                run=false;
                break;
            case 3:
                for (int i = 0; i < SIZE; i++) 
                {
                    for (int j = 0; j< SIZE; j++) 
                    {
                        if (i*4<=255 && j*4 <= 255)
                            temp[i][j]=image[i*4][j*4];
                        else
                        temp[i][j]=255;
                    }
                }
                run=false;
                break;
            default:
                cout<<"\nwrong choice\nPlease enter your choice again\n";
        }
    }
}


//copy pixels and paste it again but in inverse order to do mirror 
void mirror()
{
    bool run=true;
    int choice;
    while(run)
    {
        cout<<"\n1-1/2 left \n2-1/2 right\n3-1/2 up\n4-1/2 down : ";
        cin>>choice;
        switch(choice)
        {
            case 1:
                for (int i = 0; i < SIZE; i++) 
                {
                    for (int j = 0; j<128 ; j++) 
                    {
                        temp[i][j]=image[i][j];
                        temp[i][255-j]=temp[i][j];
                    }
                }
                run=false;
                break;
            case 2:
                for (int i = 0; i < SIZE; i++) 
                {
                    for (int j = 128; j<SIZE; j++) 
                    {
                        temp[i][j]=image[i][j];
                        temp[i][255-j]=temp[i][j];
                    }
                }
                run=false;
                break;
            case 3:
                for (int i = 0; i < 128; i++) 
                {
                    for (int j = 0; j< SIZE; j++) 
                    {
                        temp[i][j]=image[i][j];
                        temp[255-i][j]=temp[i][j];
                    }
                }
                run=false;
                break;
            case 4:
                for (int i = 128; i < SIZE; i++) 
                {
                    for (int j = 0; j< SIZE; j++) 
                    {
                        temp[i][j]=image[i][j];
                        temp[255-i][j]=temp[i][j];
                    }
                }
                run=false;
                break;
            default:
                cout<<"\nwrong choice\nPlease enter your choice again\n";
        }
    }
}


// change the place of pixels for each column or row to flip the image horizontal or vertical 
void flip()
{
        bool run=true;
    int choice;
    while(run)
    {
        cout<<"\n1- horizontally \n2- vertically : ";
        cin>>choice;
        switch(choice)
        {
            case 1:
                for (int i = 0; i < SIZE; i++) 
                {
                    for (int j = 0; j<SIZE ; j++) 
                    {
                        temp[255-i][j]=image[i][j];
                    }
                }
                run=false;
                break;
            case 2:
                for (int i = 0; i < SIZE; i++) 
                {
                    for (int j = 0; j < SIZE; j++) 
                    {
                        temp[i][255-j]=image[i][j];
                    }
                }
                run=false;
                break;
            default:
                cout<<"\nwrong choice\nPlease enter your choice again\n";
        }
    }
}


// limit an interval to divid image into quarters then copy each pixel of original image to 4 pixels of our template to large it 
void enlarge()
{
    bool run=true;
    int choice;
    while(run)
    {
        cout<<"\n   1   |   2   \n-------|------\n   3   |   4   \n";
        cout<<"\nChoose one of four quarters of the image as showen \n1- Q1\n2- Q2\n3- Q3\n4- Q4 : ";
        cin>>choice;
        switch(choice)
        {
            case 1:
                for (int i = 0,x=0; i < SIZE,x<128; i+=2,x++) 
                {
                    for (int j = 0,y=0 ;j< SIZE,y<128; j+=2,y++) 
                    {
                        temp[i][j]=image[x][y];
                        temp[i][j+1]=image[x][y];
                        temp[i+1][j]=image[x][y];
                        temp[i+1][j+1]=image[x][y];
                    }
                }
                run=false;
                break;
            case 2:
                for (int i = 0,x=0; i < SIZE,x<128; i+=2,x++) 
                {
                    for (int j = 0,y=128; j< SIZE,y<SIZE; j+=2,y++) 
                    {
                        temp[i][j]=image[x][y];
                        temp[i][j+1]=image[x][y];
                        temp[i+1][j]=image[x][y];
                        temp[i+1][j+1]=image[x][y];
                    }
                }
                run=false;
                break;
            case 3:
                for (int i = 0,x=128; i < SIZE,x<SIZE; i+=2,x++) 
                {
                    for (int j = 0,y=0; j< SIZE,y<128; j+=2,y++) 
                    {
                        temp[i][j]=image[x][y];
                        temp[i][j+1]=image[x][y];
                        temp[i+1][j]=image[x][y];
                        temp[i+1][j+1]=image[x][y];
                    }
                }
                run=false;
                break;
            case 4:
                            for (int i = 0,x=128; i < SIZE,x<SIZE; i+=2,x++) 
                {
                    for (int j = 0,y=128; j< SIZE,y<SIZE; j+=2,y++) 
                    {
                        temp[i][j]=image[x][y];
                        temp[i][j+1]=image[x][y];
                        temp[i+1][j]=image[x][y];
                        temp[i+1][j+1]=image[x][y];
                    }
                }
                run=false;
                break;
            default:
                cout<<"\nwrong choice\nPlease enter your choice again\n";
        }
    }
}