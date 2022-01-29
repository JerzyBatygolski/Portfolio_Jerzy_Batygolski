//Tester losowosci szesciennej kostki do gry.
//Gromadzi statystyki i pokazuje je na wyswietlaczu LCD.
//Autor: Jerzy Batygolski, AiR 132036

#include<LiquidCrystal.h>
#include<EEPROM.h>

#define rs 2
#define en 3
#define d4 4
#define d5 5
#define d6 6
#define d7 7

int odczytAC = 0;
int znak = 1;
int istats[7] = {0};
int kolumny[7] = {0};
int i = 0;
int j = 0;
byte high = 0;
byte low = 0;
union data
{
  float f;
  int a;
} convert;

//stworzenie wlasnych symboli poziomu
byte jeden[8]=
{
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B11111
};
byte dwa[8]=
{
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B11111,
  B11111
};
byte trzy[8]=
{
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B11111,
  B11111,
  B11111
};
byte cztery[8]=
{
  B00000,
  B00000,
  B00000,
  B00000,
  B11111,
  B11111,
  B11111,
  B11111
};
byte piec[8]=
{
  B00000,
  B00000,
  B00000,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
};
byte szesc[8]=
{
  B00000,
  B00000,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
};
byte siedem[8]=
{
  B00000,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
};
byte osiem[8]=
{
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
};

LiquidCrystal lcd(rs,en,d4,d5,d6,d7);

void setup() {
  lcd.begin(20,4);

  //tworzenie wlasnych symboli poziomu
  lcd.createChar(0,jeden);
  lcd.createChar(1,dwa);
  lcd.createChar(2,trzy);
  lcd.createChar(3,cztery);
  lcd.createChar(4,piec);
  lcd.createChar(5,szesc);
  lcd.createChar(6,siedem);
  lcd.createChar(7,osiem);

  // 1. Ekran powitalny
  lcd.setCursor(0,0);
  lcd.print("  Tester losowosci");
  lcd.setCursor(0,1);
  lcd.print("  kostki do gry");
  lcd.setCursor(0,2);
  lcd.print("       #123456");
  lcd.setCursor(0,3);
  lcd.print("    Jerzy Batygolski"); 
  delay(2000);
  lcd.clear();
  
  // 2. Odczyt danych z pamieci EEPROM
  
  // odczyt znaku
  high = EEPROM.read(0);
  low = EEPROM.read(1);
  znak = (high<<8) + low;
  if((znak != 1) && (znak != -1)){znak = 1;}

  //odczyt istats[7]
  for(i = 0; i < 7; i++)
  {
    high = EEPROM.read(2*i + 2);
    low = EEPROM.read(2*i + 3);
    istats[i] = (high<<8) + low;
  }

  //odczyt kolumny[7]
  for(i = 0; i < 7; i++)
  {
    high = EEPROM.read(2*i + 16);
    low = EEPROM.read(2*i + 17);
    kolumny[i] = (high<<8) + low;
  }

  // 3. Wyswietlenie poczatkowych danych odczytanych z EEPROM
  
  //wyswietlenie stalych napisow
  lcd.setCursor(0,0);
  lcd.print("1:     4:");
  lcd.setCursor(0,1);
  lcd.print("2:     5:");
  lcd.setCursor(0,2);
  lcd.print("3:     6:");
  lcd.setCursor(0,3);
  lcd.print("Srednia: ");
  lcd.setCursor(14,3);
  lcd.print("123456");

  lcd_aktualizuj(znak, istats, kolumny);
}

void loop() {
  
  // 1. Odczyt z przetwornika A/C
  
  do
  {
    odczytAC = analogRead(A5);
  }while(odczytAC < 50);
  
  delay(10);
  odczytAC = analogRead(A5);

  // 2. Obsluga przyciskow
  
  if(odczytAC > 962)
  {
    // save - zapisz dane w pamieci EEPROM

    // zapis znaku
    EEPROM.write(0, highByte(znak));
    EEPROM.write(1, lowByte(znak));

    //zapis istats[7]
    for(i = 0; i < 7; i++)
    {
      EEPROM.write(2*i + 2, highByte(istats[i]));
      EEPROM.write(2*i + 3, lowByte(istats[i]));
    }

    //zapis kolumny[7]
    for(i = 0; i < 7; i++)
    {
      EEPROM.write(2*i + 16, highByte(kolumny[i]));
      EEPROM.write(2*i + 17, lowByte(kolumny[i]));
    }

    lcd.setCursor(0,3);
    lcd.print("Zapisano");
    delay(1000);
    lcd.setCursor(0,3);
    lcd.print("Srednia: ");
    
  }
  else if(odczytAC > 843)
  {
    // clear - wyczysc pamiec EEPROM
    
    for(i = 0; i < 30; i++)
    {
      EEPROM.write(i,0);
    }
    lcd.setCursor(0,3);
    lcd.print("Skasowano");
    delay(1000);
    lcd.setCursor(0,3);
    lcd.print("Srednia: ");
  }
  else 
  {
    // obsluga przyciskow 1-6 i +/-

    if(odczytAC > 726)
    {
      // +/- - zmien tryb na dodawanie/odejmowanie
      znak*=-1;
    }
    else if(odczytAC > 613)
    {
      // przycisk 6
      istats[6]+=znak;
      if(istats[6] < 0) {istats[6] = 0;}
      else if(istats[6] > 999) {istats[6] = 999;}
    }
    else if(odczytAC > 502)
    {
      //przycisk 5
      istats[5]+=znak;
      if(istats[5] < 0) {istats[5] = 0;}
      else if(istats[5] > 999) {istats[5] = 999;}
    }
     else if(odczytAC > 390)
    {
      //przycisk 4
      istats[4]+=znak;
      if(istats[4] < 0) {istats[4] = 0;}
      else if(istats[4] > 999) {istats[4] = 999;}
    }
     else if(odczytAC > 280)
    {
      //przycisk 3
      istats[3]+=znak;
      if(istats[3] < 0) {istats[3] = 0;}
      else if(istats[3] > 999) {istats[3] = 999;}
    }
     else if(odczytAC > 169)
    {
      //przycisk 2
      istats[2]+=znak;
      if(istats[2] < 0) {istats[2] = 0;}
      else if(istats[2] > 999) {istats[2] = 999;}
    }
     else if(odczytAC > 57)
    {
      //przycisk 1
      istats[1]+=znak;
      if(istats[1] < 0) {istats[1] = 0;}
      else if(istats[1] > 999) {istats[1] = 999;}
    }
    
    // 3. Aktualizacja wyswietlacza
    lcd_aktualizuj(znak, istats, kolumny);  
  }
  
  do
  {
    odczytAC = analogRead(A5);
  }while(odczytAC > 50);
  delay(50);
}

//*****************************************************************************************************

void lcd_aktualizuj(int f_znak, int* f_istats, int* f_kolumny)
{
    int i = 0;
    int j = 0;
    
    //aktualizacja znakow
    if(f_znak == 1)
      {
        lcd.setCursor(2,0);
        lcd.print("+");
        lcd.setCursor(9,0);
        lcd.print("+");
        lcd.setCursor(2,1);
        lcd.print("+");
        lcd.setCursor(9,1);
        lcd.print("+");
        lcd.setCursor(2,2);
        lcd.print("+");
        lcd.setCursor(9,2);
        lcd.print("+");
      }
      else
      {
        lcd.setCursor(2,0);
        lcd.print("-");
        lcd.setCursor(9,0);
        lcd.print("-");
        lcd.setCursor(2,1);
        lcd.print("-");
        lcd.setCursor(9,1);
        lcd.print("-");
        lcd.setCursor(2,2);
        lcd.print("-");
        lcd.setCursor(9,2);
        lcd.print("-");
      }

      //aktualizacja statystyk liczbowych
      
      // liczba jedynek
      lcd.setCursor(3,0);
      lcd.print(f_istats[1]);
      lcd.print(" ");

      // liczba dwojek
      lcd.setCursor(3,1);
      lcd.print(f_istats[2]);
      lcd.print(" ");

      // liczba trojek
      lcd.setCursor(3,2);
      lcd.print(f_istats[3]);
      lcd.print(" ");

      //liczba czworek
      lcd.setCursor(10,0);
      lcd.print(f_istats[4]);
      lcd.print(" ");
   
      //liczba piatek
      lcd.setCursor(10,1);
      lcd.print(f_istats[5]);
      lcd.print(" ");
    
      // liczba szostek  
      lcd.setCursor(10,2);
      lcd.print(f_istats[6]);
      lcd.print(" ");

      //aktualizacja sredniej
      int suma = (1*f_istats[1] + 2*f_istats[2] + 3*f_istats[3] + 4*f_istats[4] + 5*f_istats[5] + 6*f_istats[6]);
      int liczba_rzutow = f_istats[1] + f_istats[2] + f_istats[3] + f_istats[4] + f_istats[5] + f_istats[6];
      float srednia;
      if(liczba_rzutow > 0) {srednia = (float) suma / ((float) liczba_rzutow);}
      else {srednia = 0.00;}
      lcd.setCursor(9,3);
      lcd.print(srednia);

      //aktualizacja wykresu

      //czyszczenie wykresu
      lcd.setCursor(14,0);
      lcd.print("      ");
      lcd.setCursor(14,1);
      lcd.print("      ");
      lcd.setCursor(14,2);
      lcd.print("      ");

      //tworzenie nowego wykresu

      //szukanie maximum
      int maximum = f_istats[1];
      int indeks_max = 1;
      for(i = 2; i < 7; i++)
      {
        if(maximum < f_istats[i])
        {
          maximum = f_istats[i];
          indeks_max = i;
        }
      }

      //aktualizacja tabeli kolumny[7]
      for(i = 1; i < 7; i++)
      {
        f_kolumny[i] = f_istats[i]*24/maximum;
      }
      
      //rysowanie wykresu
      for(i = 1; i < 7; i++)
      {
        j = 0;
        while(f_kolumny[i]>0)
        {
          lcd.setCursor(13+i, 2-j);
          if(f_kolumny[i] == 1)
          {
            lcd.write(byte(0));
            f_kolumny[i] = 0;
          }
          else if(f_kolumny[i] > 7)
          {
            lcd.write(7);
            f_kolumny[i] -= 8;
          }
          else
          {
            lcd.write(f_kolumny[i]-1);
            f_kolumny[i] = 0;
          }
          j++;
        }
      }
}
