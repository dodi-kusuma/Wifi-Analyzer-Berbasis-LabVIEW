/*
    This sketch demonstrates how to scan WiFi networks.
    The API is almost the same as with the WiFi Shield library,
    the most obvious difference being the different file you need to include:
*/
#include <ESP8266WiFi.h>
/*Fungsi void setup() dijalankan pada saat sketch atau program Arduino mulai.
Fungsi ini digunakan untuk menginisiasi variabel, mendeklarasikan pin yang digunakan,
menggunakan library, dll. */
void setup() {
  Serial.begin(115200);//buka port serial dengan bitrate 115200 baud
  Serial.println(F("\nESP8266 WiFi scan example"));
  // Set WiFi to station mode// station mode: the ESP32 connects to an access point
  WiFi.mode(WIFI_STA);
  // Disconnect from an AP if it was previously connected
  WiFi.disconnect();
  delay(100);
}
/*Fungsi void loop() dijalankan setelah fungsi setup() sudah selesai dijalankan,
 * void loop() bertujuan untuk mengeksekusi dan menjalankan program yang sudah dibuat.
Fungi ini akan secara aktif mengontrol board Arduino baik membaca input atau merubah output.
*/ 
void loop() {
  String ssid; /* String yaitu tipe data yang digunakan untuk menuliskan karakter atau teks,
  bisa berupa huruf, angka atau karakter lain*/
  int32_t RSSI; // mediumInt
  uint8_t encryptionType; // smallInt
  uint8_t* BSSID; // smallInt BSSID adalah nama lain dari SSID, SSID diberikan oleh pemakai misalnya “pcsaya” pada komputer yang sedang digunakan dan komputer lainnya dibuatkan nama “pckamu”. Sedangkan BSSID mengunakan basis MAC address.
  int32_t channel; // mediumInt
  bool isHidden;
  int scanResult;
/*Serial.print("This is a test - Hello world!!");
uses SRAM for the string, so few such prints and your SRAM is full.
You may use:
Serial.print(F("This is a test - Hello world!!"));
and it uses FLASH for storing the string, thus you save the SRAM.
p.*/
  Serial.println(F("Starting WiFi scan..."));
  scanResult = WiFi.scanNetworks();
  
  if (scanResult == 0) {
    Serial.println(F("No networks found"));
  } else if (scanResult > 0) {
    Serial.printf(PSTR("%d networks found:\n"), scanResult);

    // Print unsorted scan results
    for (int8_t i = 0; i < scanResult; i++) {
      WiFi.getNetworkInfo(i, ssid, encryptionType, RSSI, BSSID, channel, isHidden);
// %02d : dua digit
      Serial.printf(PSTR("  %02d: [CH %02d] [%02x:%02x:%02x:%02x:%02x:%02x] %ddBm %c %c %s\n"),
                    i, channel, BSSID[0], BSSID[1], BSSID[2], BSSID[3], BSSID[4], BSSID[5], RSSI,
                    (encryptionType == ENC_TYPE_NONE) ? ' ' : '*',
                    isHidden ? 'H' : 'V',
                    ssid.c_str());
      delay(0);
    }
  } else {
    Serial.printf(PSTR("WiFi scan error %d"), scanResult);
  }

  // Wait a bit before scanning again
  delay(5000);
}
