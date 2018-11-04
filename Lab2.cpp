//Created By Nick Flouty
//Lab 2. Excersises 1-3 
//This program demonstrates image manipulation using recursion.

#include "EasyBMP.h"
#include "EasyBMP_DataStructures.h"
#include "EasyBMP_BMP.h"
#include "EasyBMP_VariousBMPutilities.h"
#include "EasyBMP.cpp"
#include <iostream>
#include <cstdlib> //for rand()
using namespace std;

void pattern(BMP & image)
{
	int picWidth = image.TellWidth();
	int picHeight = image.TellHeight();

	for (int i = 0; i < picWidth; ++i)	//X row
		for (int j = 0; j < picHeight; ++j) //Y col
		{
			int row = i / 32;
			int col = j / 32;
			if ((row + col) % 2 == 0)	//if even, then red
			{
				image(i, j)->Red = 255;
				image(i, j)->Green = 0;
				image(i, j)->Blue = 0;
			}
			else	//set to black
			{
				image(i, j)->Red = 0;
				image(i, j)->Green = 0;
				image(i, j)->Blue = 0;
			}
		}
}

void triangle(BMP & image, BMP & X, BMP & Y, BMP & Z, BMP & P, int counter)		//recursive function for creating triangle
{
	if (counter != 0)
	{
		int chose = rand() % 3;
		if (chose == 0)	//X
		{
			//create a red dot between x-cord and p-cord. Then recursive call but with new P being half of current P

			BMP midpoint;
			int picWidth2 = ((X.TellWidth() + P.TellWidth()) / 2);
			int picHeight2 = ((P.TellHeight() + X.TellHeight()) / 2);
			midpoint.SetSize(picWidth2, picHeight2);

			image(midpoint.TellWidth(), midpoint.TellHeight())->Red = 255;
			image(midpoint.TellWidth(), midpoint.TellHeight())->Blue = 0;
			image(midpoint.TellWidth(), midpoint.TellHeight())->Green = 0;

			triangle(image, X, Y, Z, midpoint, --counter);
		}
		else if (chose == 1) //Y
		{
			BMP midpoint;
			int picWidth2 = ((Y.TellWidth() + P.TellWidth()) / 2);
			int picHeight2 = ((P.TellHeight() + Y.TellHeight()) / 2);
			midpoint.SetSize(picWidth2, picHeight2);

			image(midpoint.TellWidth(), midpoint.TellHeight())->Red = 255;
			image(midpoint.TellWidth(), midpoint.TellHeight())->Blue = 0;
			image(midpoint.TellWidth(), midpoint.TellHeight())->Green = 0;

			triangle(image, X, Y, Z, midpoint, --counter);
		}
		else if (chose == 2) //Z
		{
			BMP midpoint;
			int picWidth2 = ((Z.TellWidth() + P.TellWidth()) / 2);
			int picHeight2 = ((P.TellHeight() + Z.TellHeight()) / 2);
			midpoint.SetSize(picWidth2, picHeight2);

			image(midpoint.TellWidth(), midpoint.TellHeight())->Red = 255;
			image(midpoint.TellWidth(), midpoint.TellHeight())->Blue = 0;
			image(midpoint.TellWidth(), midpoint.TellHeight())->Green = 0;

			triangle(image, X, Y, Z, midpoint, --counter);

		}
	}
	return;
}

void Tile(BMP & input_image, BMP & output_image)
{
	if (input_image.TellWidth() == 1)			//Base Case: when the recieved input has been reduced to a 1x1 size.
	{
		return;
	}

	BMP temp;
	temp.SetSize(input_image.TellWidth(), input_image.TellHeight());
	Rescale(input_image, 'p', 50);
	RangedPixelToPixelCopy(input_image, 0, output_image.TellWidth() / 2, output_image.TellHeight() / 2, 0, temp, 0, temp.TellHeight() / 2);

	Tile(input_image, temp);
	//****************
	RangedPixelToPixelCopy(temp, 0, output_image.TellWidth() / 2, output_image.TellHeight() / 2, 0, output_image, 0, 0);
	RangedPixelToPixelCopy(temp, 0, output_image.TellWidth() / 2, output_image.TellHeight() / 2, 0, output_image, output_image.TellHeight() / 4, 0);
	//The top two lines copy the image left and the bottom two lines copy the image down.
	RangedPixelToPixelCopy(temp, 0, output_image.TellWidth() / 2, output_image.TellHeight() / 2, 0, output_image, output_image.TellHeight() / 2, output_image.TellHeight() / 2);
	RangedPixelToPixelCopy(temp, 0, output_image.TellWidth() / 2, output_image.TellHeight() / 2, 0, output_image, output_image.TellHeight() / 2, output_image.TellHeight() / 4);
	//***************
	RangedPixelToPixelCopy(temp, 0, output_image.TellWidth() / 2, output_image.TellHeight() / 2, 0, output_image, output_image.TellHeight() / 2, 0); 
	//recursively places the images in the top right corner of the previous
}


int main()
{
	BMP board;
	board.SetSize(256, 256);
	board.SetBitDepth(8);	//color depth to 8 bits

	pattern(board);
	board.WriteToFile("testimage.bmp");
	//*********************************************************
	BMP image;
	image.SetSize(256, 256);

	BMP X, Y, Z, P;

	X.SetSize(128, 5);
	Y.SetSize(5, 251);
	Z.SetSize(251, 251);
	P.SetSize(171, 34);

	triangle(image, X, Y, Z, P, 10000);
	image.WriteToFile("sierpinski.bmp");
	//*******************************************************
	BMP input_image;
	input_image.ReadFromFile("einstein.bmp");

	BMP output_image;
	output_image.SetSize(input_image.TellWidth(), input_image.TellHeight());
	Rescale(input_image, 'p', 50);

	RangedPixelToPixelCopy(input_image, 0, output_image.TellWidth() / 2, output_image.TellHeight() / 2, 0, output_image, 0, output_image.TellHeight() / 2);	//LEFT BOTTOM CORNER
	
	Tile(input_image, output_image);
	output_image.WriteToFile("NEW_einstein.bmp");
	//********************************************************
	//system("PAUSE");
	return 0;
}
