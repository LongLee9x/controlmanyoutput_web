#include <WiFi.h>
#include <DNSServer.h>
#include <WebServer.h>
#include <WiFiManager.h>         // https://github.com/tzapu/WiFiManager

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Auxiliar variables to store the current output state
String outputBomState = "off";
String outputDenState = "off";
String outputQuatState = "off";
String outputPhanBonState = "off";
String outputMoMaiCheState = "off";
String outputDongMaiCheState = "off";

String outputMoMaiCheState1 = "off";

int ledState = LOW;        
int buttonState;      
int lastButtonState = HIGH; 
int lastButtonState1 = HIGH;   
unsigned long lastDebounceTime = 0; 
unsigned long debounceDelay = 50;  

// Assign output variables to GPIO pins
const int outputBom = 15;
const int outputDen = 13;
const int outputQuat = 12;
const int outputPhanBon = 14;
const int outputMoMaiChe = 2;
const int outputDongMaiChe = 0;
const int buttonBom = 4;
const int buttonDen = 5;
const int buttonQuat = 16;

//// Variables will change:
//int ledState = LOW;        
//int buttonState;      
//int lastButtonState = LOW;   
//unsigned long lastDebounceTime = 0; 
//unsigned long debounceDelay = 50;  
        boolean a =false;
void setup() {
  Serial.begin(115200);
  // Initialize the output variables as outputs
  pinMode(outputBom, OUTPUT);
  pinMode(outputDen, OUTPUT);
  pinMode(outputQuat, OUTPUT);
  pinMode(outputPhanBon, OUTPUT);
  pinMode(outputMoMaiChe, OUTPUT);
  pinMode(outputDongMaiChe, OUTPUT);
  pinMode(buttonBom, INPUT_PULLUP);
  // Set outputs to LOW
  digitalWrite(outputBom, HIGH);
  digitalWrite(outputDen, HIGH);
  digitalWrite(outputQuat, HIGH);
  digitalWrite(outputPhanBon, HIGH);
  digitalWrite(outputMoMaiChe, LOW);
  digitalWrite(outputDongMaiChe, LOW);

  // WiFiManager
  // Local intialization. Once its business is done, there is no need to keep it around
  WiFiManager wifiManager;
  
  // Uncomment and run it once, if you want to erase all the stored information
  //wifiManager.resetSettings();
  
  // set custom ip for portal
  //wifiManager.setAPConfig(IPAddress(10,0,1,1), IPAddress(10,0,1,1), IPAddress(255,255,255,0));

  // fetches ssid and pass from eeprom and tries to connect
  // if it does not connect it starts an access point with the specified name
  // here  "AutoConnectAP"
  // and goes into a blocking loop awaiting configuration
  wifiManager.autoConnect("AutoConnectAP");
  // or use this for auto generated name ESP + ChipID
  //wifiManager.autoConnect();
  
  // if you get here you have connected to the WiFi
  Serial.println("Connected.");
  
  server.begin();
}

void loop(){
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      Serial.println("New Client.1"); 
      if (digitalRead(buttonBom) ==0) { //nếu khác trạng thái của nhau
        Serial.println("Client disconnected.=============================");
        a=!a;
      } 
      if(a){
        outputMoMaiCheState = "on";
        Serial.println("Client disconnected.-------------------------------");
        //web
        digitalWrite(outputMoMaiChe, HIGH);
      }
      if(!a){
        outputMoMaiCheState = "off";
      digitalWrite(outputMoMaiChe, LOW);
      }  
      if (client.available()) {             // if there's bytes to read from the client,
        Serial.println("New Client.2");   
        
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == 'n'||a) {                    // if the byte is a newline character  
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0||a) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // turns the GPIOs on and off
            if (header.indexOf("GET  
              outputBomState = "on";
              digitalWrite(outputBom, LOW);
            } else if (header.indexOf("GET /15/off") >= 0) {
              Serial.println("GPIO Bom off");
              outputBomState = "off";
              digitalWrite(outputBom, HIGH);
            } else if (header.indexOf("GET /13/on") >= 0) {
              Serial.println("GPIO Den on");
              outputDenState = "on";
              digitalWrite(outputDen, LOW);
            } else if (header.indexOf("GET /13/off") >= 0) {
              Serial.println("GPIO Den off");
              outputDenState = "off";
              digitalWrite(outputDen, HIGH);
            }else if (header.indexOf("GET /12/on") >= 0) {
              Serial.println("GPIO Den on");
              outputQuatState = "on";
              digitalWrite(outputQuat, LOW);
            } else if (header.indexOf("GET /12/off") >= 0) {
              Serial.println("GPIO Quat off");
              outputQuatState = "off";
              digitalWrite(outputQuat, HIGH);
            }else if (header.indexOf("GET /14/on") >= 0) {
              Serial.println("GPIO Quat on");
              outputPhanBonState = "on";
              digitalWrite(outputPhanBon, LOW);
            } else if (header.indexOf("GET /14/off") >= 0) {
              Serial.println("GPIO PhanBon off");
              outputPhanBonState = "off";
              digitalWrite(outputPhanBon, HIGH);
            }
            if (header.indexOf("GET /2/on") >= 0||a) {
              Serial.println("GPIO MoMaiChe on");
              outputMoMaiCheState = "on";
              digitalWrite(outputMoMaiChe, HIGH);
            } else if (header.indexOf("GET /2/off") >= 0) {
              Serial.println("GPIO MoMaiChe off");
              outputMoMaiCheState = "off";
              digitalWrite(outputMoMaiChe, LOW);
            }else if (header.indexOf("GET /0/on") >= 0) {
              Serial.println("GPIO DongMaiChe on");
              outputDongMaiCheState = "on";
              digitalWrite(outputDongMaiChe, HIGH);
            } else if (header.indexOf("GET /0/off") >= 0) {
              Serial.println("GPIO DongMaiChe off");
              outputDongMaiCheState = "off";
              digitalWrite(outputDongMaiChe, LOW);
            }
            
            
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #195B6A; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #77878A;}</style></head>");
            
            // Web Page Heading
            client.println("<body><h1>Cham soc cay trong</h1>");
            client.println("<div>");
            client.println("<div style='display: flex;  justify-content: center;  align-items: center;'>");
            client.println("<div style='margin: 0 30px; width: 210px'>");
            // Display current state, and ON/OFF buttons for GPIO 15  
            client.println("<p>Trang thai Bom " + outputBomState + "</p>");
            // If the outputBomState is off, it displays the ON button       
            if (outputBomState=="off") {
              client.println("<p><a href=\"/15/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/15/off\"><button class=\"button button2\">OFF</button></a></p>");
            } 
            client.println("</div>");
               
            client.println("<div style='margin: 0 30px; width: 210px'>");
            // Display current state, and ON/OFF buttons for GPIO 13  
            client.println("<p>Trang thai Den " + outputDenState + "</p>");
            // If the outputDenState is off, it displays the ON button       
            if (outputDenState=="off") {
              client.println("<p><a href=\"/13/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/13/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            client.println("</div>");
            client.println("</div>");
            
            client.println("<div style='display: flex;  justify-content: center;  align-items: center;'>");
            client.println("<div style='margin: 0 30px; width: 210px'>");
            // Display current state, and ON/OFF buttons for GPIO 12  
            client.println("<p>Trang thai Quat " + outputQuatState + "</p>");
            // If the outputQuatState is off, it displays the ON button       
            if (outputQuatState=="off") {
              client.println("<p><a href=\"/12/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/12/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            client.println("</div>");
            
            client.println("<div style='margin: 0 30px; width: 210px'>");
            // Display current state, and ON/OFF buttons for GPIO 14  
            client.println("<p>Trang thai Phan Bon " + outputPhanBonState + "</p>");
            // If the outputPhanBonState is off, it displays the ON button       
            if (outputPhanBonState=="off") {
              client.println("<p><a href=\"/14/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/14/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            client.println("</div>");
            client.println("</div>");
            
            client.println("<div style='display: flex;  justify-content: center;  align-items: center;'>");
            client.println("<div style='margin: 0 30px; width: 210px'>");
             // Display current state, and ON/OFF buttons for GPIO 2  
            client.println("<p>Trang thai Mo Mai Che " + outputMoMaiCheState + "</p>");
            // If the outputPhanBonState is off, it displays the ON button       
            if (outputMoMaiCheState=="off") {
              client.println("<p><a href=\"/2/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/2/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            client.println("</div>");
            
            client.println("<div style='margin: 0 30px; width: 210px'>");
            // Display current state, and ON/OFF buttons for GPIO 2  
            client.println("<p>Trang thai Dong Mai Che " + outputDongMaiCheState + "</p>");
            // If the outputPhanBonState is off, it displays the ON button       
            if (outputDongMaiCheState=="off") {
              client.println("<p><a href=\"/0/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/0/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            client.println("</div>");
            client.println("</div>");
            client.println("</div>");
            client.println("</body></html>");
            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
            
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != 'r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
        
      }
      
     
    }//while
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.\n");
    Serial.println("");
      if (outputMoMaiCheState == "on" ) {
      digitalWrite(outputMoMaiChe, HIGH);
    }
  }
  



    


//  if ((millis() - lastDebounceTime) > debounceDelay) {
//    if (reading != buttonState) {
//      buttonState = reading; //ở mức cao
//      if (buttonState == HIGH) {
//        ledState = !ledState; //cao sẽ đảo về trạng thái thấp
//      }
//    }
//  }
// digitalWrite(outputMoMaiChe, ledState);
}

// digitalWrite(outputMoMaiChe, ledState);
 
  //lastButtonState = reading;
//void aplyCmd(){
//  // read the state of the switch into a local variable:
//  int reading = digitalRead(buttonBom);
//  if (reading != lastButtonState) {
//    // reset the debouncing timer
//    lastDebounceTime = millis();
//  }
//
//  if ((millis() - lastDebounceTime) > debounceDelay) {
//    if (reading != buttonState) {
//      buttonState = reading;
//      if (buttonState == HIGH) {
//        ledState = !ledState;
//      }
//    }
//  }
//
// digitalWrite(outputMoMaiChe, ledState);
//  lastButtonState = reading;

//}
