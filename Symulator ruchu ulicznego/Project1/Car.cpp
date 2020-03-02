#include "Car.h"
#include <cmath>

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::IO;

Car::Car(int position)
{
	picture = gcnew System::Windows::Forms::PictureBox();
	v = v_ = a = 0;
	v_limit = 1.5;
	a_normal = 2 * pow(10, -2);

	switch (position)
	{
	case 1:
		start_position = 1;
		start_x = x = x_ = 580; start_y = y = y_ = 312;	//pozycja prawa
		aim_x = 0; aim_y = 312;			//pozycja lewa
		break;
	case 2:
		start_position = 2;
		start_x = x = x_ = 303; start_y = y = y_ = 605;	//pozycja dolna
		aim_x = 303; aim_y = 4;			//pozycja górna
		break;
	case 3:
		start_position = 3;
		start_x = x = x_ = -20; start_y = y = y_ = 328;		//pozycja lewa
		aim_x = 600; aim_y = 328;		//pozycja prawa
		break;
	case 4:
		start_position = 4;
		start_x = x = x_ = 287; start_y = y = y_ = 25;		//pozycja górna
		aim_x = 287; aim_y = 4;		//pozycja dolna
		break;
	}

	//inicjalizacja obrazka
	picture->SizeMode = System::Windows::Forms::PictureBoxSizeMode::AutoSize;
	picture->Location = Point(x, y);
	picture->BringToFront();
}

void Car::Drive(int direction, double acceleration)
{
	x_ = x;
	y_ = y;
	v_ = v;
	a = acceleration;

	if (v < v_limit){ v = v + a;}
	if (v < 0) { v = 0; }
	else if (direction == 1) //w lewo
	{
		x = x - v_ - (a / 2);
	}
	else if (direction == 2) //w górê
	{
		y = y - v_ - (a / 2);
	}
	else if (direction == 3) //w prawo
	{
		x = x + v_ + (a / 2);
	}
	else if (direction == 4) //w dó³
	{
		y = y + v_ + (a / 2);
	}
}

