/***********************************************************************************
Extensor de Memória RAM para Arduno UNO
Código baseado no exemplo de: J. B. Gallaher 07/09/2016

Um simples programa para usar um chip SRAM serial para expandir a memória de um Arduino Uno.
O 23LC1024 usa SPI para transferir informação e comandos entre o Uno e a Memória do chip.
***********************************************************************************/

#include <SPI.h>

/************SRAM opcodes: Comandos para 23LC1024 ******************/
#define RDMR 5 // Lê o modo registrador
#define WRMR 1 // Escreve no Modo Registrador
#define READ 3 // Lê o comando
#define WRITE 2 // Escreve o comando
#define RSTIO 0xFF // Reseta memória para SPI
#define ByteMode 0x00 // Byte mode (leitura/escrita de um byte)
#define Sequential 0x40 // Sequential mode (leitura/escrita nos blocos da memória)
#define CS 10 // Chip Select Line para Uno

/******************* Funções **************************/
void SetMode(char Mode);
byte ReadByte(uint32_t address);
void WriteByte(uint32_t address, byte data_byte);
void WriteArray(uint32_t address, byte *data, uint16_t big);
void ReadArray(uint32_t address, byte *data, uint16_t big);

/******************* Variáveis Globais *********************/

byte x[20] = {"abcdefghijklmnopqrs"}; // Array para escrever algo
byte read_data[20]; // Array para segurar a informação lida na memória
byte i = 0; // contador
/******* Configure o código para definir variáveis e iniciar as interfaces seriais SCI e SPI *****/
void setup(void) {
  uint32_t address = 0; //  crie uma variável de 32 bits para armazenar o endereço
  byte value; // criar variável para reter o valor dos dados lidos
  byte data; //  criar variável para armazenar o valor dos dados enviados
  pinMode(CS, OUTPUT); // Fazer com que pin 10 esteja em modo saida
  Serial.begin(9600); // Monitor serial
  SPI.begin(); // Começa a comunicação com o chip
  /********** Escreva um único byte de cada vez na memória *******************/
  Serial.println("Bytes Individuais: ");
  SetMode(ByteMode); // configurado para enviar / receber um único byte de dados
  data = 0; // inicialize a variável de dados
  for(i = 0; i <=5; i++){ // Vamos escrever 5 bytes individuais na memória
    address = i; // use o contador de loop como o endereço
    WriteByte(address, data); // agora escreva os dados nesse endereço
    data+=2; // incrementar os dados em 2
  }

  /********* Leia um único byte de cada vez da memória *********************/
  Serial.println("lendo cada byte de dados individualmente: ");
  SetMode(ByteMode); //configurado para enviar / receber um único byte de dados
  
  for(i = 0; i <=5; i++){ // comece no local de memória 0 e termine em 5
    address = i; // use o contador de loop como endereço de memória
    value = ReadByte(address); // lê um byte de dados nessa localização de memória
    Serial.println(value); 
  }

  /************ Escrever uma sequência de bytes de um array *******************/
  Serial.println("\nEscrevendo array usando Sequential: ");
  SetMode(Sequential); // configurado para enviar / receber vários bytes de dados
  WriteArray(0, x, sizeof(x)); // Use a matriz de caracteres definida em x acima
  // grava na memória começando no endereço 0

  /************ Read a Sequence of Bytes from Memory into an Array **********/
  Serial.println("Reading array using sequential: ");
  SetMode(Sequential); // set to send/receive multiple bytes of data
  ReadArray(0, read_data, sizeof(read_data)); // Read from memory into empty array read_data
  // starting at memory address 0
  for(i=0; i<sizeof(read_data); i++) // print the array just read using a for loop.
    Serial.println((char)read_data[i]); // We need to cast it as a char
    // to make it print as a character
  }
  void loop() { // we have nothing to do in the loop
  }
  /* Functions to Set the Mode, and Read and Write Data to the Memory Chip ***********/
  /* Set up the memory chip to either single byte or sequence of bytes mode **********/
  void SetMode(char Mode){ 
    // Select for single or multiple byte transfer
    digitalWrite(CS, LOW); // set SPI slave select LOW;
    SPI.transfer(WRMR); // command to write to mode register
    SPI.transfer(Mode); // set for sequential mode
    digitalWrite(CS, HIGH); // release chip select to finish command
  }
  /************ Byte transfer functions ***************************/
  byte ReadByte(uint32_t address) {
    char read_byte;
    digitalWrite(CS, LOW); // set SPI slave select LOW;
    SPI.transfer(READ); // send READ command to memory chip
    SPI.transfer((byte)(address >> 16)); // send high byte of address
    SPI.transfer((byte)(address >> 8)); // send middle byte of address
    SPI.transfer((byte)address); // send low byte of address
    read_byte = SPI.transfer(0x00); // read the byte at that address
    digitalWrite(CS, HIGH);; // set SPI slave select HIGH;
    return read_byte; // send data back to the calling function
  }
  void WriteByte(uint32_t address, byte data_byte) {
    digitalWrite(CS, LOW); // set SPI slave select LOW;
    SPI.transfer(WRITE); // send WRITE command to the memory chip
    SPI.transfer((byte)(address >> 16)); // send high byte of address
    SPI.transfer((byte)(address >> 8)); // send middle byte of address
    SPI.transfer((byte)address); // send low byte of address
    SPI.transfer(data_byte); // write the data to the memory location
    digitalWrite(CS, HIGH); //set SPI slave select HIGH
  }
  /*********** Sequential data transfer functions using Arrays ************************/
  void WriteArray(uint32_t address, byte *data, uint16_t big){
    uint16_t i = 0; // loop counter
    digitalWrite(CS, LOW); // start new command sequence
    SPI.transfer(WRITE); // send WRITE command
    SPI.transfer((byte)(address >> 16)); // send high byte of address
    SPI.transfer((byte)(address >> 8)); // send middle byte of address
    SPI.transfer((byte)address); // send low byte of address
    SPI.transfer(data, big); // transfer an array of data => needs array name & size digitalWrite(CS, HIGH); // set SPI slave select HIGH
  }
  void ReadArray(uint32_t address, byte *data, uint16_t big){
    uint16_t i = 0; // loop counter
    digitalWrite(CS, LOW); // start new command sequence
    SPI.transfer(READ); // send READ command
    SPI.transfer((byte)(address >> 16)); // send high byte of address
    SPI.transfer((byte)(address >> 8)); // send middle byte of address
    SPI.transfer((byte)address); // send low byte of address
    for(i=0; i<big; i++){
    data[i] = SPI.transfer(0x00); // Lê a informação
  }
  digitalWrite(CS, HIGH);
}
