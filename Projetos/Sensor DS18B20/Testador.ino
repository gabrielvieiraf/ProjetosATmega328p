#include <LiquidCrystal.h>
#include <OneWire.h>

const int rs = 12, en = 11, d4 = 6, d5 = 5, d6 = 4, d7 = 3;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int numRows = 2;
const int numCols = 16;

OneWire  ds(2);  // Pino do Sinal do sensor

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
  ds.write(0x44, 1);        // Começa conversão com o sensor em modo parasita

  delay(1000);

  present = ds.reset();
  ds.select(addr);
  ds.write(0xBE);         // Lê Scratchpad

  for ( i = 0; i < 9; i++) {           // Precisamos de 9 bytes
    data[i] = ds.read();
  }

  int16_t raw = (data[1] << 8) | data[0];
  if (type_s) {
    raw = raw << 3; // 9 bit como padrão
    if (data[7] == 0x10) {
      // "count remain" lhe dá resolução de 12 bit
      raw = (raw & 0xFFF0) + 12 - data[6];
    }
  } else {
    byte cfg = (data[4] & 0x60);
    if (cfg == 0x00) raw = raw & ~7;  // 9 bit res, 93.75 ms
    else if (cfg == 0x20) raw = raw & ~3; // 10 bit res, 187.5 ms
    else if (cfg == 0x40) raw = raw & ~1; // 11 bit res, 375 ms
    //// Por padrão, utilizamos a resolução de 12 bit, tempo de conversão de 750 ms
  }
  
  celsius = (float)raw / 16.0; //Conversão da leitura para graus celsius

  lcd.clear();

  if ( !ds.search(addr)) {
    ds.reset_search();
    lcd.setCursor(9, 0);
    if (celsius <= 0 || celsius >= 50) {
      for (int positionCounter = 0; positionCounter < 40; positionCounter ++) {
        lcd.setCursor(1, 0);
        lcd.scrollDisplayLeft();  //Essa é a função que faz as letras se deslocarem
        lcd.print("Insira a Sonda ou verifique a Crimpagem");
        delay(250);
      }
    }
    else {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("sonda OK");
      lcd.setCursor(10, 0);
      lcd.print(celsius);
      lcd.setCursor(14, 0);
      lcd.print("C");
      lcd.setCursor(3, 1);
      lcd.print("SN:");
      lcd.setCursor(7, 1);
      for ( i = 4; i > 0; i--) {
        lcd.print(addr[i], HEX);
      }
    }
    delay(1000);
    return;
  }

  // O primeiro byte da ROM indica o modelo do chip, apenas para título de curiosidade.
  switch (addr[0]) {
    case 0x10:
      Serial.println("  Chip = DS18S20");
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
      Serial.println("O Dispositivo não pertence à familia DS18x20.");
      return;
  }
}
