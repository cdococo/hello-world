// file receiver.cpp
#include &amp;lt;cstdlib&amp;gt;
#include &amp;lt;iostream&amp;gt;
#include "librf24/RF24.h"
#include "payload.h"
using namespace std;
 
//
// Hardware configuration
//
RF24 radio("/dev/spidev0.0", 8000000 , 25);  //spi device, speed and CSN,only CSN is NEEDED in RPI
const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };
 
Payload payload = Payload();
 
//
// Setup
//
void setup(void) {
  radio.begin();
  radio.setRetries(15, 15);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_MAX);
  radio.setPayloadSize(sizeof(payload));
  radio.openWritingPipe(pipes[1]);
  radio.openReadingPipe(1, pipes[0]);
  radio.startListening();
  radio.printDetails();
}
 
//
// Loop
//
void loop(void) {
  if (radio.available()) {
    radio.read(&amp;amp;payload, sizeof(payload));
    printf("packet %d %d %d %d %d \n", payload.data.meteo.temperature, payload.data.meteo.humidity, payload.data.meteo.luminosity, payload.data.meteo.altitude, payload.data.meteo.pressure);
  }
}
 
int main(int argc, char** argv){
        setup();
        while(1)
                loop();
 
        return 0;
}