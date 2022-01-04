#ifdef ESP32 // ESP32 libraries
#include <WiFi.h>
#include <AsyncTCP.h>
#else // ESP8266 libraries
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#endif
#include <ESPAsyncWebServer.h>
 
//******Enter your network credentials************
const char* ssid = "";
const char* password = "";
//************************************************
 
//Define Status
const char* PARAM_INPUT_1 = "state";
const char* PARAM_INPUT_2 = "state2";
const char* PARAM_INPUT_3 = "state3";
const char* PARAM_INPUT_4 = "state4";
const char* PARAM_INPUT_5 = "state5";
const char* PARAM_INPUT_6 = "state6";
 
//**********Pin Assignments***********
const int relay1 = 33; //bơm
const int switch1 = 23; //nút bật tắt bơm
const int relay2 = 32; // đèn
const int switch2 = 13; // nút bật tắt đèn
const int relay3 = 25; //quạt
const int switch3 = 16; //nút bật tắt quạt
const int relay4 = 26; //bón phân
const int switch4 = 17; //
const int relay5 = 27; //mở mái che
const int switch5 = 19; 
const int relay6 = 14; // đóng mái che
const int switch6 = 18; //
const int switch7 = 5; //
const int switch8 = 15; //

//************************************

//*********************Variables declaration**********************
int relay_1_status = LOW; // the current status of relay1
int switch_1_status; // the current status of switch1
int last_switch_1_status = LOW; // Last status of switch1
int relay_2_status = LOW;
int switch_2_status;
int last_switch_2_status = LOW; 
int relay_3_status = LOW; 
int switch_3_status; 
int last_switch_3_status = LOW; 
int relay_4_status = LOW; 
int switch_4_status; 
int last_switch_4_status = LOW; 
int relay_5_status = LOW; 
int switch_5_status; 
int last_switch_5_status = LOW; 
int relay_6_status = LOW; 
int switch_6_status; 
int last_switch_6_status = LOW; 

//****************************************************************
 
// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0; // the last time the output pin was toggled
unsigned long debounceDelay = 50; // the debounce time; increase if the output flickers
 
// Create AsyncWebServer object on port 80
AsyncWebServer server(80);
 
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
<title>Home page</title>
<meta name="viewport" content="width=device-width, initial-scale=1">
<style>
html {font-family: Arial; display: inline-block; text-align: center;}
h2 {font-size: 3.0rem;}
p {font-size: 3.0rem;}
body {max-width: 600px; margin:0px auto; padding-bottom: 25px;}
.switch {position: relative; display: inline-block; width: 120px; height: 68px}
.switch input {display: none}
.slider {position: absolute; top: 0; left: 0; right: 0; bottom: 0; background-color: #F63E36; border-radius: 34px}
.slider:before {position: absolute; content: ""; height: 52px; width: 52px; left: 8px; bottom: 8px; background-color: #fff; -webkit-transition: .4s; transition: .4s; border-radius: 68px}
input:checked+.slider {background-color: #3CC33C}
input:checked+.slider:before {-webkit-transform: translateX(52px); -ms-transform: translateX(52px); transform: translateX(52px)}
</style>
</head>
<body>
<h2>Vườn rau tự động</h2>
<meta charset="utf-8">
<div>
<div style='display: flex;  justify-content: center;  align-items: center;'>
<div style='margin: 0 30px; width: 210px'>
%BUTTONPLACEHOLDER%
</div>
<div style='margin: 0 30px; width: 210px'>
%BUTTONPLACEHOLDER2%
</div>
</div>
<div style='display: flex;  justify-content: center;  align-items: center;'>
<div style='margin: 0 30px; width: 210px'>
%BUTTONPLACEHOLDER3%
</div>
<div style='margin: 0 30px; width: 210px'>
%BUTTONPLACEHOLDER4%
</div>
</div>
<div style='display: flex;  justify-content: center;  align-items: center;'>
<div style='margin: 0 30px; width: 210px'>
%BUTTONPLACEHOLDER5%
</div>
<div style='margin: 0 30px; width: 210px'>
%BUTTONPLACEHOLDER6%
</div>
</div>
</div>
<script>

//nut 1
function toggleCheckbox(element)
{
var xhr = new XMLHttpRequest();
if(element.checked)
{
xhr.open("GET", "/update?state=1", true);
}
else
{
xhr.open("GET", "/update?state=0", true);
}
xhr.send();
}

//nut 2 
function toggleCheckbox2(element)
{
var xhr2 = new XMLHttpRequest();
if(element.checked)
{
xhr2.open("GET", "/update?state2=1", true);
}
else
{
xhr2.open("GET", "/update?state2=0", true);
}
xhr2.send();
}

//nut 3
function toggleCheckbox3(element)
{
var xhr3 = new XMLHttpRequest();
if(element.checked)
{
xhr3.open("GET", "/update?state3=1", true);
}
else
{
xhr3.open("GET", "/update?state3=0", true);
}
xhr3.send();
}

//nut 4
function toggleCheckbox4(element)
{
var xhr4 = new XMLHttpRequest();
if(element.checked)
{
xhr4.open("GET", "/update?state4=1", true);
}
else
{
xhr4.open("GET", "/update?state4=0", true);
}
xhr4.send();
}


//nut 5
function toggleCheckbox5(element)
{
var xhr5 = new XMLHttpRequest();
if(element.checked)
{
xhr5.open("GET", "/update?state5=1", true);
}
else
{
xhr5.open("GET", "/update?state5=0", true);
}
xhr5.send();
}

//nut 6
function toggleCheckbox6(element)
{
var xhr6 = new XMLHttpRequest();
if(element.checked)
{
xhr6.open("GET", "/update?state6=1", true);
}
else
{
xhr6.open("GET", "/update?state6=0", true);
}
xhr6.send();
}

setInterval(function ( )
{
var xhttp = new XMLHttpRequest();
xhttp.onreadystatechange = function()
{
if (this.readyState == 4 && this.status == 200)
{
var inputChecked;
var outputStateM;
 
if( this.responseText == 1)
{
inputChecked = true;
outputStateM = "ON";
}
else
{
inputChecked = false;
outputStateM = "OFF";
}
document.getElementById("output").checked = inputChecked;
document.getElementById("outputState").innerHTML = outputStateM;
}
}
xhttp.open("GET", "/state", true);
xhttp.send();
 
var xhttp2 = new XMLHttpRequest();
xhttp2.onreadystatechange = function()
{
if (this.readyState == 4 && this.status == 200)
{
var inputChecked2;
var outputStateM2;
 
if( this.responseText == 1)
{
inputChecked2 = true;
outputStateM2 = "ON";
}
else
{
inputChecked2 = false;
outputStateM2 = "OFF";
}
document.getElementById("output2").checked = inputChecked2;
document.getElementById("outputState2").innerHTML = outputStateM2;
}
};
xhttp2.open("GET", "/state2", true);
xhttp2.send();

var xhttp3 = new XMLHttpRequest();
xhttp3.onreadystatechange = function()
{
if (this.readyState == 4 && this.status == 200)
{
var inputChecked3;
var outputStateM3;
 
if( this.responseText == 1)
{
inputChecked3 = true;
outputStateM3 = "ON";
}
else
{
inputChecked3 = false;
outputStateM3 = "OFF";
}
document.getElementById("output3").checked = inputChecked3;
document.getElementById("outputState3").innerHTML = outputStateM3;
}
};
xhttp3.open("GET", "/state3", true);
xhttp3.send();

var xhttp4 = new XMLHttpRequest();
xhttp4.onreadystatechange = function()
{
if (this.readyState == 4 && this.status == 200)
{
var inputChecked4;
var outputStateM4;
 
if( this.responseText == 1)
{
inputChecked4 = true;
outputStateM4 = "ON";
}
else
{
inputChecked4 = false;
outputStateM4 = "OFF";
}
document.getElementById("output4").checked = inputChecked4;
document.getElementById("outputState4").innerHTML = outputStateM4;
}
};
xhttp4.open("GET", "/state4", true);
xhttp4.send();

var xhttp5 = new XMLHttpRequest();
xhttp5.onreadystatechange = function()
{
if (this.readyState == 4 && this.status == 200)
{
var inputChecked5;
var outputStateM5;
 
if( this.responseText == 1)
{
inputChecked5 = true;
outputStateM5 = "ON";
}
else
{
inputChecked5 = false;
outputStateM5 = "OFF";
}
document.getElementById("output5").checked = inputChecked5;
document.getElementById("outputState5").innerHTML = outputStateM5;
}
};
xhttp5.open("GET", "/state5", true);
xhttp5.send();

var xhttp6 = new XMLHttpRequest();
xhttp6.onreadystatechange = function()
{
if (this.readyState == 4 && this.status == 200)
{
var inputChecked6;
var outputStateM6;
 
if( this.responseText == 1)
{
inputChecked6 = true;
outputStateM6 = "ON";
}
else
{
inputChecked6 = false;
outputStateM6 = "OFF";
}
document.getElementById("output6").checked = inputChecked6;
document.getElementById("outputState6").innerHTML = outputStateM6;
}
};
xhttp6.open("GET", "/state6", true);
xhttp6.send();
}, 1000 ) ;
</script>
</body>
</html>
)rawliteral";
 
// Replaces placeholder with button section in your web page
String processor(const String& var)
{
//Serial.println(var);

if(var == "BUTTONPLACEHOLDER")
{
String buttons1 ="";
String outputStateValue = outputState();
buttons1+= "<h4>Tưới nước <span id=\"outputState\"><span></h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"output\" " + outputStateValue + "><span class=\"slider\"></span></label>";
return buttons1;
}

if(var == "BUTTONPLACEHOLDER2")
{
String buttons2 ="";
String outputStateValue2 = outputState2();
buttons2+= "<h4>Quạt gió <span id=\"outputState2\"><span></h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox2(this)\" id=\"output2\" " + outputStateValue2 + "><span class=\"slider\"></span></label>";
return buttons2;
}

if(var == "BUTTONPLACEHOLDER3")
{
String buttons3 ="";
String outputStateValue3 = outputState3();
buttons3+= "<h4>Đèn <span id=\"outputState3\"><span></h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox3(this)\" id=\"output3\" " + outputStateValue3 + "><span class=\"slider\"></span></label>";
return buttons3;
}

if(var == "BUTTONPLACEHOLDER4")
{
String buttons4 ="";
String outputStateValue4 = outputState4();
buttons4+= "<h4>Bón phân <span id=\"outputState4\"><span></h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox4(this)\" id=\"output4\" " + outputStateValue4 + "><span class=\"slider\"></span></label>";
return buttons4;
}

if(var == "BUTTONPLACEHOLDER5")
{
String buttons5 ="";
String outputStateValue5 = outputState5();
buttons5+= "<h4>Mở mái <span id=\"outputState5\"><span></h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox5(this)\" id=\"output5\" " + outputStateValue5 + "><span class=\"slider\"></span></label>";
return buttons5;
}

if(var == "BUTTONPLACEHOLDER6")
{
String buttons6 ="";
String outputStateValue6 = outputState6();
buttons6+= "<h4>Đóng mái <span id=\"outputState6\"><span></h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox6(this)\" id=\"output6\" " + outputStateValue6 + "><span class=\"slider\"></span></label>";
return buttons6;
}
return String();
}
 
String outputState()
{
if(digitalRead(relay1))
{
return "checked";
}
else
{
return "";
}
return "";
}
String outputState2()
{
if(digitalRead(relay2))
{
return "checked";
}
else
{
return "";
}
return "";
}
String outputState3()
{
if(digitalRead(relay3))
{
return "checked";
}
else
{
return "";
}
return "";
}
String outputState4()
{
if(digitalRead(relay4))
{
return "checked";
}
else
{
return "";
}
return "";
}
String outputState5()
{
if(digitalRead(relay5))
{
return "checked";
}
else
{
return "";
}
return "";
}
String outputState6()
{
if(digitalRead(relay6))
{
return "checked";
}
else
{
return "";
}
return "";
}
void setup()
{
// Serial port for debugging purposes
Serial.begin(115200);
 
pinMode(relay1, OUTPUT);
digitalWrite(relay1, LOW);
pinMode(switch1, INPUT);
 
pinMode(relay2, OUTPUT);
digitalWrite(relay2, LOW);
pinMode(switch2, INPUT);

pinMode(relay3, OUTPUT);
digitalWrite(relay3, LOW);
pinMode(switch3, INPUT);

pinMode(relay4, OUTPUT);
digitalWrite(relay4, LOW);
pinMode(switch4, INPUT);

pinMode(relay5, OUTPUT);
digitalWrite(relay5, LOW);
pinMode(switch5, INPUT);

pinMode(relay6, OUTPUT);
digitalWrite(relay6, LOW);
pinMode(switch6, INPUT);
 
// Connect to Wi-Fi
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED)
{
delay(1000);
Serial.println("Connecting to WiFi..");
}
 
// Print ESP Local IP Address
Serial.println(WiFi.localIP());
 
// Route for root / web page
server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
{
request->send_P(200, "text/html", index_html, processor);
});
 
// Send a GET request
server.on("/update", HTTP_GET, [] (AsyncWebServerRequest *request)
{
String inputMessage;
String inputParam;
 
// GET input1 value on <ESP_IP>/update?state=<inputMessage>
if (request->hasParam(PARAM_INPUT_1))
{
inputMessage = request->getParam(PARAM_INPUT_1)->value();
inputParam = PARAM_INPUT_1;
digitalWrite(relay1, inputMessage.toInt());
relay_1_status = !relay_1_status;
}
else
{
inputMessage = "No message sent";
inputParam = "none";
}
Serial.println(inputMessage);
request->send(200, "text/plain", "OK");
 
String inputMessage2;
String inputParam2;
 
if (request->hasParam(PARAM_INPUT_2))
{
inputMessage2 = request->getParam(PARAM_INPUT_2)->value();
inputParam2 = PARAM_INPUT_2;
digitalWrite(relay2, inputMessage2.toInt());
relay_2_status = !relay_2_status;
}
else
{
inputMessage2 = "No message sent";
inputParam2 = "none";
}
Serial.println(inputMessage2);
request->send(200, "text/plain", "OK");

String inputMessage3;
String inputParam3;
 
if (request->hasParam(PARAM_INPUT_3))
{
inputMessage3 = request->getParam(PARAM_INPUT_3)->value();
inputParam3 = PARAM_INPUT_3;
digitalWrite(relay3, inputMessage3.toInt());
relay_3_status = !relay_3_status;
}
else
{
inputMessage3 = "No message sent";
inputParam3 = "none";
}
Serial.println(inputMessage3);
request->send(200, "text/plain", "OK");

String inputMessage4;
String inputParam4;
 
if (request->hasParam(PARAM_INPUT_4))
{
inputMessage4 = request->getParam(PARAM_INPUT_4)->value();
inputParam4 = PARAM_INPUT_4;
digitalWrite(relay4, inputMessage4.toInt());
relay_4_status = !relay_4_status;
}
else
{
inputMessage4 = "No message sent";
inputParam4 = "none";
}
Serial.println(inputMessage4);
request->send(200, "text/plain", "OK");

String inputMessage5;
String inputParam5;
 
if (request->hasParam(PARAM_INPUT_5))
{
inputMessage5 = request->getParam(PARAM_INPUT_5)->value();
inputParam5 = PARAM_INPUT_5;
digitalWrite(relay5, inputMessage5.toInt());
relay_5_status = !relay_5_status;
}
else
{
inputMessage5 = "No message sent";
inputParam5 = "none";
}
Serial.println(inputMessage5);
request->send(200, "text/plain", "OK");

String inputMessage6;
String inputParam6;
 
if (request->hasParam(PARAM_INPUT_6))
{
inputMessage6 = request->getParam(PARAM_INPUT_6)->value();
inputParam6 = PARAM_INPUT_6;
digitalWrite(relay6, inputMessage6.toInt());
relay_6_status = !relay_6_status;
}
else
{
inputMessage6 = "No message sent";
inputParam6 = "none";
}
Serial.println(inputMessage6);
request->send(200, "text/plain", "OK");
});
 
// Send a GET request to <ESP_IP>/state
server.on("/state", HTTP_GET, [] (AsyncWebServerRequest *request)
{
request->send(200, "text/plain", String(digitalRead(relay1)).c_str());
});
 
server.on("/state2", HTTP_GET, [] (AsyncWebServerRequest *request)
{
request->send(200, "text/plain", String(digitalRead(relay2)).c_str());
});

server.on("/state3", HTTP_GET, [] (AsyncWebServerRequest *request)
{
request->send(200, "text/plain", String(digitalRead(relay3)).c_str());
});

server.on("/state4", HTTP_GET, [] (AsyncWebServerRequest *request)
{
request->send(200, "text/plain", String(digitalRead(relay4)).c_str());
});

server.on("/state5", HTTP_GET, [] (AsyncWebServerRequest *request)
{
request->send(200, "text/plain", String(digitalRead(relay5)).c_str());
});

server.on("/state6", HTTP_GET, [] (AsyncWebServerRequest *request)
{
request->send(200, "text/plain", String(digitalRead(relay6)).c_str());
});
// Start server
server.begin();
}
 
void loop()
{
int reading1 = digitalRead(switch1);
if (reading1 != last_switch_1_status)
{
lastDebounceTime = millis(); // reset the debouncing timer
}
 
if ((millis() - lastDebounceTime) > debounceDelay) 
{ 
if (reading1 != switch_1_status)
{
switch_1_status = reading1;
if (switch_1_status == HIGH)
{
relay_1_status = !relay_1_status;
}
}
}
 
int reading2 = digitalRead(switch2);
if (reading2 != last_switch_2_status)
{
lastDebounceTime = millis();
}
 
if ((millis() - lastDebounceTime) > debounceDelay)
{
if (reading2 != switch_2_status)
{
switch_2_status = reading2;
if (switch_2_status == HIGH)
{
relay_2_status = !relay_2_status;
}
}
}

int reading3 = digitalRead(switch3);
if (reading3 != last_switch_3_status)
{
lastDebounceTime = millis();
}
 
if ((millis() - lastDebounceTime) > debounceDelay)
{
if (reading3 != switch_3_status)
{
switch_3_status = reading3;
if (switch_3_status == HIGH)
{
relay_3_status = !relay_3_status;
}
}
}


// set the LED:
digitalWrite(relay1, relay_1_status);
digitalWrite(relay2, relay_2_status);
digitalWrite(relay3, relay_3_status);
 
// save the reading. Next time through the loop, it'll be the lastButtonState:
last_switch_1_status = reading1;
last_switch_2_status = reading2;
last_switch_3_status = reading3;

}
