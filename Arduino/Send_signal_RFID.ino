#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN  9    //Pin 9 para el reset del RC522
#define SS_PIN  5   //Pin 10 para el SS (SDA) del RC522 cambio por el 10
MFRC522 mfrc522(SS_PIN, RST_PIN); ///Creamos el objeto para el RC522

int digPin = 10; // pin digital 10


void setup() {
  Serial.begin(9600); //Iniciamos La comunicacion serial
  SPI.begin();        //Iniciamos el Bus SPI
  mfrc522.PCD_Init(); // Iniciamos el MFRC522
  Serial.println("Control de acceso:");

}

//96 29 E0 A0 Llaverito   10%
//46 EC D9 A0 Llaverito   20%

//6C 70 8C 2B Card        30%
//B2 3A D5 BD Card        40%

byte Numero_RFID[4]; //almacenará el código del Tag leído
byte Tarjeta1[4]= {0x96, 0x29, 0xE0, 0xA0} ; //código de tarjeta 1
byte Tarjeta2[4]= {0x46, 0xEC, 0xD9, 0xA0} ; //código de tarjeta 2
byte Tarjeta3[4]= {0x6C, 0x70, 0x8C, 0x2B} ; //código de tarjeta 3
byte Tarjeta4[4]= {0xB2, 0x3A, 0xD5, 0xBD} ; //código de tarjeta 4
void loop() {
  // Revisamos si hay nuevas tarjetas  presentes
  if ( mfrc522.PICC_IsNewCardPresent())
        {
      //Seleccionamos una tarjeta
            if ( mfrc522.PICC_ReadCardSerial())
            {
                  // Enviamos serialemente su UID
                  Serial.print(F("Card UID:"));
                  for (byte i = 0; i < mfrc522.uid.size; i++) {
                          Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
                          Serial.print(mfrc522.uid.uidByte[i], HEX);
                          Numero_RFID[i]=mfrc522.uid.uidByte[i];
                  }
                  Serial.print("     ");
                  /*
Tabla de entradas
0 - > 1500
150 -> 1200
222 -> 1777
254 -> 2040
*/
                  //comparamos los UID para determinar si es uno de nuestros usuarios
                       if(compareArray(Numero_RFID,Tarjeta1))
                    analogWrite(digPin,254);
                  else if(compareArray(Numero_RFID,Tarjeta2))
                    analogWrite(digPin,150);
                  else if(compareArray(Numero_RFID,Tarjeta3))
                    analogWrite(digPin,222);
                  else if(compareArray(Numero_RFID,Tarjeta4))
                    analogWrite(digPin,0);
                  else
                    Serial.println("Acceso denegado...");
                  // Terminamos la lectura de la tarjeta tarjeta  actual
                  mfrc522.PICC_HaltA();
            }
  }

}

//Función para comparar dos vectores
 boolean compareArray(byte array1[],byte array2[])
{
  if(array1[0] != array2[0])return(false);
  if(array1[1] != array2[1])return(false);
  if(array1[2] != array2[2])return(false);
  if(array1[3] != array2[3])return(false);
  return(true);
}
