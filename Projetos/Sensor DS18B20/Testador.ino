#include <LiquidCrystal.h>
#include <OneWire.h>

const int rs = 12, en = 11, d4 = 6, d5 = 5, d6 = 4, d7 = 3;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int numRows = 2;
const int numCols = 16;

OneWire  ds(2);  // Pino do Sinal do sensor

/*
    lcd.setCursor(0, 0); // top left
    lcd.setCursor(15, 0); // top right
    lcd.setCursor(0, 1); // bottom left
    lcd.setCursor(15, 1); // bottom right
*/


void setup(void) {
  Serial.begin(9600);
  lcd.begin(numCols, numRows);
}

void loop(void) {
    
  byte i;
  byte present = 0;
  byte type_s;
  byte data[12];
  byte addr[8];
  float celsius;


  ds.reset();
  ds.select(addr);
  ds.write(0x44, 1);        // start conversion, with parasite power on at the end

  delay(1000);     // maybe 750ms is enough, maybe not
  // we might do a ds.depower() here, but the reset will take care of it.

  present = ds.reset();
  ds.select(addr);
  ds.write(0xBE);         // Read Scratchpad

  Serial.print("  Data = ");
  Serial.print(present, HEX);
  Serial.print(" ");
  for ( i = 0; i < 9; i++) {           // we need 9 bytes
    data[i] = ds.read();
    Serial.print(data[i], HEX);
    Serial.print(" ");
  }
  
  int16_t raw = (data[1] << 8) | data[0];
  if (type_s) {
    raw = raw << 3; // 9 bit resolution default
    if (data[7] == 0x10) {
      // "count remain" gives full 12 bit resolution
      raw = (raw & 0xFFF0) + 12 - data[6];
    }
  } else {
    byte cfg = (data[4] & 0x60);
    // at lower res, the low bits are undefined, so let's zero them
    if (cfg == 0x00) raw = raw & ~7;  // 9 bit resolution, 93.75 ms
    else if (cfg == 0x20) raw = raw & ~3; // 10 bit res, 187.5 ms
    else if (cfg == 0x40) raw = raw & ~1; // 11 bit res, 375 ms
    //// default is 12 bit resolution, 750 ms conversion time
  }
  celsius = (float)raw / 16.0;

    lcd.clear();

    
  if ( !ds.search(addr)) {
    ds.reset_search();
    lcd.setCursor(9,0);
    if(celsius <= 0 || celsius >= 50) {
      for(int positionCounter = 0; positionCounter <40; positionCounter ++) {
      lcd.setCursor(1,0);
      lcd.scrollDisplayLeft();  //Essa é a função que faz as letras se deslocarem
      lcd.print("Insira a Sonda ou verifique a Crimpagem");
      delay(250);
        }
      }
    else {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("sonda OK");
    lcd.setCursor(10,0);
    lcd.print(celsius);
    lcd.setCursor(14,0);
    lcd.print("C");
    lcd.setCursor(3,1);
    lcd.print("SN:");
    lcd.setCursor(7,1);
    for( i = 4; i > 0; i--) {
    lcd.print(addr[i], HEX);
    }
    }
    delay(1000);
    return;
  } 
  
/*
    lcd.print(addr[3], HEX);
    lcd.setCursor(7,1);
    lcd.print(addr[2], HEX);
    lcd.setCursor(8,1);
    lcd.print(addr[1], HEX);
    */


  // the first ROM byte indicates which chip
  switch (addr[0]) {
    case 0x10:
      Serial.println("  Chip = DS18S20");  // or old DS1820
      type_s = 1;
      break;
    case 0x28:
      Serial.println("  Chip = DS18B20");
      type_s = 0;
      break;
    case 0x22:
      Serial.println("  Chip = DS1822");
      type_s = 0;
      break;
    default:
      Serial.println("Device is not a DS18x20 family device.");
      return;
  }


  
  }
/*
  // Convert the data to actual temperature
  // because the result is a 16 bit signed integer, it should
  // be stored to an "int16_t" type, which is always 16 bits
  // even when compiled on a 32 bit processor.
  int16_t raw = (data[1] << 8) | data[0];
  if (type_s) {
    raw = raw << 3; // 9 bit resolution default
    if (data[7] == 0x10) {
      // "count remain" gives full 12 bit resolution
      raw = (raw & 0xFFF0) + 12 - data[6];
    }
  } else {
    byte cfg = (data[4] & 0x60);
    // at lower res, the low bits are undefined, so let's zero them
    if (cfg == 0x00) raw = raw & ~7;  // 9 bit resolution, 93.75 ms
    else if (cfg == 0x20) raw = raw & ~3; // 10 bit res, 187.5 ms
    else if (cfg == 0x40) raw = raw & ~1; // 11 bit res, 375 ms
    //// default is 12 bit resolution, 750 ms conversion time
  }
  celsius = (float)raw / 16.0;
    Serial.print("  Temperatura = ");
  Serial.print(celsius);
  }*/
