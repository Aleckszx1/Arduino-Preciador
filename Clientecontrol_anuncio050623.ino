//Control, este lado va fuera del anuncio

#include <SPI.h>
#include<RH_NRF24.h>

RH_NRF24 ctrl;

void setup() {
  Serial.begin(9600);
  if(!ctrl.init())
    Serial.println("fallo de inicializacion");
  if(!ctrl.setChannel(2))
    Serial.println("fallo en establecer canal");
  if(!ctrl.setRF(RH_NRF24::DataRate250kbps, RH_NRF24::TransmitPower0dBm))
    Serial.println("fallo en opciones RF");
}

void loop() {
  Serial.println("Enviando mensaje al anuncio");
  uint8_t data[] = "Mensaje de prueba";
  ctrl.send(data, sizeof(data));
  ctrl.waitPacketSent();
  
  uint8_t buf[RH_NRF24_MAX_MESSAGE_LEN];
  uint8_t len = sizeof(buf);

  if(ctrl.available()){
    if(ctrl.recv(buf, &len)){
      Serial.print("Recibido: ");
      Serial.println((char*)buf);
    }
    else{
      Serial.println("Fallo en recepcion");
    }
  }
  delay(1000);
}
