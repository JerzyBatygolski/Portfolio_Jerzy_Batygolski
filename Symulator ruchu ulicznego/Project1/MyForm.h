#pragma once

#include<cmath>
#include<cliext\vector>
#include "Car.h"

namespace Project1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;
	using namespace cliext;

	//Moje zmienne globalne

	double global_meter=0;			//globalny licznik czasu
	int meter;						//licznik czasu dla kolejnych faz œwiate³
	double time_of_green = 300;		//czas trwania zielonego œwiat³a
	double time_of_yellow = 40;		//czas trwania ¿ó³tego œwiat³a
	double pause = 25;				//czas trwania przerwy pomiêdzy zmian¹ œwiate³
	int phase;						//faza œwiate³ (zielone, ¿ó³te, czerwone, czerwone+¿ó³te) [1,2,3,4]
	int probability = 30;			//prawdopodobieñstwo powstawania samochodów

	int ns1=0;						//liczniki samochodów w kolejkach
	int ns2 = 0;
	int ns3 = 0;
	int ns4 = 0;
	int n1 = 0;
	int n2 = 0;
	int n3 = 0;
	int n4 = 0;

	int i;							//zmienne pomocnicze
	int temp1;
	int temp2;
	int temp3;
	int X;
	int Y;
	double a;
	bool b;
	int min;
	int sec;

	int max_traffic_jam = 0;		//maksymalny korek	
	int max_number_of_cars = 0;		//maksymalna liczba samochodów
	int number_of_cars = 0;			//aktualna liczba samochodów
	bool green_on[5] = {};			//okreœla czy dane zielone œwiat³o jest w³¹czone, zerowa komórka nieaktywna

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}

			//usuniêcie moich zmiennych dynamicznych
			delete vs1;
			delete vs2;
			delete vs3;
			delete vs4;
			delete v1;
			delete v2;
			delete v3;
			delete v4;
		}
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::PictureBox^  lights1_red;
	private: System::Windows::Forms::PictureBox^  lights2_green;
	private: System::Windows::Forms::PictureBox^  lights3_red;
	private: System::Windows::Forms::PictureBox^  lights4_green;
	private: System::Windows::Forms::Timer^  timer1;
	private: System::ComponentModel::IContainer^  components;

	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::PictureBox^  lights2_yellow;
	private: System::Windows::Forms::PictureBox^  lights2_ry;
	private: System::Windows::Forms::PictureBox^  lights2_red;
	private: System::Windows::Forms::PictureBox^  lights4_ry;
	private: System::Windows::Forms::PictureBox^  lights4_red;
	private: System::Windows::Forms::PictureBox^  lights4_yellow;
	private: System::Windows::Forms::PictureBox^  lights3_yellow;
	private: System::Windows::Forms::PictureBox^  lights3_green;
	private: System::Windows::Forms::PictureBox^  lights3_ry;
	private: System::Windows::Forms::PictureBox^  lights1_green;
	private: System::Windows::Forms::PictureBox^  lights1_ry;
	private: System::Windows::Forms::Button^  btn_stop;
	private: System::Windows::Forms::Button^  btn_reset;
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  zmieñToolStripMenuItem;
	private: System::Windows::Forms::PictureBox^  lights1_yellow;
	private: System::Windows::Forms::PictureBox^  picture_car;
	private: System::Windows::Forms::PictureBox^  picture_car2;

			 //Wektory kolejkowe
	private: vector<Car^> vs1;
	private: vector<Car^> vs2;
	private: vector<Car^> vs3;
	private: vector<Car^> vs4;
	private: vector<Car^> v1;
	private: vector<Car^> v2;
	private: vector<Car^> v3;
	private: vector<Car^> v4;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::TextBox^  textBox3;
	private: System::Windows::Forms::ToolStripMenuItem^  zieloneToolStripMenuItem;
	private: System::Windows::Forms::ToolStripTextBox^  toolStripTextBox1;
	private: System::Windows::Forms::ToolStripMenuItem^  ¿ó³teToolStripMenuItem;
	private: System::Windows::Forms::ToolStripTextBox^  toolStripTextBox2;
	private: System::Windows::Forms::ToolStripMenuItem^  przerwaToolStripMenuItem;
	private: System::Windows::Forms::ToolStripTextBox^  toolStripTextBox3;
	private: System::Windows::Forms::ToolStripMenuItem^  resetujToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  c¿êstoœæPojazdówToolStripMenuItem;
	private: System::Windows::Forms::ToolStripTextBox^  toolStripTextBox4;
	private: System::Windows::Forms::PictureBox^  picture_car_yellow;
	private: System::Windows::Forms::PictureBox^  picture_car_green;
	private: System::Windows::Forms::PictureBox^  picture_car_brown;
	private: System::Windows::Forms::PictureBox^  picture_car_blue;
	private: System::Windows::Forms::PictureBox^  picture_car_black;
	private: System::Windows::Forms::PictureBox^  picture_car2_black;
	private: System::Windows::Forms::PictureBox^  picture_car2_blue;
	private: System::Windows::Forms::PictureBox^  picture_car2_brown;
	private: System::Windows::Forms::PictureBox^  picture_car2_green;
	private: System::Windows::Forms::PictureBox^  picture_car2_yellow;
	private: System::Windows::Forms::CheckBox^  checkBox1;
	private: System::Windows::Forms::PictureBox^  pictureBox2;
	private: System::Windows::Forms::PictureBox^  picture_car_left;
	private: System::Windows::Forms::PictureBox^  picture_car_right;
	private: System::Windows::Forms::PictureBox^  picture_car2_right;
	private: System::Windows::Forms::PictureBox^  picture_car2_left;
	private: System::Windows::Forms::Label^  label4;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->lights1_red = (gcnew System::Windows::Forms::PictureBox());
			this->lights2_green = (gcnew System::Windows::Forms::PictureBox());
			this->lights3_red = (gcnew System::Windows::Forms::PictureBox());
			this->lights4_green = (gcnew System::Windows::Forms::PictureBox());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->lights2_yellow = (gcnew System::Windows::Forms::PictureBox());
			this->lights2_ry = (gcnew System::Windows::Forms::PictureBox());
			this->lights2_red = (gcnew System::Windows::Forms::PictureBox());
			this->lights4_ry = (gcnew System::Windows::Forms::PictureBox());
			this->lights4_red = (gcnew System::Windows::Forms::PictureBox());
			this->lights4_yellow = (gcnew System::Windows::Forms::PictureBox());
			this->lights3_yellow = (gcnew System::Windows::Forms::PictureBox());
			this->lights3_green = (gcnew System::Windows::Forms::PictureBox());
			this->lights3_ry = (gcnew System::Windows::Forms::PictureBox());
			this->lights1_green = (gcnew System::Windows::Forms::PictureBox());
			this->lights1_ry = (gcnew System::Windows::Forms::PictureBox());
			this->lights1_yellow = (gcnew System::Windows::Forms::PictureBox());
			this->btn_stop = (gcnew System::Windows::Forms::Button());
			this->btn_reset = (gcnew System::Windows::Forms::Button());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->zmieñToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->zieloneToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripTextBox1 = (gcnew System::Windows::Forms::ToolStripTextBox());
			this->¿ó³teToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripTextBox2 = (gcnew System::Windows::Forms::ToolStripTextBox());
			this->przerwaToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripTextBox3 = (gcnew System::Windows::Forms::ToolStripTextBox());
			this->resetujToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->c¿êstoœæPojazdówToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripTextBox4 = (gcnew System::Windows::Forms::ToolStripTextBox());
			this->picture_car = (gcnew System::Windows::Forms::PictureBox());
			this->picture_car2 = (gcnew System::Windows::Forms::PictureBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->picture_car_yellow = (gcnew System::Windows::Forms::PictureBox());
			this->picture_car_green = (gcnew System::Windows::Forms::PictureBox());
			this->picture_car_brown = (gcnew System::Windows::Forms::PictureBox());
			this->picture_car_blue = (gcnew System::Windows::Forms::PictureBox());
			this->picture_car_black = (gcnew System::Windows::Forms::PictureBox());
			this->picture_car2_black = (gcnew System::Windows::Forms::PictureBox());
			this->picture_car2_blue = (gcnew System::Windows::Forms::PictureBox());
			this->picture_car2_brown = (gcnew System::Windows::Forms::PictureBox());
			this->picture_car2_green = (gcnew System::Windows::Forms::PictureBox());
			this->picture_car2_yellow = (gcnew System::Windows::Forms::PictureBox());
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->picture_car_left = (gcnew System::Windows::Forms::PictureBox());
			this->picture_car_right = (gcnew System::Windows::Forms::PictureBox());
			this->picture_car2_right = (gcnew System::Windows::Forms::PictureBox());
			this->picture_car2_left = (gcnew System::Windows::Forms::PictureBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->lights1_red))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->lights2_green))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->lights3_red))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->lights4_green))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->lights2_yellow))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->lights2_ry))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->lights2_red))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->lights4_ry))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->lights4_red))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->lights4_yellow))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->lights3_yellow))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->lights3_green))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->lights3_ry))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->lights1_green))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->lights1_ry))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->lights1_yellow))->BeginInit();
			this->menuStrip1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picture_car))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picture_car2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picture_car_yellow))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picture_car_green))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picture_car_brown))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picture_car_blue))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picture_car_black))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picture_car2_black))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picture_car2_blue))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picture_car2_brown))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picture_car2_green))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picture_car2_yellow))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picture_car_left))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picture_car_right))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picture_car2_right))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picture_car2_left))->BeginInit();
			this->SuspendLayout();
			// 
			// pictureBox1
			// 
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->Location = System::Drawing::Point(0, 0);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(800, 800);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			// 
			// lights1_red
			// 
			this->lights1_red->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"lights1_red.Image")));
			this->lights1_red->Location = System::Drawing::Point(439, 329);
			this->lights1_red->Name = L"lights1_red";
			this->lights1_red->Size = System::Drawing::Size(103, 38);
			this->lights1_red->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->lights1_red->TabIndex = 1;
			this->lights1_red->TabStop = false;
			// 
			// lights2_green
			// 
			this->lights2_green->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"lights2_green.Image")));
			this->lights2_green->Location = System::Drawing::Point(439, 437);
			this->lights2_green->Name = L"lights2_green";
			this->lights2_green->Size = System::Drawing::Size(38, 103);
			this->lights2_green->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->lights2_green->TabIndex = 2;
			this->lights2_green->TabStop = false;
			// 
			// lights3_red
			// 
			this->lights3_red->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"lights3_red.Image")));
			this->lights3_red->Location = System::Drawing::Point(264, 437);
			this->lights3_red->Name = L"lights3_red";
			this->lights3_red->Size = System::Drawing::Size(103, 38);
			this->lights3_red->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->lights3_red->TabIndex = 3;
			this->lights3_red->TabStop = false;
			// 
			// lights4_green
			// 
			this->lights4_green->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"lights4_green.Image")));
			this->lights4_green->Location = System::Drawing::Point(329, 264);
			this->lights4_green->Name = L"lights4_green";
			this->lights4_green->Size = System::Drawing::Size(38, 103);
			this->lights4_green->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->lights4_green->TabIndex = 4;
			this->lights4_green->TabStop = false;
			// 
			// timer1
			// 
			this->timer1->Interval = 20;
			this->timer1->Tick += gcnew System::EventHandler(this, &MyForm::timer1_Tick);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->BackColor = System::Drawing::Color::White;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->label1->Location = System::Drawing::Point(31, 55);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(87, 32);
			this->label1->TabIndex = 5;
			this->label1->Text = L"00:00";
			// 
			// lights2_yellow
			// 
			this->lights2_yellow->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"lights2_yellow.Image")));
			this->lights2_yellow->Location = System::Drawing::Point(439, 437);
			this->lights2_yellow->Name = L"lights2_yellow";
			this->lights2_yellow->Size = System::Drawing::Size(38, 103);
			this->lights2_yellow->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->lights2_yellow->TabIndex = 6;
			this->lights2_yellow->TabStop = false;
			this->lights2_yellow->Visible = false;
			// 
			// lights2_ry
			// 
			this->lights2_ry->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"lights2_ry.Image")));
			this->lights2_ry->Location = System::Drawing::Point(439, 437);
			this->lights2_ry->Name = L"lights2_ry";
			this->lights2_ry->Size = System::Drawing::Size(38, 103);
			this->lights2_ry->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->lights2_ry->TabIndex = 7;
			this->lights2_ry->TabStop = false;
			this->lights2_ry->Visible = false;
			// 
			// lights2_red
			// 
			this->lights2_red->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"lights2_red.Image")));
			this->lights2_red->Location = System::Drawing::Point(439, 437);
			this->lights2_red->Name = L"lights2_red";
			this->lights2_red->Size = System::Drawing::Size(38, 103);
			this->lights2_red->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->lights2_red->TabIndex = 8;
			this->lights2_red->TabStop = false;
			this->lights2_red->Visible = false;
			// 
			// lights4_ry
			// 
			this->lights4_ry->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"lights4_ry.Image")));
			this->lights4_ry->Location = System::Drawing::Point(329, 264);
			this->lights4_ry->Name = L"lights4_ry";
			this->lights4_ry->Size = System::Drawing::Size(38, 103);
			this->lights4_ry->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->lights4_ry->TabIndex = 9;
			this->lights4_ry->TabStop = false;
			this->lights4_ry->Visible = false;
			// 
			// lights4_red
			// 
			this->lights4_red->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"lights4_red.Image")));
			this->lights4_red->Location = System::Drawing::Point(329, 264);
			this->lights4_red->Name = L"lights4_red";
			this->lights4_red->Size = System::Drawing::Size(38, 103);
			this->lights4_red->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->lights4_red->TabIndex = 10;
			this->lights4_red->TabStop = false;
			this->lights4_red->Visible = false;
			// 
			// lights4_yellow
			// 
			this->lights4_yellow->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"lights4_yellow.Image")));
			this->lights4_yellow->Location = System::Drawing::Point(329, 264);
			this->lights4_yellow->Name = L"lights4_yellow";
			this->lights4_yellow->Size = System::Drawing::Size(38, 103);
			this->lights4_yellow->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->lights4_yellow->TabIndex = 11;
			this->lights4_yellow->TabStop = false;
			this->lights4_yellow->Visible = false;
			// 
			// lights3_yellow
			// 
			this->lights3_yellow->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"lights3_yellow.Image")));
			this->lights3_yellow->Location = System::Drawing::Point(264, 437);
			this->lights3_yellow->Name = L"lights3_yellow";
			this->lights3_yellow->Size = System::Drawing::Size(103, 38);
			this->lights3_yellow->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->lights3_yellow->TabIndex = 13;
			this->lights3_yellow->TabStop = false;
			this->lights3_yellow->Visible = false;
			// 
			// lights3_green
			// 
			this->lights3_green->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"lights3_green.Image")));
			this->lights3_green->Location = System::Drawing::Point(264, 437);
			this->lights3_green->Name = L"lights3_green";
			this->lights3_green->Size = System::Drawing::Size(103, 38);
			this->lights3_green->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->lights3_green->TabIndex = 14;
			this->lights3_green->TabStop = false;
			this->lights3_green->Visible = false;
			// 
			// lights3_ry
			// 
			this->lights3_ry->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"lights3_ry.Image")));
			this->lights3_ry->Location = System::Drawing::Point(264, 437);
			this->lights3_ry->Name = L"lights3_ry";
			this->lights3_ry->Size = System::Drawing::Size(103, 38);
			this->lights3_ry->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->lights3_ry->TabIndex = 15;
			this->lights3_ry->TabStop = false;
			this->lights3_ry->Visible = false;
			// 
			// lights1_green
			// 
			this->lights1_green->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"lights1_green.Image")));
			this->lights1_green->Location = System::Drawing::Point(439, 329);
			this->lights1_green->Name = L"lights1_green";
			this->lights1_green->Size = System::Drawing::Size(103, 38);
			this->lights1_green->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->lights1_green->TabIndex = 16;
			this->lights1_green->TabStop = false;
			this->lights1_green->Visible = false;
			// 
			// lights1_ry
			// 
			this->lights1_ry->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"lights1_ry.Image")));
			this->lights1_ry->Location = System::Drawing::Point(439, 329);
			this->lights1_ry->Name = L"lights1_ry";
			this->lights1_ry->Size = System::Drawing::Size(103, 38);
			this->lights1_ry->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->lights1_ry->TabIndex = 17;
			this->lights1_ry->TabStop = false;
			this->lights1_ry->Visible = false;
			// 
			// lights1_yellow
			// 
			this->lights1_yellow->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"lights1_yellow.Image")));
			this->lights1_yellow->Location = System::Drawing::Point(439, 329);
			this->lights1_yellow->Name = L"lights1_yellow";
			this->lights1_yellow->Size = System::Drawing::Size(103, 38);
			this->lights1_yellow->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->lights1_yellow->TabIndex = 18;
			this->lights1_yellow->TabStop = false;
			this->lights1_yellow->Visible = false;
			// 
			// btn_stop
			// 
			this->btn_stop->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->btn_stop->Location = System::Drawing::Point(834, 55);
			this->btn_stop->Name = L"btn_stop";
			this->btn_stop->Size = System::Drawing::Size(277, 51);
			this->btn_stop->TabIndex = 19;
			this->btn_stop->Text = L"Start";
			this->btn_stop->UseVisualStyleBackColor = true;
			this->btn_stop->Click += gcnew System::EventHandler(this, &MyForm::btn_stop_Click);
			// 
			// btn_reset
			// 
			this->btn_reset->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->btn_reset->Location = System::Drawing::Point(834, 137);
			this->btn_reset->Name = L"btn_reset";
			this->btn_reset->Size = System::Drawing::Size(277, 51);
			this->btn_reset->TabIndex = 21;
			this->btn_reset->Text = L"Zacznij od nowa";
			this->btn_reset->UseVisualStyleBackColor = true;
			this->btn_reset->Click += gcnew System::EventHandler(this, &MyForm::btn_reset_Click);
			// 
			// menuStrip1
			// 
			this->menuStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->zmieñToolStripMenuItem,
					this->c¿êstoœæPojazdówToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(1164, 28);
			this->menuStrip1->TabIndex = 22;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// zmieñToolStripMenuItem
			// 
			this->zmieñToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->zieloneToolStripMenuItem,
					this->¿ó³teToolStripMenuItem, this->przerwaToolStripMenuItem, this->resetujToolStripMenuItem
			});
			this->zmieñToolStripMenuItem->Name = L"zmieñToolStripMenuItem";
			this->zmieñToolStripMenuItem->Size = System::Drawing::Size(125, 24);
			this->zmieñToolStripMenuItem->Text = L"D³ugoœæ œwiate³";
			// 
			// zieloneToolStripMenuItem
			// 
			this->zieloneToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->toolStripTextBox1 });
			this->zieloneToolStripMenuItem->Name = L"zieloneToolStripMenuItem";
			this->zieloneToolStripMenuItem->Size = System::Drawing::Size(181, 26);
			this->zieloneToolStripMenuItem->Text = L"zielone";
			this->zieloneToolStripMenuItem->MouseEnter += gcnew System::EventHandler(this, &MyForm::zieloneToolStripMenuItem_MouseEnter_1);
			// 
			// toolStripTextBox1
			// 
			this->toolStripTextBox1->Name = L"toolStripTextBox1";
			this->toolStripTextBox1->Size = System::Drawing::Size(100, 27);
			this->toolStripTextBox1->Text = L"300";
			this->toolStripTextBox1->TextChanged += gcnew System::EventHandler(this, &MyForm::toolStripTextBox1_TextChanged_1);
			// 
			// ¿ó³teToolStripMenuItem
			// 
			this->¿ó³teToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->toolStripTextBox2 });
			this->¿ó³teToolStripMenuItem->Name = L"¿ó³teToolStripMenuItem";
			this->¿ó³teToolStripMenuItem->Size = System::Drawing::Size(181, 26);
			this->¿ó³teToolStripMenuItem->Text = L"¿ó³te";
			this->¿ó³teToolStripMenuItem->MouseEnter += gcnew System::EventHandler(this, &MyForm::¿ó³teToolStripMenuItem_MouseEnter_1);
			// 
			// toolStripTextBox2
			// 
			this->toolStripTextBox2->Name = L"toolStripTextBox2";
			this->toolStripTextBox2->Size = System::Drawing::Size(100, 27);
			this->toolStripTextBox2->Text = L"40";
			this->toolStripTextBox2->TextChanged += gcnew System::EventHandler(this, &MyForm::toolStripTextBox2_TextChanged_1);
			// 
			// przerwaToolStripMenuItem
			// 
			this->przerwaToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->toolStripTextBox3 });
			this->przerwaToolStripMenuItem->Name = L"przerwaToolStripMenuItem";
			this->przerwaToolStripMenuItem->Size = System::Drawing::Size(181, 26);
			this->przerwaToolStripMenuItem->Text = L"przerwa";
			this->przerwaToolStripMenuItem->MouseEnter += gcnew System::EventHandler(this, &MyForm::przerwaToolStripMenuItem_MouseEnter_1);
			// 
			// toolStripTextBox3
			// 
			this->toolStripTextBox3->Name = L"toolStripTextBox3";
			this->toolStripTextBox3->Size = System::Drawing::Size(100, 27);
			this->toolStripTextBox3->Text = L"25";
			this->toolStripTextBox3->TextChanged += gcnew System::EventHandler(this, &MyForm::toolStripTextBox3_TextChanged_1);
			// 
			// resetujToolStripMenuItem
			// 
			this->resetujToolStripMenuItem->Name = L"resetujToolStripMenuItem";
			this->resetujToolStripMenuItem->Size = System::Drawing::Size(181, 26);
			this->resetujToolStripMenuItem->Text = L"resetuj";
			this->resetujToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::resetujToolStripMenuItem_Click_1);
			// 
			// c¿êstoœæPojazdówToolStripMenuItem
			// 
			this->c¿êstoœæPojazdówToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->toolStripTextBox4 });
			this->c¿êstoœæPojazdówToolStripMenuItem->Name = L"c¿êstoœæPojazdówToolStripMenuItem";
			this->c¿êstoœæPojazdówToolStripMenuItem->Size = System::Drawing::Size(173, 24);
			this->c¿êstoœæPojazdówToolStripMenuItem->Text = L"C¿êstoœæ pojazdów 1/x";
			// 
			// toolStripTextBox4
			// 
			this->toolStripTextBox4->Name = L"toolStripTextBox4";
			this->toolStripTextBox4->Size = System::Drawing::Size(100, 27);
			this->toolStripTextBox4->Text = L"30";
			this->toolStripTextBox4->TextChanged += gcnew System::EventHandler(this, &MyForm::toolStripTextBox4_TextChanged);
			// 
			// picture_car
			// 
			this->picture_car->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"picture_car.Image")));
			this->picture_car->Location = System::Drawing::Point(457, 102);
			this->picture_car->Name = L"picture_car";
			this->picture_car->Size = System::Drawing::Size(10, 20);
			this->picture_car->SizeMode = System::Windows::Forms::PictureBoxSizeMode::AutoSize;
			this->picture_car->TabIndex = 23;
			this->picture_car->TabStop = false;
			this->picture_car->Visible = false;
			// 
			// picture_car2
			// 
			this->picture_car2->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"picture_car2.Image")));
			this->picture_car2->Location = System::Drawing::Point(732, 80);
			this->picture_car2->Name = L"picture_car2";
			this->picture_car2->Size = System::Drawing::Size(20, 10);
			this->picture_car2->SizeMode = System::Windows::Forms::PictureBoxSizeMode::AutoSize;
			this->picture_car2->TabIndex = 25;
			this->picture_car2->TabStop = false;
			this->picture_car2->Visible = false;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->label2->Location = System::Drawing::Point(814, 238);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(265, 50);
			this->label2->TabIndex = 28;
			this->label2->Text = L"Aktualna liczba samochodów\r\nna skrzy¿owaniu";
			this->label2->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// textBox1
			// 
			this->textBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->textBox1->Location = System::Drawing::Point(1108, 248);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(44, 30);
			this->textBox1->TabIndex = 29;
			this->textBox1->Text = L"0";
			this->textBox1->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->label3->Location = System::Drawing::Point(840, 309);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(223, 50);
			this->label3->TabIndex = 30;
			this->label3->Text = L"Najwiêksza odnotowana\r\nliczba samochodów";
			this->label3->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// textBox2
			// 
			this->textBox2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->textBox2->Location = System::Drawing::Point(1108, 319);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(44, 30);
			this->textBox2->TabIndex = 31;
			this->textBox2->Text = L"0";
			this->textBox2->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// textBox3
			// 
			this->textBox3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->textBox3->Location = System::Drawing::Point(1108, 394);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(44, 30);
			this->textBox3->TabIndex = 32;
			this->textBox3->Text = L"0";
			this->textBox3->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->label4->Location = System::Drawing::Point(814, 397);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(274, 25);
			this->label4->TabIndex = 33;
			this->label4->Text = L"Najwiêkszy odnotowany korek";
			// 
			// picture_car_yellow
			// 
			this->picture_car_yellow->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"picture_car_yellow.Image")));
			this->picture_car_yellow->Location = System::Drawing::Point(548, 102);
			this->picture_car_yellow->Name = L"picture_car_yellow";
			this->picture_car_yellow->Size = System::Drawing::Size(10, 20);
			this->picture_car_yellow->SizeMode = System::Windows::Forms::PictureBoxSizeMode::AutoSize;
			this->picture_car_yellow->TabIndex = 34;
			this->picture_car_yellow->TabStop = false;
			this->picture_car_yellow->Visible = false;
			// 
			// picture_car_green
			// 
			this->picture_car_green->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"picture_car_green.Image")));
			this->picture_car_green->Location = System::Drawing::Point(532, 102);
			this->picture_car_green->Name = L"picture_car_green";
			this->picture_car_green->Size = System::Drawing::Size(10, 20);
			this->picture_car_green->SizeMode = System::Windows::Forms::PictureBoxSizeMode::AutoSize;
			this->picture_car_green->TabIndex = 35;
			this->picture_car_green->TabStop = false;
			this->picture_car_green->Visible = false;
			// 
			// picture_car_brown
			// 
			this->picture_car_brown->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"picture_car_brown.Image")));
			this->picture_car_brown->Location = System::Drawing::Point(505, 102);
			this->picture_car_brown->Name = L"picture_car_brown";
			this->picture_car_brown->Size = System::Drawing::Size(10, 20);
			this->picture_car_brown->SizeMode = System::Windows::Forms::PictureBoxSizeMode::AutoSize;
			this->picture_car_brown->TabIndex = 36;
			this->picture_car_brown->TabStop = false;
			this->picture_car_brown->Visible = false;
			// 
			// picture_car_blue
			// 
			this->picture_car_blue->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"picture_car_blue.Image")));
			this->picture_car_blue->Location = System::Drawing::Point(489, 102);
			this->picture_car_blue->Name = L"picture_car_blue";
			this->picture_car_blue->Size = System::Drawing::Size(10, 20);
			this->picture_car_blue->SizeMode = System::Windows::Forms::PictureBoxSizeMode::AutoSize;
			this->picture_car_blue->TabIndex = 37;
			this->picture_car_blue->TabStop = false;
			this->picture_car_blue->Visible = false;
			// 
			// picture_car_black
			// 
			this->picture_car_black->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"picture_car_black.Image")));
			this->picture_car_black->Location = System::Drawing::Point(473, 102);
			this->picture_car_black->Name = L"picture_car_black";
			this->picture_car_black->Size = System::Drawing::Size(10, 20);
			this->picture_car_black->SizeMode = System::Windows::Forms::PictureBoxSizeMode::AutoSize;
			this->picture_car_black->TabIndex = 38;
			this->picture_car_black->TabStop = false;
			this->picture_car_black->Visible = false;
			// 
			// picture_car2_black
			// 
			this->picture_car2_black->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"picture_car2_black.Image")));
			this->picture_car2_black->Location = System::Drawing::Point(732, 180);
			this->picture_car2_black->Name = L"picture_car2_black";
			this->picture_car2_black->Size = System::Drawing::Size(20, 10);
			this->picture_car2_black->SizeMode = System::Windows::Forms::PictureBoxSizeMode::AutoSize;
			this->picture_car2_black->TabIndex = 39;
			this->picture_car2_black->TabStop = false;
			this->picture_car2_black->Visible = false;
			// 
			// picture_car2_blue
			// 
			this->picture_car2_blue->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"picture_car2_blue.Image")));
			this->picture_car2_blue->Location = System::Drawing::Point(732, 164);
			this->picture_car2_blue->Name = L"picture_car2_blue";
			this->picture_car2_blue->Size = System::Drawing::Size(20, 10);
			this->picture_car2_blue->SizeMode = System::Windows::Forms::PictureBoxSizeMode::AutoSize;
			this->picture_car2_blue->TabIndex = 40;
			this->picture_car2_blue->TabStop = false;
			this->picture_car2_blue->Visible = false;
			// 
			// picture_car2_brown
			// 
			this->picture_car2_brown->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"picture_car2_brown.Image")));
			this->picture_car2_brown->Location = System::Drawing::Point(732, 137);
			this->picture_car2_brown->Name = L"picture_car2_brown";
			this->picture_car2_brown->Size = System::Drawing::Size(20, 10);
			this->picture_car2_brown->SizeMode = System::Windows::Forms::PictureBoxSizeMode::AutoSize;
			this->picture_car2_brown->TabIndex = 41;
			this->picture_car2_brown->TabStop = false;
			this->picture_car2_brown->Visible = false;
			// 
			// picture_car2_green
			// 
			this->picture_car2_green->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"picture_car2_green.Image")));
			this->picture_car2_green->Location = System::Drawing::Point(732, 112);
			this->picture_car2_green->Name = L"picture_car2_green";
			this->picture_car2_green->Size = System::Drawing::Size(20, 10);
			this->picture_car2_green->SizeMode = System::Windows::Forms::PictureBoxSizeMode::AutoSize;
			this->picture_car2_green->TabIndex = 42;
			this->picture_car2_green->TabStop = false;
			this->picture_car2_green->Visible = false;
			// 
			// picture_car2_yellow
			// 
			this->picture_car2_yellow->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"picture_car2_yellow.Image")));
			this->picture_car2_yellow->Location = System::Drawing::Point(732, 96);
			this->picture_car2_yellow->Name = L"picture_car2_yellow";
			this->picture_car2_yellow->Size = System::Drawing::Size(20, 10);
			this->picture_car2_yellow->SizeMode = System::Windows::Forms::PictureBoxSizeMode::AutoSize;
			this->picture_car2_yellow->TabIndex = 43;
			this->picture_car2_yellow->TabStop = false;
			this->picture_car2_yellow->Visible = false;
			// 
			// checkBox1
			// 
			this->checkBox1->AutoSize = true;
			this->checkBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->checkBox1->Location = System::Drawing::Point(845, 463);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(222, 29);
			this->checkBox1->TabIndex = 44;
			this->checkBox1->Text = L"Kolorowe samochody";
			this->checkBox1->UseVisualStyleBackColor = true;
			// 
			// pictureBox2
			// 
			this->pictureBox2->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox2.Image")));
			this->pictureBox2->Location = System::Drawing::Point(37, 96);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(57, 62);
			this->pictureBox2->SizeMode = System::Windows::Forms::PictureBoxSizeMode::AutoSize;
			this->pictureBox2->TabIndex = 45;
			this->pictureBox2->TabStop = false;
			// 
			// picture_car_left
			// 
			this->picture_car_left->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"picture_car_left.Image")));
			this->picture_car_left->Location = System::Drawing::Point(457, 164);
			this->picture_car_left->Name = L"picture_car_left";
			this->picture_car_left->Size = System::Drawing::Size(10, 20);
			this->picture_car_left->SizeMode = System::Windows::Forms::PictureBoxSizeMode::AutoSize;
			this->picture_car_left->TabIndex = 46;
			this->picture_car_left->TabStop = false;
			this->picture_car_left->Visible = false;
			// 
			// picture_car_right
			// 
			this->picture_car_right->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"picture_car_right.Image")));
			this->picture_car_right->Location = System::Drawing::Point(489, 164);
			this->picture_car_right->Name = L"picture_car_right";
			this->picture_car_right->Size = System::Drawing::Size(10, 20);
			this->picture_car_right->SizeMode = System::Windows::Forms::PictureBoxSizeMode::AutoSize;
			this->picture_car_right->TabIndex = 47;
			this->picture_car_right->TabStop = false;
			this->picture_car_right->Visible = false;
			// 
			// picture_car2_right
			// 
			this->picture_car2_right->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"picture_car2_right.Image")));
			this->picture_car2_right->Location = System::Drawing::Point(624, 164);
			this->picture_car2_right->Name = L"picture_car2_right";
			this->picture_car2_right->Size = System::Drawing::Size(20, 10);
			this->picture_car2_right->SizeMode = System::Windows::Forms::PictureBoxSizeMode::AutoSize;
			this->picture_car2_right->TabIndex = 48;
			this->picture_car2_right->TabStop = false;
			this->picture_car2_right->Visible = false;
			// 
			// picture_car2_left
			// 
			this->picture_car2_left->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"picture_car2_left.Image")));
			this->picture_car2_left->Location = System::Drawing::Point(624, 189);
			this->picture_car2_left->Name = L"picture_car2_left";
			this->picture_car2_left->Size = System::Drawing::Size(20, 10);
			this->picture_car2_left->SizeMode = System::Windows::Forms::PictureBoxSizeMode::AutoSize;
			this->picture_car2_left->TabIndex = 49;
			this->picture_car2_left->TabStop = false;
			this->picture_car2_left->Visible = false;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1164, 953);
			this->Controls->Add(this->picture_car2_left);
			this->Controls->Add(this->picture_car2_right);
			this->Controls->Add(this->picture_car_right);
			this->Controls->Add(this->picture_car_left);
			this->Controls->Add(this->pictureBox2);
			this->Controls->Add(this->checkBox1);
			this->Controls->Add(this->picture_car2_yellow);
			this->Controls->Add(this->picture_car2_green);
			this->Controls->Add(this->picture_car2_brown);
			this->Controls->Add(this->picture_car2_blue);
			this->Controls->Add(this->picture_car2_black);
			this->Controls->Add(this->picture_car_black);
			this->Controls->Add(this->picture_car_blue);
			this->Controls->Add(this->picture_car_brown);
			this->Controls->Add(this->picture_car_green);
			this->Controls->Add(this->picture_car_yellow);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->textBox3);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->menuStrip1);
			this->Controls->Add(this->btn_reset);
			this->Controls->Add(this->btn_stop);
			this->Controls->Add(this->lights3_ry);
			this->Controls->Add(this->lights3_green);
			this->Controls->Add(this->lights3_yellow);
			this->Controls->Add(this->lights4_yellow);
			this->Controls->Add(this->lights4_red);
			this->Controls->Add(this->lights4_ry);
			this->Controls->Add(this->lights2_red);
			this->Controls->Add(this->lights2_ry);
			this->Controls->Add(this->lights2_yellow);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->lights4_green);
			this->Controls->Add(this->lights3_red);
			this->Controls->Add(this->lights2_green);
			this->Controls->Add(this->picture_car);
			this->Controls->Add(this->picture_car2);
			this->Controls->Add(this->lights1_red);
			this->Controls->Add(this->lights1_yellow);
			this->Controls->Add(this->lights1_ry);
			this->Controls->Add(this->lights1_green);
			this->Controls->Add(this->pictureBox1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->lights1_red))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->lights2_green))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->lights3_red))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->lights4_green))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->lights2_yellow))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->lights2_ry))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->lights2_red))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->lights4_ry))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->lights4_red))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->lights4_yellow))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->lights3_yellow))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->lights3_green))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->lights3_ry))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->lights1_green))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->lights1_ry))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->lights1_yellow))->EndInit();
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picture_car))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picture_car2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picture_car_yellow))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picture_car_green))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picture_car_brown))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picture_car_blue))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picture_car_black))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picture_car2_black))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picture_car2_blue))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picture_car2_brown))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picture_car2_green))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picture_car2_yellow))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picture_car_left))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picture_car_right))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picture_car2_right))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picture_car2_left))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		//£adowanie formatki
private: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e) {
		meter = 0;
		global_meter = 0;
		phase = 1;
		number_of_cars = 0;
		max_number_of_cars = 0;
		max_traffic_jam = 0;
		green_on[2] = green_on[4] = green_on[3] = 0;
		green_on[1] = 1;
		btn_stop->Text = "Start";

		ns1 = ns2 = ns3 = ns4 = 0;
		n1 = n2 = n3 = n4 = 0;

		//Wyzerowanie œwiate³

		lights1_green->Visible = true;
		lights1_yellow->Visible = false;
		lights1_ry->Visible = false;
		lights1_red->Visible = false;

		lights2_green->Visible = false;
		lights2_yellow->Visible = false;
		lights2_ry->Visible = false;
		lights2_red->Visible = true;

		lights3_green->Visible = false;
		lights3_yellow->Visible = false;
		lights3_ry->Visible = false;
		lights3_red->Visible = true;

		lights4_green->Visible = false;
		lights4_yellow->Visible = false;
		lights4_ry->Visible = false;
		lights4_red->Visible = true;
}
			 
			 //Zdarzenia wykonywane po ka¿dym interwale czasowym

private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
		meter = meter + 1;
		global_meter = global_meter + (timer1->Interval * 0.001);
		
		//obs³uga licznika czasu na formatce
		sec = global_meter;
		min = sec / 60;
		sec = sec % 60;
		if(sec<10 && min<10){ label1->Text = "0"+ min.ToString() + ":" + "0" + sec.ToString(); }
		else if(sec<10){ label1->Text = min.ToString() + ":" + "0" + sec.ToString(); }
		else if(min<10){ label1->Text = "0" + min.ToString() + ":" + sec.ToString(); }
		else { label1->Text = min.ToString() + ":" + sec.ToString(); }

		//Obs³uga œwiate³ (16-fazowa)
		
		if (meter == time_of_green && phase == 1)
		{
			//lights1 change on yellow
			lights1_green->Visible = false;
			lights1_yellow->Visible = true;
			meter = 0;
			phase = 2;
		}
		else if (meter == time_of_yellow && phase == 2)
		{
			//lights1 change on red
			lights1_yellow->Visible = false;
			lights1_red->Visible = true;
			green_on[1] = 0;
			meter = 0;
			phase = 3;
		}
		else if (meter == pause && phase ==3)
		{
			//lights2 change on red+yellow	
			lights2_red->Visible = false;
			lights2_ry->Visible = true;
			meter = 0;
			phase = 4;
		}
		else if (meter == time_of_yellow && phase == 4)
		{
			//lights2 change on green
			lights2_ry->Visible = false;
			lights2_green->Visible = true;
			green_on[2] = 1;
			meter = 0;
			phase = 5;
		}
		else if (meter == time_of_green && phase == 5)
		{
			//lights2 change on yellow
			lights2_green->Visible = false;
			lights2_yellow->Visible = true;
			meter = 0;
			phase = 6;
		}
		else if (meter == time_of_yellow && phase == 6)
		{
			//lights2 change on red
			lights2_yellow->Visible = false;
			lights2_red->Visible = true;
			green_on[2] = 0;
			meter = 0;
			phase = 7;
		}
		else if (meter == pause && phase == 7)
		{
			//lights3 change on red+yellow	
			lights3_red->Visible = false;
			lights3_ry->Visible = true;
			meter = 0;
			phase = 8;
		}
		else if (meter == time_of_yellow && phase == 8)
		{
			//lights3 change on green
			lights3_ry->Visible = false;
			lights3_green->Visible = true;
			green_on[3] = 1;
			meter = 0;
			phase = 9;
		}
		else if (meter == time_of_green && phase == 9)
		{
			//lights3 change on yellow
			lights3_green->Visible = false;
			lights3_yellow->Visible = true;
			meter = 0;
			phase = 10;
		}
		else if (meter == time_of_yellow && phase == 10)
		{
			//lights3 change on red
			lights3_yellow->Visible = false;
			lights3_red->Visible = true;
			green_on[3] = 0;
			meter = 0;
			phase = 11;
		}
		else if (meter == pause && phase == 11)
		{
			//lights4 change on red+yellow	
			lights4_red->Visible = false;
			lights4_ry->Visible = true;
			meter = 0;
			phase = 12;
		}
		else if (meter == time_of_yellow && phase == 12)
		{
			//lights4 change on green
			lights4_ry->Visible = false;
			lights4_green->Visible = true;
			green_on[4] = 1;
			meter = 0;
			phase = 13;
		}
		else if (meter == time_of_green && phase == 13)
		{
			//lights4 change on yellow
			lights4_green->Visible = false;
			lights4_yellow->Visible = true;
			meter = 0;
			phase = 14;
		}
		else if (meter == time_of_yellow && phase == 14)
		{
			//lights4 change on red
			lights4_yellow->Visible = false;
			lights4_red->Visible = true;
			green_on[4] = 0;
			meter = 0;
			phase = 15;
		}
		else if (meter == pause && phase == 15)
		{
			//lights1 change on red+yellow
			lights1_red->Visible = false;
			lights1_ry->Visible = true;
			meter = 0;
			phase = 16;
		}
		else if (meter == time_of_yellow && phase == 16)
		{
			//lights1 change on green
			lights1_ry->Visible = false;
			lights1_green->Visible = true;
			green_on[1] = 1;
			meter = 0;
			phase = 1;
		}

		//Stwarzanie samochodów z prawdopodobieñstwem 1/30
		Random^ los = gcnew Random();
		temp1 = los->Next(probability);

		//tworzenie nowego samochodu
		if (temp1 == 0)
		{
			temp2 = los->Next(6);	//losowanie koloru samochodu
			number_of_cars++;
			if (number_of_cars > max_number_of_cars) { max_number_of_cars++; }
			temp1 = los->Next(4) + 1;	//losowanie pozycji startowej
			temp3 = los->Next(100);		//losowanie czy samochód skrêca

			//prawa pozycja startowa
			if (temp1 == 1)
			{
				ns1 += 1;
				Car ^test = gcnew Car(temp1);
				if (checkBox1->Checked == true)
				{
					test->turn = 0;
					switch (temp2)
					{
					case 0: test->picture->Image = picture_car2->Image; break;
					case 1: test->picture->Image = picture_car2_yellow->Image; break;
					case 2: test->picture->Image = picture_car2_brown->Image; break;
					case 3: test->picture->Image = picture_car2_green->Image; break;
					case 4: test->picture->Image = picture_car2_blue->Image; break;
					case 5: test->picture->Image = picture_car2_black->Image; break;
					}
				}
				else if(temp3<70)						//nie skrêca
				{
					test->picture->Image = picture_car2->Image;
					test->turn = 0;
				}
				else if (temp3 < 85 && temp3 >= 70)		//skrêca w prawo
				{
					test->picture->Image = picture_car2_right->Image;
					test->turn = 1;
				}
				else if (temp3 < 100 && temp3 >= 85)		//skrêca w lewo
				{
					test->picture->Image = picture_car2_left->Image;
					test->turn = 2;
				}
				test->picture->BringToFront();
				vs1.push_back(test);
				Controls->Add(test->picture);
				delete test;
			}

			//dolna pozycja startowa
			else if (temp1 == 2)
			{
				ns2 += 1;
				Car ^test = gcnew Car(temp1);
				if (checkBox1->Checked == true)
				{
					test->turn = 0;
					switch (temp2)
					{
					case 0: test->picture->Image = picture_car->Image; break;
					case 1: test->picture->Image = picture_car_yellow->Image; break;
					case 2: test->picture->Image = picture_car_brown->Image; break;
					case 3: test->picture->Image = picture_car_green->Image; break;
					case 4: test->picture->Image = picture_car_blue->Image; break;
					case 5: test->picture->Image = picture_car_black->Image; break;
					}
				}
				else if (temp3<70)						//nie skrêca
				{
					test->picture->Image = picture_car->Image;
					test->turn = 0;
				}
				else if (temp3 < 85 && temp3 >= 70)		//skrêca w prawo
				{
					test->picture->Image = picture_car_right->Image;
					test->turn = 1;
				}
				else if (temp3 < 100 && temp3 >= 85)		//skrêca w lewo
				{
					test->picture->Image = picture_car_left->Image;
					test->turn = 2;
				}
				test->picture->BringToFront();
				vs2.push_back(test);
				Controls->Add(test->picture);
				delete test;
			}

			//lewa pozycja startowa
			else if (temp1 == 3)
			{
				ns3 += 1;
				Car ^test = gcnew Car(temp1);
				if (checkBox1->Checked == true)
				{
					test->turn = 0;
					switch (temp2)
					{
					case 0: test->picture->Image = picture_car2->Image; break;
					case 1: test->picture->Image = picture_car2_yellow->Image; break;
					case 2: test->picture->Image = picture_car2_brown->Image; break;
					case 3: test->picture->Image = picture_car2_green->Image; break;
					case 4: test->picture->Image = picture_car2_blue->Image; break;
					case 5: test->picture->Image = picture_car2_black->Image; break;
					}
				}
				else if (temp3<70)						//nie skrêca
				{
					test->picture->Image = picture_car2->Image;
					test->turn = 0;
				}
				else if (temp3 < 85 && temp3 >= 70)		//skrêca w prawo
				{
					test->picture->Image = picture_car2_left->Image;
					test->turn = 1;
				}
				else if (temp3 < 100 && temp3 >= 85)		//skrêca w lewo
				{
					test->picture->Image = picture_car2_right->Image;
					test->turn = 2;
				}
				test->picture->BringToFront();
				vs3.push_back(test);
				Controls->Add(test->picture);
				delete test;
			}

			//górna pozycja startowa
			else if (temp1 == 4)
			{
				ns4 += 1;
				Car ^test = gcnew Car(temp1);
				if (checkBox1->Checked == true)
				{
					test->turn = 0;
					switch (temp2)
					{
					case 0: test->picture->Image = picture_car->Image; break;
					case 1: test->picture->Image = picture_car_yellow->Image; break;
					case 2: test->picture->Image = picture_car_brown->Image; break;
					case 3: test->picture->Image = picture_car_green->Image; break;
					case 4: test->picture->Image = picture_car_blue->Image; break;
					case 5: test->picture->Image = picture_car_black->Image; break;
					}
				}
				else if (temp3<70)						//nie skrêca
				{
					test->picture->Image = picture_car->Image;
					test->turn = 0;
				}
				else if (temp3 < 85 && temp3 >= 70)		//skrêca w prawo
				{
					test->picture->Image = picture_car_left->Image;
					test->turn = 1;
				}
				else if (temp3 < 100 && temp3 >= 85)		//skrêca w lewo
				{
					test->picture->Image = picture_car_right->Image;
					test->turn = 2;
				}
				test->picture->BringToFront();
				vs4.push_back(test);
				Controls->Add(test->picture);
				delete test;
			}
			//obs³uga statystyk
			if (ns1 > max_traffic_jam || ns2 > max_traffic_jam || ns3 > max_traffic_jam || ns4 > max_traffic_jam) 
			{
				max_traffic_jam++;
			}
		}
		delete los;

		//obs³uga samochodów w kolejkach bez œwiate³

		//1.kolejka
		//obs³uga czo³a kolejki
		if (n1 > 0)
		{
			v1[0]->Drive(v1[0]->start_position, v1[0]->a_normal);
			v1[0]->picture->Location = Point(v1[0]->x, v1[0]->y);
			v1[0]->picture->BringToFront();
			//obs³uga skrêcania
			if (v1[0]->turn>0)
			{
				//skrêt w prawo
				if (v1[0]->turn == 1 && v1[0]->x <= 304)
				{

					v1[0]->turn = 0;
					v1[0]->start_position=2;
					v1[0]->picture->Image = picture_car->Image;
					v1[0]->y -= 5;
					v1[0]->picture->Location = Point(v1[0]->x, v1[0]->y);
					v1[0]->picture->BringToFront();
					v2.push_back(v1[0]);
					v1.erase(v1.begin());
					n2++;
					n1--;
				}
				//skrêt w lewo
				else if (v1[0]->turn == 2 && v1[0]->x <= 289)
				{
					v1[0]->turn = 0;
					v1[0]->start_position=4;
					v1[0]->picture->Image = picture_car->Image;
					v1[0]->y += 5;
					v1[0]->picture->Location = Point(v1[0]->x, v1[0]->y);
					v1[0]->picture->BringToFront();
					v4.push_back(v1[0]);
					v1.erase(v1.begin());
					n4++;
					n1--;
				}
			}
			else if (v1[0]->x < 0)		//jeœli wyjecha³ poza skrzy¿owanie
			{
				delete v1[0]->picture;
				delete v1[0];
				v1.erase(v1.begin());
				n1--;
				number_of_cars--;
			}
		}
		//obs³uga reszty samochodów w kolejce
		for (i = 1; i < n1; i++)
		{
			v1[i]->front = v1[i]->x - v1[i - 1]->x;		//od³eg³oœæ do samochodu z przodu
			if (v1[i]->front>35)						//jeœli jest daleko do samochodu z przodu
			{
				v1[i]->Drive(v1[i]->start_position, v1[i]->a_normal);
				v1[i]->picture->Location = Point(v1[i]->x, v1[i]->y);
				v1[i]->picture->BringToFront();
			}
			else {				//hamuje
				v1[i]->v = 0;
				v1[i]->picture->Location = Point(v1[i]->x, v1[i]->y);
				v1[i]->picture->BringToFront();
			}
			//obs³uga skrêcania
			if (v1[i]->turn>0)
			{
				//skrêt w prawo
				if (v1[i]->turn == 1 && v1[i]->x <= 304)
				{
					vector<Car^>::iterator it = v1.begin() + i;
					v1[i]->turn = 0;
					v1[i]->start_position=2;
					v1[i]->picture->Image = picture_car->Image;
					v1[i]->y -= 5;
					v1[i]->picture->Location = Point(v1[i]->x, v1[i]->y);
					v1[i]->picture->BringToFront();
					v2.push_back(v1[i]);
					v1.erase(it);
					n2++;
					n1--;
				}
				//skrêt w lewo
				else if (v1[i]->turn == 2 && v1[i]->x <= 289)
				{
					vector<Car^>::iterator it = v1.begin() + i;
					v1[i]->turn = 0;
					v1[i]->start_position = 4;
					v1[i]->picture->Image = picture_car->Image;
					v1[i]->y += 5;
					v1[i]->picture->Location = Point(v1[i]->x, v1[i]->y);
					v1[i]->picture->BringToFront();
					v4.push_back(v1[i]);
					v1.erase(it);
					n4++;
					n1--;
				}
			}
		}
		//2. kolejka
		if (n2 > 0)
		{
			v2[0]->Drive(v2[0]->start_position, v2[0]->a_normal);
			v2[0]->picture->Location = Point(v2[0]->x, v2[0]->y);
			v2[0]->picture->BringToFront();
			//obs³uga skrêcania
			if (v2[0]->turn>0)
			{
				//skrêt w prawo
				if (v2[0]->turn == 1 && v2[0]->y <= 329)
				{
					v2[0]->turn = 0;
					v2[0]->start_position = 3;
					v2[0]->picture->Image = picture_car2->Image;
					v2[0]->x += 5;
					v2[0]->picture->Location = Point(v2[0]->x, v2[0]->y);
					v2[0]->picture->BringToFront();
					v3.push_back(v2[0]);
					v2.erase(v2.begin());
					n3++;
					n2--;
				}
				//skrêt w lewo
				else if (v2[0]->turn == 2 && v2[0]->y <= 314)
				{
					v2[0]->turn = 0;
					v2[0]->start_position = 1;
					v2[0]->picture->Image = picture_car2->Image;
					v2[0]->x -= 5;
					v2[0]->picture->Location = Point(v2[0]->x, v2[0]->y);
					v2[0]->picture->BringToFront();
					v1.push_back(v2[0]);
					v2.erase(v2.begin());
					n1++;
					n2--;
				}
			}
			else if (v2[0]->y < 25)
			{
				delete v2[0]->picture;
				delete v2[0];
				v2.erase(v2.begin());
				n2--;
				number_of_cars--;
			}
		}
		for (i = 1; i < n2; i++)
		{
			v2[i]->front = v2[i]->y - v2[i - 1]->y;
			if (v2[i]->front>35)
			{
				v2[i]->Drive(v2[i]->start_position, v2[i]->a_normal);
				v2[i]->picture->Location = Point(v2[i]->x, v2[i]->y);
				v2[i]->picture->BringToFront();
			}
			else {
				v2[i]->v = 0;
				v2[i]->picture->Location = Point(v2[i]->x, v2[i]->y);
				v2[i]->picture->BringToFront();
			}
			//obs³uga skrêcania
			if (v2[i]->turn>0)
			{
				//skrêt w prawo
				if (v2[i]->turn == 1 && v2[i]->y <= 329)
				{
					vector<Car^>::iterator it = v2.begin() + i;
					v2[i]->turn = 0;
					v2[i]->start_position = 3;
					v2[i]->picture->Image = picture_car2->Image;
					v2[i]->x += 5;
					v2[i]->picture->Location = Point(v2[i]->x, v2[i]->y);
					v2[i]->picture->BringToFront();
					v3.push_back(v2[i]);
					v2.erase(it);
					n3++;
					n2--;
				}
				//skrêt w lewo
				else if (v2[i]->turn == 2 && v2[i]->y <= 314)
				{
					vector<Car^>::iterator it = v2.begin() + i;
					v2[i]->turn = 0;
					v2[i]->start_position = 1;
					v2[i]->picture->Image = picture_car2->Image;
					v2[i]->x -= 5;
					v2[i]->picture->Location = Point(v2[i]->x, v2[i]->y);
					v2[i]->picture->BringToFront();
					v1.push_back(v2[i]);
					v2.erase(it);
					n1++;
					n2--;
				}
			}
		}
		//3.kolejka
		if (n3 > 0)
		{
			v3[0]->Drive(v3[0]->start_position, v3[0]->a_normal);
			v3[0]->picture->Location = Point(v3[0]->x, v3[0]->y);
			v3[0]->picture->BringToFront();
			//obs³uga skrêcania
			if (v3[0]->turn>0)
			{
				//skrêt w prawo
				if (v3[0]->turn == 1 && v3[0]->x >= 287)
				{
					v3[0]->turn = 0;
					v3[0]->start_position = 4;
					v3[0]->picture->Image = picture_car->Image;
					v3[0]->y += 5;
					v3[0]->picture->Location = Point(v3[0]->x, v3[0]->y);
					v3[0]->picture->BringToFront();
					v4.push_back(v3[0]);
					v3.erase(v3.begin());
					n4++;
					n3--;
				}
				//skrêt w lewo
				else if (v3[0]->turn == 2 && v3[0]->x >= 302)
				{
					v3[0]->turn = 0;
					v3[0]->start_position = 2;
					v3[0]->picture->Image = picture_car->Image;
					v3[0]->y -= 5;
					v3[0]->picture->Location = Point(v3[0]->x, v3[0]->y);
					v3[0]->picture->BringToFront();
					v2.push_back(v3[0]);
					v3.erase(v3.begin());
					n2++;
					n3--;
				}
			}
			else if (v3[0]->x > 580)
			{
				delete v3[0]->picture;
				delete v3[0];
				v3.erase(v3.begin());
				n3--;
				number_of_cars--;
			}
		}
		for (i = 1; i < n3; i++)
		{
			v3[i]->front = v3[i - 1]->x - v3[i]->x;
			if (v3[i]->front>35)
			{
				v3[i]->Drive(v3[i]->start_position, v3[i]->a_normal);
				v3[i]->picture->Location = Point(v3[i]->x, v3[i]->y);
				v3[i]->picture->BringToFront();
			}
			else {
				v3[i]->v = 0;
				v3[i]->picture->Location = Point(v3[i]->x, v3[i]->y);
				v3[i]->picture->BringToFront();
			}
			//obs³uga skrêcania
			if (v3[i]->turn>0)
			{
				//skrêt w prawo
				if (v3[i]->turn == 1 && v3[i]->x >= 287)
				{
					vector<Car^>::iterator it = v3.begin() + i;
					v3[i]->turn = 0;
					v3[i]->start_position = 4;
					v3[i]->picture->Image = picture_car->Image;
					v3[i]->y += 5;
					v3[i]->picture->Location = Point(v3[i]->x, v3[i]->y);
					v3[i]->picture->BringToFront();
					v4.push_back(v3[i]);
					v3.erase(it);
					n4++;
					n3--;
				}
				//skrêt w lewo
				else if (v3[i]->turn == 2 && v3[i]->x >= 302)
				{
					vector<Car^>::iterator it = v3.begin() + i;
					v3[i]->turn = 0;
					v3[i]->start_position = 2;
					v3[i]->picture->Image = picture_car->Image;
					v3[i]->y -= 5;
					v3[i]->picture->Location = Point(v3[i]->x, v3[i]->y);
					v3[i]->picture->BringToFront();
					v2.push_back(v3[i]);
					v3.erase(it);
					n2++;
					n3--;
				}
			}
		}
		//4.kolejka
		if (n4 > 0)
		{
			v4[0]->Drive(v4[0]->start_position, v4[0]->a_normal);
			v4[0]->picture->Location = Point(v4[0]->x, v4[0]->y);
			v4[0]->picture->BringToFront();
			//obs³uga skrêcania
			if (v4[0]->turn>0)
			{
				//skrêt w prawo
				if (v4[0]->turn == 1 && v4[0]->y >= 312)
				{
					v4[0]->turn = 0;
					v4[0]->start_position = 1;
					v4[0]->picture->Image = picture_car2->Image;
					v4[0]->x -= 5;
					v4[0]->picture->Location = Point(v4[0]->x, v4[0]->y);
					v4[0]->picture->BringToFront();
					v1.push_back(v4[0]);
					v4.erase(v4.begin());
					n1++;
					n4--;
				}
				//skrêt w lewo
				else if (v4[0]->turn == 2 && v4[0]->y >= 327)
				{
					v4[0]->turn = 0;
					v4[0]->start_position = 3;
					v4[0]->picture->Image = picture_car2->Image;
					v4[0]->x += 5;
					v4[0]->picture->Location = Point(v4[0]->x, v4[0]->y);
					v4[0]->picture->BringToFront();
					v3.push_back(v4[0]);
					v4.erase(v4.begin());
					n3++;
					n4--;
				}
			}
			else if (v4[0]->y> 605)
			{
				delete v4[0]->picture;
				delete v4[0];
				v4.erase(v4.begin());
				n4--;
				number_of_cars--;
			}
		}
		for (i = 1; i < n4; i++)
		{
			v4[i]->front = v4[i - 1]->y - v4[i]->y;
			if (v4[i]->front>35)
			{
				v4[i]->Drive(v4[i]->start_position, v4[i]->a_normal);
				v4[i]->picture->Location = Point(v4[i]->x, v4[i]->y);
				v4[i]->picture->BringToFront();
			}
			else {
				v4[i]->v = 0;
				v4[i]->picture->Location = Point(v4[i]->x, v4[i]->y);
				v4[i]->picture->BringToFront();
			}
			//obs³uga skrêcania
			if (v4[i]->turn>0)
			{
				//skrêt w prawo
				if (v4[i]->turn == 1 && v4[i]->y >= 312)
				{
					vector<Car^>::iterator it = v4.begin() + i;
					v4[i]->turn = 0;
					v4[i]->start_position = 1;
					v4[i]->picture->Image = picture_car2->Image;
					v4[i]->x -= 5;
					v4[i]->picture->Location = Point(v4[i]->x, v4[i]->y);
					v4[i]->picture->BringToFront();
					v1.push_back(v4[i]);
					v4.erase(it);
					n1++;
					n4--;
				}
				//skrêt w lewo
				else if (v4[i]->turn == 2 && v4[i]->y >= 327)
				{
					vector<Car^>::iterator it = v4.begin() + i;
					v4[i]->turn = 0;
					v4[i]->start_position = 3;
					v4[i]->picture->Image = picture_car2->Image;
					v4[i]->x += 5;
					v4[i]->picture->Location = Point(v4[i]->x, v4[i]->y);
					v4[i]->picture->BringToFront();
					v3.push_back(v4[i]);
					v4.erase(it);
					n3++;
					n4--;
				}
			}
		}

		///////////////////////////////////////////////
		//Obs³uga samochodów w kolejkach ze œwiat³ami//
		///////////////////////////////////////////////

		//obs³uga czo³a kolejek
		//1.kolejka
		if(ns1>0)						//jeœli w kolejce jest jakiœ samochód
		{
			if (n1 > 0) { vs1[0]->front = vs1[0]->x - v1[n1 - 1]->x;}  //odleg³oœæ do samochodu z przodu
			else { vs1[0]->front = 100; }

			if (green_on[1] == 1 || vs1[0]->x > 346)	//jeœli jest zielone lub jest daleko od œwiate³
			{
				if (vs1[0]->front > 35)				//jeœli jest daleko do samochodu z przodu
				{
					a = vs1[0]->a_normal;
				}
				else {								//jeœli jest blisko to hamuje (przez 10 tick'ów)
					a = 0;
					if (v1[n1 - 1]->a < v1[n1 - 1]->a_normal) { vs1[0]->v = vs1[0]->v - 0.15; }
					else { vs1[0]->v = 0.2; }
					if (vs1[0]->v < 0) { vs1[0]->v = 0; }
				}
				vs1[0]->Drive(vs1[0]->start_position, a);
				vs1[0]->picture->Location = Point(vs1[0]->x, vs1[0]->y);
				vs1[0]->picture->BringToFront();
				if(vs1[0]->x < 321)				//jeœli wyjecha³ poza œwiat³a
				{
					v1.push_back(vs1[0]);
					vs1.erase(vs1.begin());
					ns1 -= 1;
					n1 += 1;
				}
			}
			else if (green_on[1] == 0 && vs1[0]->x <= 324)		//jeœli jest czerwone i jest bardzo blisko œwiate³
			{
				vs1[0]->v = 0.0;
				vs1[0]->a = 0;
				vs1[0]->picture->Location = Point(vs1[0]->x, vs1[0]->y);
				vs1[0]->picture->BringToFront();
			}
			else if (green_on[1] == 0 && vs1[0]->x <= 346)		//p³ynne hamowanie
			{
				vs1[0]->v = 0.95*vs1[0]->v;
				vs1[0]->a = 0;
				if (vs1[0]->v < 0) { vs1[0]->v = 0; }
				vs1[0]->Drive(vs1[0]->start_position, a);
				vs1[0]->picture->Location = Point(vs1[0]->x, vs1[0]->y);
				vs1[0]->picture->BringToFront();
			}
		}
		//2.kolejka
		if (ns2>0)
		{
			if (n2 > 0) { vs2[0]->front = vs2[0]->y - v2[n2 - 1]->y;}  //odleg³oœæ do samochodu z przodu
			else { vs2[0]->front = 100;}
			if (green_on[2] == 1 || vs2[0]->y > 371)	//jeœli jest zielone lub jest daleko od œwiate³
			{
				if (vs2[0]->front > 35)				//jeœli jest daleko do samochodu z przodu
				{
					a = vs2[0]->a_normal;
				}
				else {								//jeœli jest blisko to hamuje (przez 10 tick'ów)
					a = 0;
					if (v2[n2 - 1]->a < v2[n2 - 1]->a_normal) { vs2[0]->v = vs2[0]->v - 0.15; }
					else { vs2[0]->v = 0.2; }
					if (vs2[0]->v < 0) { vs2[0]->v = 0; }
				}
				vs2[0]->Drive(vs2[0]->start_position, a);
				vs2[0]->picture->Location = Point(vs2[0]->x, vs2[0]->y);
				vs2[0]->picture->BringToFront();
				if (vs2[0]->y < 346)
				{
					v2.push_back(vs2[0]);
					vs2.erase(vs2.begin());
					ns2 -= 1;
					n2 += 1;
				}
			}
			else if (green_on[2] == 0 && vs2[0]->y <= 349)
			{
				vs2[0]->v = 0.0;
				vs2[0]->a = 0;
				vs2[0]->picture->Location = Point(vs2[0]->x, vs2[0]->y);
				vs2[0]->picture->BringToFront();
			}
			else if (green_on[2] == 0 && vs2[0]->y <= 371)		//p³ynne hamowanie
			{
				vs2[0]->v = 0.95* vs2[0]->v;
				vs2[0]->a = 0;
				if (vs2[0]->v < 0) { vs2[0]->v = 0; }
				vs2[0]->Drive(vs2[0]->start_position, a);
				vs2[0]->picture->Location = Point(vs2[0]->x, vs2[0]->y);
				vs2[0]->picture->BringToFront();
			}
		}
		//3.kolejka
		if (ns3>0)
		{
			if (n3 > 0) { vs3[0]->front = v3[n3 - 1]->x - vs3[0]->x;}  //odleg³oœæ do samochodu z przodu
			else { vs3[0]->front = 100;}
			if (green_on[3] == 1 || vs3[0]->x < 235)	//jeœli jest zielone lub jest daleko od œwiate³
			{
				if (vs3[0]->front > 35)				//jeœli jest daleko do samochodu z przodu
				{
					a = vs3[0]->a_normal;
				}
				else {								//jeœli jest blisko to hamuje (przez 10 tick'ów)
					a = 0;
					if (v3[n3 - 1]->a < v3[n3 - 1]->a_normal) { vs3[0]->v = vs3[0]->v - 0.15; }
					else { vs3[0]->v = 0.2; }
					if (vs3[0]->v < 0) { vs3[0]->v = 0; }
				}
				vs3[0]->Drive(vs3[0]->start_position, a);
				vs3[0]->picture->Location = Point(vs3[0]->x, vs3[0]->y);
				vs3[0]->picture->BringToFront();
				if (vs3[0]->x > 260)
				{
					v3.push_back(vs3[0]);
					vs3.erase(vs3.begin());
					ns3 -= 1;
					n3 += 1;
				}
			}
			else if (green_on[3] == 0 && vs3[0]->x >=257)
			{
				vs3[0]->v = 0.0;
				vs3[0]->a = 0;
				vs3[0]->picture->Location = Point(vs3[0]->x, vs3[0]->y);
				vs3[0]->picture->BringToFront();
			}
			else if (green_on[3] == 0 && vs3[0]->x >= 235)		//p³ynne hamowanie
			{
				vs3[0]->v = 0.95 * vs3[0]->v;
				vs3[0]->a = 0;
				if (vs3[0]->v < 0) { vs3[0]->v = 0; }
				vs3[0]->Drive(vs3[0]->start_position, a);
				vs3[0]->picture->Location = Point(vs3[0]->x, vs3[0]->y);
				vs3[0]->picture->BringToFront();
			}
		}
		//4.kolejka
		if (ns4>0)
		{
			if (n4 > 0) { vs4[0]->front = v4[n4 - 1]->y - vs4[0]->y;}  //odleg³oœæ do samochodu z przodu
			else { vs4[0]->front = 100;}
			if (green_on[4] == 1 || vs4[0]->y < 260)	//jeœli jest zielone lub jest daleko od œwiate³
			{
				if (vs4[0]->front > 35)				//jeœli jest daleko do samochodu z przodu
				{
					a = vs4[0]->a_normal;
				}
				else {								//jeœli jest blisko to hamuje (przez 10 tick'ów)
					a = 0;
					if (v4[n4 - 1]->a < v4[n4 - 1]->a_normal) { vs4[0]->v = vs4[0]->v - 0.15; }
					else { vs4[0]->v = 0.2; }
					if (vs4[0]->v < 0) { vs4[0]->v = 0; }
				}
				vs4[0]->Drive(vs4[0]->start_position, a);
				vs4[0]->picture->Location = Point(vs4[0]->x, vs4[0]->y);
				vs4[0]->picture->BringToFront();
				if (vs4[0]->y > 285)
				{
					v4.push_back(vs4[0]);
					vs4.erase(vs4.begin());
					ns4 -= 1;
					n4 += 1;
				}
			}
			else if (green_on[4] == 0 && vs4[0]->y >= 282)
			{
				vs4[0]->v = 0.0;
				vs4[0]->a = 0;
				vs4[0]->picture->Location = Point(vs4[0]->x, vs4[0]->y);
				vs4[0]->picture->BringToFront();
			}
			else if (green_on[4] == 0 && vs4[0]->y >= 260)		//p³ynne hamowanie
			{
				vs4[0]->v = 0.95 * vs4[0]->v;
				vs4[0]->a = 0;
				if (vs4[0]->v < 0) { vs4[0]->v = 0; }
				vs4[0]->Drive(vs4[0]->start_position, a);
				vs4[0]->picture->Location = Point(vs4[0]->x, vs4[0]->y);
				vs4[0]->picture->BringToFront();
			}
		}

		//obs³uga reszty samochodów w kolejkach ze œwiat³ami
		//1.kolejka
		for (i = 1; i < ns1; i++)
		{
			vs1[i]->front = vs1[i]->x - vs1[i - 1]->x;		//od³eg³oœæ do samochodu z przodu
			if (vs1[i]->front>35)					//jeœli jest daleko do samochodu z przodu
			{
				a = vs1[i]->a_normal;
			}
			else {				//jeœli jest blisko to hamuje (przez 10 tick'ów)
				a = 0;
				if (vs1[i - 1]->a < vs1[i - 1]->a_normal) { vs1[i]->v = vs1[i]->v - 0.15; }
				else { vs1[i]->v = 0.2; }
				if (vs1[i]->v < 0) { vs1[i]->v = 0; }
			}
			vs1[i]->Drive(vs1[i]->start_position, a);
			vs1[i]->picture->Location = Point(vs1[i]->x, vs1[i]->y);
			vs1[i]->picture->BringToFront();
		}
		//2.kolejka
		for (i = 1; i < ns2; i++)
		{
			vs2[i]->front = vs2[i]->y - vs2[i - 1]->y;
			if (vs2[i]->front>35)
			{
				a = vs2[i]->a_normal;
			}
			else {
				a = 0;
				if (vs2[i - 1]->a < vs2[i - 1]->a_normal) { vs2[i]->v = vs2[i]->v - 0.15; }
				else { vs2[i]->v = 0.2; }
				if (vs2[i]->v < 0) { vs2[i]->v = 0; }
			}
			vs2[i]->Drive(vs2[i]->start_position, a);
			vs2[i]->picture->Location = Point(vs2[i]->x, vs2[i]->y);
			vs2[i]->picture->BringToFront();
		}
		//3.kolejka
		for (i = 1; i < ns3; i++)
		{
			vs3[i]->front = vs3[i - 1]->x - vs3[i]->x;
			if (vs3[i]->front>35)
			{
				a = vs3[i]->a_normal;
			}
			else {
				a = 0;
				if (vs3[i - 1]->a < vs3[i - 1]->a_normal) { vs3[i]->v = vs3[i]->v - 0.15; }
				else { vs3[i]->v = 0.2; }
				if (vs3[i]->v < 0) { vs3[i]->v = 0; }
			}
			vs3[i]->Drive(vs3[i]->start_position, a);
			vs3[i]->picture->Location = Point(vs3[i]->x, vs3[i]->y);
			vs3[i]->picture->BringToFront();
		}
		//4.kolejka
		for (i = 1; i < ns4; i++)
		{
			vs4[i]->front = vs4[i - 1]->y - vs4[i]->y;
			if ( vs4[i]->front>35)
			{
				a = vs4[i]->a_normal;
			}
			else {
				a = 0;
				if (vs4[i - 1]->a < vs4[i - 1]->a_normal) { vs4[i]->v = vs4[i]->v - 0.15; }
				else { vs4[i]->v = 0.2; }
				if (vs4[i]->v < 0) { vs4[i]->v = 0; }
			}
			vs4[i]->Drive(vs4[i]->start_position, a);
			vs4[i]->picture->Location = Point(vs4[i]->x, vs4[i]->y);
			vs4[i]->picture->BringToFront();
		}

		//obs³uga textboxów
		textBox1->Text = number_of_cars.ToString();
		textBox2->Text = max_number_of_cars.ToString();
		textBox3->Text = max_traffic_jam.ToString();
}
			 //Obs³uga przycisku Czas stop/Wznów
private: System::Void btn_stop_Click(System::Object^  sender, System::EventArgs^  e) {
	if (btn_stop->Text == "Czas stop") 
	{
		btn_stop->Text = "Wznów";
		timer1->Stop();
	}
	else
	{
		btn_stop->Text = "Czas stop";
		timer1->Start();
	}
}

		 //Obs³uga przycisku Zacznij od nowa
private: System::Void btn_reset_Click(System::Object^  sender, System::EventArgs^  e) {
	timer1->Stop();
	for (i = 0; i < n1; i++)
	{
		delete v1[i]->picture;
	}
	for (i = 0; i < n2; i++)
	{
		delete v2[i]->picture;
	}
	for (i = 0; i < n3; i++)
	{
		delete v3[i]->picture;
	}
	for (i = 0; i < n4; i++)
	{
		delete v4[i]->picture;
	}
	v1.clear();
	v2.clear();
	v3.clear();
	v4.clear();

	for (i = 0; i < ns1; i++)
	{
		delete vs1[i]->picture;
	}
	for (i = 0; i < ns2; i++)
	{
		delete vs2[i]->picture;
	}
	for (i = 0; i < ns3; i++)
	{
		delete vs3[i]->picture;
	}
	for (i = 0; i < ns4; i++)
	{
		delete vs4[i]->picture;
	}
	vs1.clear();
	vs2.clear();
	vs3.clear();
	vs4.clear();

	btn_stop->Text = "Wznów";
	label1->Text = "0";
	MyForm_Load(sender, e);
}
		 
		 //Obs³uga zmiany d³ugoœci œwiate³ (zabezpieczona)
private: System::Void Message1(){
	MessageBox::Show("WprowadŸ liczbê ca³kowit¹ wiêksz¹ od 0!!", "B³ad", MessageBoxButtons::OK, MessageBoxIcon::Error);
}
private: System::Void zieloneToolStripMenuItem_MouseEnter_1(System::Object^  sender, System::EventArgs^  e) {
	toolStripTextBox1->Text = time_of_green.ToString();
}
private: System::Void ¿ó³teToolStripMenuItem_MouseEnter_1(System::Object^  sender, System::EventArgs^  e) {
	toolStripTextBox2->Text = time_of_yellow.ToString();
}
private: System::Void przerwaToolStripMenuItem_MouseEnter_1(System::Object^  sender, System::EventArgs^  e) {
	toolStripTextBox3->Text = pause.ToString();
}
private: System::Void resetujToolStripMenuItem_Click_1(System::Object^  sender, System::EventArgs^  e) {
	time_of_green = 300;
	time_of_yellow = 40;
	pause = 25;
	toolStripTextBox1->Text = "300";
	toolStripTextBox2->Text = "40";
	toolStripTextBox3->Text = "25";
	btn_reset_Click(sender, e);
}
private: System::Void toolStripTextBox1_TextChanged_1(System::Object^  sender, System::EventArgs^  e) {
	if (toolStripTextBox1->Text != "")
	{
		if (toolStripTextBox1->Text == "0")
		{
			Message1();
		}
		try {
			time_of_green = Convert::ToDouble(toolStripTextBox1->Text);
			if (time_of_green != floor(time_of_green)) { Message1(); }
			btn_reset_Click(sender, e);
		}
		catch (...)
		{
			Message1();
		}
	}
	else Message1();
}
private: System::Void toolStripTextBox2_TextChanged_1(System::Object^  sender, System::EventArgs^  e) {
	if (toolStripTextBox2->Text != "")
	{
		if (toolStripTextBox2->Text == "0")
		{
			Message1();
		}
		try {
			time_of_yellow = Convert::ToDouble(toolStripTextBox2->Text);
			if (time_of_yellow != floor(time_of_yellow)) { Message1(); }
			btn_reset_Click(sender, e);
		}
		catch (...)
		{
			Message1();
		}
	}
	else Message1();
}
private: System::Void toolStripTextBox3_TextChanged_1(System::Object^  sender, System::EventArgs^  e) {
	if (toolStripTextBox3->Text != "")
	{
		if (toolStripTextBox3->Text == "0")
		{
			Message1();
		}
		try {
			pause = Convert::ToDouble(toolStripTextBox3->Text);
			if (pause != floor(pause)) { Message1(); }
			btn_reset_Click(sender, e);
		}
		catch (...)
		{
			Message1();
		}
	}
	else Message1();
}
private: System::Void toolStripTextBox4_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	timer1->Stop();
	btn_stop->Text = "Wznów";
	if (toolStripTextBox4->Text != "")
	{
		if (toolStripTextBox4->Text == "0")
		{
			Message1();
		}
		try {
			probability = Convert::ToInt32(toolStripTextBox4->Text);
		}
		catch (...)
		{
			Message1();
		}
	}
	else Message1();
}
};
}
