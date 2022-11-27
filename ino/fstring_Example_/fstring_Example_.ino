#include <ArduinoJson.h>

double value = 0;
bool state=false ; 
String longitude = "126.7731674155423";

void setup() {
  // Initialize Serial port
  Serial.begin(9600);
  while (!Serial) continue;

  // Allocate the JSON document
  //
  // Inside the brackets, 200 is the RAM allocated to this document.
  // Don't forget to change this value to match your requirement.
  // Use arduinojson.org/v6/assistant to compute the capacity.
  StaticJsonDocument<200> doc;

  // StaticJsonObject allocates memory on the stack, it can be
  // replaced by DynamicJsonDocument which allocates in the heap.
  //
  // DynamicJsonDocument  doc(200);

  // Add values in the document
  //
  doc["value"] = value;
  doc["longitude"] = longitude;

  if(state){
    doc["state"] = "Active";
  }
  else {
    doc["state"] = "Disable";
  }

  // Generate the minified JSON and send it to the Serial port.
  //
  // serializeJson(doc, Serial);
  // The above line prints:
  // {"value":value,"state":"Active"}

  // Start a new line
  // Serial.println();/

  // Generate the prettified JSON and send it to the Serial port.
  //
  serializeJsonPretty(doc, Serial);
  // The above line prints:
  // {
  //  "value":value,
  //  "state":"Active"
  //}
  // Serial.println(doc.getMember());
}

void loop() {
  // not used in this example
}