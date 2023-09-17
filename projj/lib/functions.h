#include "../include/header.h"
void toggleled() {
    if (millis() - buttonprevious >= 300UL) {
        state = !state;
        digitalWrite(ledPin, state);
        buttonprevious = millis();
    }
}

void handletoggle() {
    toggleled();
    server.send(200, "text/plain", "LED toggled");
}

void handleRoot() {
  // Read the HTML file into a String
  String html;
  File file = SPIFFS.open("/indexx.html", "r");
  if (file) {
    while (file.available()) {
      html += (char)file.read();
    }
    file.close();
  } else {
    Serial.println("Failed to open HTML file");
    return;
  }

  // Replace the placeholder with LED state and color when reloading the page
  String buttonLabel = (state ? "Off" : "On");
  String buttonColor = (state ? "red" : "green");
  html.replace("(LED_STATE)", buttonLabel);
  html.replace("(LED_STATE_COLOR)", buttonColor);

  // Send the HTML content as the response
  server.send(200, "text/html", html);
}