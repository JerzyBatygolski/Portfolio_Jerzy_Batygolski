#define L_DIR 4 //kierunek obrotów lewego silnika (0 - przód, 1 - tył)
#define L_PWM 5 //prędkość lewego silnika (0-165)
#define R_PWM 6 //prędkość prawego silnika (0-165)
#define R_DIR 9  //kierunek obrotów prawego silnika (0 - przód, 1 - tył)
#define BUZZER 10 //pin sterujący buzzerem
#define BUTTON 2 //pin oodczytujący stan przycisku
#define trigPin 8 //pin wyzwalający pomiar odległości
#define echoPin 7 //pin do odczytu odległości
#define R_SIDE_SENSOR A0 // prawa krańcówka
#define L_SIDE_SENSOR A1 //lewa krańcówka
#define PWM_MAX 165 //maksymalne wypelnienie sygnalu sterującego prędkością silnika

char bluetoothVal; //zmienna przechowująca odczytany znak
char temp; //zmienna pomocnicza
bool w = 0; //zmienna logiczna określająca czy robot jest na przeszkodzie
int i = 5; //zmienna pomocnicza

//zmienna przechowujące wartości sliderów
int sliderLeft = 60;
int sliderRight = 60;
int sliderRotate = 60;

//zmienne do pomiaru odległosći
long czas = 0;
long dystans = 50;

void setup() {
  Serial.begin(9600);
  
  // konfiguracja pinów od mostka H
  pinMode(L_DIR, OUTPUT);
  pinMode(R_DIR, OUTPUT);
  pinMode(L_PWM, OUTPUT);
  pinMode(R_PWM, OUTPUT);

  //konfiguracja pinów czujników, przycisków itp.
  pinMode(BUZZER, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(L_SIDE_SENSOR, INPUT_PULLUP);
  pinMode(R_SIDE_SENSOR, INPUT_PULLUP);
  digitalWrite(BUZZER, LOW);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  // pomiar odległości co 500 ms
  if(i == 5) 
  { 
    measureDistance();
    i = 1;
  }
  else i++;

  //jeśli robot napotka przeszkodę
  if((digitalRead(L_SIDE_SENSOR) == LOW) || (digitalRead(R_SIDE_SENSOR) == LOW))
  {
    if(w == 0)
    {
      stopMotors();
      digitalWrite(BUZZER, HIGH);
      delay(400);
      digitalWrite(BUZZER, LOW);
      w = 1;
    }
  }

  //jeśli robot wycofał się z przeszkody
  if((digitalRead(L_SIDE_SENSOR) == HIGH) && (digitalRead(R_SIDE_SENSOR) == HIGH) && (w == 1))
  {
    w = 0;
  }
  
  // odczytywanie danych przesłanych z aplikacji
  while(Serial.available())
  {
    bluetoothVal = Serial.read();
    switch(bluetoothVal)
    {
      // obsługa sliderów

      // slider prędkości lewego koła
      case 'x':
      sliderLeft = Serial.parseInt();
      temp = Serial.read();
      if(sliderLeft < 0 || sliderLeft > 100){sliderLeft = 0;}
      break;

      // slider prędkości prawego koła
      case 'y':
      sliderRight = Serial.parseInt();
      temp = Serial.read();
      if(sliderRight < 0 || sliderRight > 100){sliderRight = 0;}
      break;

      // slider prędkości obrotów
      case 'z':
      sliderRotate = Serial.parseInt();
      temp = Serial.read();
      if(sliderRotate < 0 || sliderRotate > 100){sliderRotate = 0;}
      break;

      // obsługa przycisków ruchu

      // przycisk jazdy w przód
      case 'f':
      if(w == 0)
      {
        leftMotor(sliderLeft);
        rightMotor(sliderRight);
      }
      break;
      
      // przycisk jazdy w tył
      case 'b': 
      leftMotor(-sliderLeft);
      rightMotor(-sliderRight);
      break;

      // przycisk obrotu wg zegara
      case 'r':
      if(w == 0)
      {
        leftMotor(-sliderRotate);
        rightMotor(sliderRotate);
      }
      break;

      //przycisk obrotu przeciwnie do zegara
      case 'l':
      if(w == 0)
      {
        leftMotor(sliderRotate);
        rightMotor(-sliderRotate);
      }
      break;

      //puszczenie dowolnego przycisku
      case 's':
      stopMotors();
    }
  }
  delay(100);
}

void leftMotor(int v)
{
  if(v > 0)
  {
    v = map(v, 0, 100, 0, PWM_MAX);
    digitalWrite(L_DIR, 0);
    analogWrite(L_PWM, v);
  }
  else
  {
    v = abs(v);
    v = map(v, 0, 100, 0, PWM_MAX);
    digitalWrite(L_DIR, 1);
    analogWrite(L_PWM, v);
  }
}

void rightMotor(int v)
{
  if(v > 0)
  {
    v = map(v, 0, 100, 0, PWM_MAX);
    digitalWrite(R_DIR, 0);
    analogWrite(R_PWM, v);
  }
  else
  {
    v = abs(v);
    v = map(v, 0, 100, 0, PWM_MAX);
    digitalWrite(R_DIR, 1);
    analogWrite(R_PWM, v);
  }
}

void stopMotors()
{
  analogWrite(L_PWM, 0);
  analogWrite(R_PWM, 0);
}

void measureDistance()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  czas = pulseIn(echoPin, HIGH);
  dystans = czas/58;
  if(dystans < 2) dystans = 2;
  else if(dystans > 200) dystans = 200;
  Serial.print((int)dystans);
}
