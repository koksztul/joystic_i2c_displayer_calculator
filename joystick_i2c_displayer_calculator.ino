const int SW_pin = 2; // digital pin connected to switch output
const int X_pin = 0; // analog pin connected to X output
const int Y_pin = 1; // analog pin connected to Y output
int var =0;

#include <Wire.h>   // standardowa biblioteka Arduino
#include <LiquidCrystal_I2C.h> // dolaczenie pobranej biblioteki I2C dla LCD

String result;

const char * expressionToParse = "3*2+4*1+(4+9)*6";

char peek()
{
    return *expressionToParse;
}

char get()
{
    return *expressionToParse++;
}

int expression();

int number()
{
    int result = get() - '0';
    while (peek() >= '0' && peek() <= '9')
    {
        result = 10*result + get() - '0';
    }
    return result;
}

int factor()
{
    if (peek() >= '0' && peek() <= '9')
        return number();
    else if (peek() == '(')
    {
        get(); // '('
        int result = expression();
        get(); // ')'
        return result;
    }
    else if (peek() == '-')
    {
        get();
        return -factor();
    }
    return 0; // error
}

int term()
{
    int result = factor();
    while (peek() == '*' || peek() == '/')
        if (get() == '*')
            result *= factor();
        else
            result /= factor();
    return result;
}

int expression()
{
    int result = term();
    while (peek() == '+' || peek() == '-')
        if (get() == '+')
            result += term();
        else
            result -= term();
    return result;
}



 
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Ustawienie adresu ukladu na 0x27
 
 
void setup()  
{
  pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, HIGH);
  Serial.begin(115200);
 
  lcd.begin(16,2);   // Inicjalizacja LCD 2x16
 
 lcd.backlight(); // zalaczenie podwietlenia
 lcd.setCursor(0,0); // Ustawienie kursora w pozycji 0,0 (pierwszy wiersz, pierwsza kolumna)
 lcd.print("Kakulator,Autor:");
 lcd.setCursor(0,1); //Ustawienie kursora w pozycji 0,0 (drugi wiersz, pierwsza kolumna)
 lcd.print("Kamil Oksztulski");
 delay(2000);
 lcd.setCursor(0,1); 
 lcd.print("                "); 
 
}
 
void loop()
{
  Serial.print("Switch:  ");
  Serial.print(digitalRead(SW_pin));
  Serial.print("\n");
  Serial.print("X-axis XX: ");
  Serial.print(analogRead(X_pin));
  Serial.print("\n");
  Serial.print("Y-axis: ");
  Serial.println(analogRead(Y_pin));
  Serial.print("\n\n");
  delay(200);
  
  if(analogRead(X_pin)<100)
  { var--; }
  if(analogRead(X_pin)>900)
  { var++; }
  if(var<0)
  { var = 13; }
  if(var >13)
  { var = 0; }
  if(analogRead(Y_pin) <100)
  {
    lcd.setCursor(0,1); 
    lcd.print("              "); 
    expressionToParse = result.c_str();
    int result = expression();
    lcd.setCursor(0,1);
    lcd.print(String(result));
  }

  if(analogRead(Y_pin)>900)
  { 
    result = "";
    lcd.setCursor(0,1); 
    lcd.print("              "); 
  }
  
  switch (var) {
  case 0:
         lcd.setCursor(0,0); 
         lcd.print("<0>123456789+-*/");
         lcd.setCursor(0,1);
         if(digitalRead(SW_pin) == 0 && result.charAt(result.length()-1) != '-' && result.charAt(result.length()-1) != '*' && result.charAt(result.length()-1) != '/'&& result.charAt(result.length()-1) != '+' && result.length() > 0)
         {
            lcd.print(result += "0");
         }
         break;
  case 1:
         lcd.setCursor(0,0);
         lcd.print("0<1>23456789+-*/");
         lcd.setCursor(0,1);
         if(digitalRead(SW_pin) == 0)
         {
            lcd.print(result += "1");
         }
    break;
  case 2:
         lcd.setCursor(0,0);
         lcd.print("01<2>3456789+-*/");
         lcd.setCursor(0,1);
         if(digitalRead(SW_pin) == 0)
         {
            lcd.print(result += "2");
         }
    break;
  case 3:
         lcd.setCursor(0,0);
         lcd.print("012<3>456789+-*/");
         lcd.setCursor(0,1);
         if(digitalRead(SW_pin) == 0)
         {
            lcd.print(result += "3");
         }
    break;
  case 4:
         lcd.setCursor(0,0);
         lcd.print("0123<4>56789+-*/");
         lcd.setCursor(0,1);
         if(digitalRead(SW_pin) == 0)
         {
            lcd.print(result += "4");
         }
    break;
  case 5:
         lcd.setCursor(0,0); 
         lcd.print("01234<5>6789+-*/");
         lcd.setCursor(0,1);
         if(digitalRead(SW_pin) == 0)
         {
            lcd.print(result += "5");
         }
    break;
  case 6:
         lcd.setCursor(0,0);
         lcd.print("012345<6>789+-*/");
         lcd.setCursor(0,1);
         if(digitalRead(SW_pin) == 0)
         {
            lcd.print(result += "6");
         }
    break;
  case 7:
         lcd.setCursor(0,0); 
         lcd.print("0123456<7>89+-*/");
         lcd.setCursor(0,1);
         if(digitalRead(SW_pin) == 0)
         {
            lcd.print(result += "7");
         }
    break;
  case 8:
         lcd.setCursor(0,0);
         lcd.print("01234567<8>9+-*/");
         lcd.setCursor(0,1);
         if(digitalRead(SW_pin) == 0)
         {
            lcd.print(result += "8");
         }
    break;
  case 9:
         lcd.setCursor(0,0);
         lcd.print("012345678<9>+-*/");
         lcd.setCursor(0,1);
         if(digitalRead(SW_pin) == 0)
         {
            lcd.print(result += "9");
         }
    break;
  case 10:
         lcd.setCursor(0,0);
         lcd.print("0123456789<+>-*/");
         lcd.setCursor(0,1);
         if(digitalRead(SW_pin) == 0 && result.charAt(result.length()-1) != '-' && result.charAt(result.length()-1) != '*' && result.charAt(result.length()-1) != '/'&& result.charAt(result.length()-1) != '+' && result.length() > 0)
         {
            lcd.print(result += "+");
         }
    break;
  case 11:
         lcd.setCursor(0,0);
         lcd.print("0123456789+<->*/");
         lcd.setCursor(0,1);
         if(digitalRead(SW_pin) == 0 && result.charAt(result.length()-1) != '-' && result.charAt(result.length()-1) != '*' && result.charAt(result.length()-1) != '/'&& result.charAt(result.length()-1) != '+' && result.length() > 0)
         {
            lcd.print(result += "-");
         }
    break;
  case 12:
         lcd.setCursor(0,0); 
         lcd.print("0123456789+-<*>/");
         lcd.setCursor(0,1);
         if(digitalRead(SW_pin) == 0 && result.charAt(result.length()-1) != '-' && result.charAt(result.length()-1) != '*' && result.charAt(result.length()-1) != '/'&& result.charAt(result.length()-1) != '+' && result.length() > 0)
         {
            lcd.print(result += "*");
         }
    break;
  case 13:
         lcd.setCursor(0,0);
         lcd.print("0123456789+-*</>");
         lcd.setCursor(0,1);
         if(digitalRead(SW_pin) == 0 && result.charAt(result.length()-1) != '-' && result.charAt(result.length()-1) != '*' && result.charAt(result.length()-1) != '/'&& result.charAt(result.length()-1) != '+' && result.length() > 0)
         {
            lcd.print(result += "/");
         }
    break;
}
}
