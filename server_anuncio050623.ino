//Server este seria el lado del anuncio

#include <SPI.h>
#include<RH_NRF24.h>

RH_NRF24 trans;

void setup() {
  Serial.begin(9600);
  if(!trans.init())
    Serial.println("fallo de inicializacion");
  if(!trans.setChannel(2))
    Serial.println("fallo en establecer canal");
  if(!trans.setRF(RH_NRF24::DataRate250kbps, RH_NRF24::TransmitPower0dBm))
    Serial.println("fallo en opciones RF");

    Serial.println("Servidor iniciado");
    

}

void loop() {
  if(trans.available()){
    uint8_t buf[RH_NRF24_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);
    if(trans.recv(buf, &len)){
      Serial.print("Recibido: ");
      Serial.println((char*)buf);

      uint8_t data[] = "Hola de regreso";
      trans.send(data, sizeof(data));
      trans.waitPacketSent();
      Serial.println("Respondiendo");  
    }
    else{
      Serial.println("Fallo en recepcion");
    }
  }
}
