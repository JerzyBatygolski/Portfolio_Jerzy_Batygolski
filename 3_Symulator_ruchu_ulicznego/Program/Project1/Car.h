#pragma once

ref class Car
{
public:
		int start_x;			//punkt startowy dla samochodu (piksele)
		int start_y;

		int aim_x;				//punkt docelowy (piksele)
		int aim_y;

		int start_position;		//pozycja startowa [1,2,3,4]
		int end_position;		//pozycja koñcowa [1,2,3,4]
		int turn;				//okreœla czy samochód skrêca (0 - prosto, 1 - prawo, 2 - lewo)

		double front;			//odleg³oœæ do samochodu z przodu

		double v_limit;			//limit prêdkoœci
		double a_normal;		//przyspieszenie normalne

		double x;				//po³o¿enie chwilowe
		double y;
		double v;				//prêdkoœæ chwilowa
		double a;				//przyspieszenie chwilowe

		double x_;				//po³o¿enie chwilowe dla chwili t(0-)
		double y_;
		double v_;				//prêdkoœæ chwilowa dla chwili t(0-)

		System::Windows::Forms::PictureBox^ picture;			//obrazek samochodu

		Car(int position);	//standardowy konstruktor, pozycja[lewa,dó³,prawa,góra]
		void Drive(int direction, double acceleration);		//metoda Drive wraz z kierunkiem jazdy i przyspieszeniem
};

