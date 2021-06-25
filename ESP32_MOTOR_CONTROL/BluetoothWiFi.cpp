#include <WiFi.h>
#include <Arduino.h>
#include "WebSite.h"
#include "BluetoothSerial.h"
#include "BluetoothWiFi.h"

//server object with port 80 open is created
BluetoothWiFi::BluetoothWiFi() : server(80)
{
}

void BluetoothWiFi::wifiConnect()
{
  // Network credentials
  const char* ssid     = "ImagineLTE_A54602";
  const char* password = "16008427";

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
    Serial.print(".");
    delay(300);
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

String BluetoothWiFi::webControl()
{
  // Current time
  unsigned long currentTime = millis();
  // Previous time
  unsigned long previousTime = 0;
  // Define timeout time in milliseconds (example: 2000ms = 2s)
  const long timeoutTime = 2000;

  int pos1 = 0;
  int pos2 = 0;

  // Variable to store the HTTP request
  String header;

  // Decode HTTP GET value
  String valueString;

  // Listen for incoming clients
  client = server.available();

  // Client Connected
  if (client)
  {
    // Set timer references
    currentTime = millis();
    previousTime = currentTime;

    // Print to serial port
    Serial.println("New Client.");

    // String to hold data from client
    String currentLine = "";

    // Do while client is cponnected
    while (client.connected() && currentTime - previousTime <= timeoutTime) {
      currentTime = millis();
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {

            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK) and a content-type
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            client.println(webpage); // displays the webpage

            // GET data
            if (header.indexOf("GET /?value=") >= 0) {
              pos1 = header.indexOf('=');
              pos2 = header.indexOf('&');

              // String with motor position
              valueString = header.substring(pos1 + 1, pos2);
            }
            // The HTTP response ends with another blank line
            client.println();

            // Break out of the while loop
            break;

          }
          else
          {
            // New lline is received, clear currentLine
            currentLine = "";
          }
        }
        else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");

    return valueString; //returns the string of values
  }
}
/*
 * will connect to a bluetooth device
 * the devices MAC address and pin is given
 * the function will then try to connect
 * 
 * if a connection is made the function returns TRUE
 * if not it returns FALSE
 */
bool BluetoothWiFi::btConnect()
{
  SerialBT.begin("ESP32", true);
  
  uint8_t address[6]  = {0x00, 0x14, 0x03, 0x06, 0x0C, 0x46};// MAC Address of HC-05
  char *pin = "1234";//HC-05 Password
  bool connected;

  Serial.println("The device started in master mode, make sure remote BT device is on!");

  connected = SerialBT.connect(address);

  if(connected)
  {
    Serial.println("Connected");
    return connected;
  }
  else 
  {
    return connected; 
  }
}

bool BluetoothWiFi::isBTConnect()
{
  if(SerialBT.available())
  {
    return 1;
  }
  else
  {
    return 0;
  }
}
/*
 *  while chars are being received
 *  variable c will store the current char and then add it 
 *  to the recievedChars char array
 *  
 */
 void BluetoothWiFi::receiveBTData(char receivedChars[])
{
  bool rInProg = 0;
  uint8_t j = 0;
  char startMarker = '<', endMarker = '>', c;

  while (SerialBT.available())
  {
    c = SerialBT.read();
    
    if (rInProg == 1)
    {
      if (c != endMarker)
      {
        receivedChars[j] = c;
        j++;
      }
      else
      {
        receivedChars[j] = '\0'; // terminate the string
        rInProg = 0;
        j = 0;
      }
    }
    else if (c == startMarker)
    {
      rInProg = 1;
    }
  }
}

/*
 * Parses the string that gets passed to it
 * a typical string will look like: <120,88,1>
 * the function will convert the values into ints
 * and assign them to their appropriate variable
 */
void BluetoothWiFi::parseData(String str, int *x, int *pot, int *ammo) // splits the string into parts and assigns them to variables
{
  int comma1, comma2;

  *x = str.toInt(); //converts first number

  comma1 = str.indexOf(",");                //comma1 is equal to the position of the first comma
  *pot = str.substring(comma1 + 1).toInt(); //the position + 1, is then converted to an int

  comma2 = str.indexOf(",", comma1 + 1);    //the comma + the first comma + 1 will get the last value 
  *ammo = str.substring(comma2 + 1).toInt();
}
