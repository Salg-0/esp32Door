#include <Arduino.h>
#include "WiFi.h"
#include <SPI.h>
#include <Wire.h>
#include <MFRC522.h>
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>
#include <Ticker.h>
#include <iostream>
#include <unordered_map>
#include <string>
#include <time.h>
#include <ctime>
#include <iostream>
#include <conf.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

using namespace std;


#define RST_PIN         4
#define SDA_PIN         5
#define DOOR_PIN        25


/*        WIFI          */
WiFiClient client;

/*        SQL         */
MySQL_Connection conn((Client *)&client);
char get_sql[] = "SELECT * FROM rfid_table.permitions where serial_number = '%s'";
char put_sql[] = "INSERT INTO rfid_table.log(serial_number, time) Values ('%s', '%s')";
char alive_sql[] = "INSERT INTO rfid_table.alive(time) Values ('%s')";
char download_sql[] = "SELECT * FROM rfid_table.permitions";
char query[128], uid_buffer[128];

/*        time         */
const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 0;
const int   daylightOffset_sec = 3600;

/*        screen         */
#define SCREEN_ADDRESS 0x3C
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

MFRC522 mfrc522(SDA_PIN, RST_PIN);  // Create MFRC522 instance
bool opening = false, updating = false;
Ticker ticker;
constexpr char hexmap[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
std::unordered_map<string,string> logMap = std::unordered_map<string,string>{};
std::unordered_map<string,string> local_Permitions = local;



void connectToWiFi();
void connectToSQL();
void openingDoor();
void addRemoteLog();
void updateDatabaseFlag();
void updateDatabase();
char* getTime();
void getUID();
void checkPermition();
void addLocalLog();
void updateAndOpen(string name);
void checkOnline();
void updateSQLLog();
void updateLastAlive();
void sendLocalLog(std::pair<string,string> entry);
std::unordered_map<std::string, std::string> sqlResults(char* sql_query);
void executeSQL();
void clearScreen();



void setup() {


  Serial.begin(9600);
  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("failed to start SSD1306 OLED"));
    while (1);
  }

  Serial.println("Booting...");
  
  oled.clearDisplay(); // clear display

  oled.setTextSize(3);
  oled.setTextColor(WHITE);
  oled.setCursor(0, 10);
  oled.println("Booting...");
  oled.display();
  
  delay(2000);         // wait two seconds for initializing
  //Initialize pins to correct modes. 
  pinMode(LED_BUILTIN, OUTPUT);
  // pinMode(D1, OUTPUT);
  pinMode(DOOR_PIN, OUTPUT);

  oled.clearDisplay();
  oled.drawBitmap(0, 18, TSB.data, TSB.width, TSB.height, WHITE);
  oled.display();
  
  connectToWiFi();
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  if(!conn.connected() && !only_local) connectToSQL();
  else{
    oled.drawBitmap(16, 0, white.data, no_database.height, no_database.width, BLACK);
    oled.drawBitmap(16, 0, no_database.data, no_database.height, no_database.width, WHITE);
    oled.display();
  }

  
  while (!Serial);		// Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
	SPI.begin();			// Init SPI bus
	mfrc522.PCD_Init(); // Init MFRC522
	delay(4);				// Optional delay. Some board do need more time after init to be ready, see Readme
	mfrc522.PCD_DumpVersionToSerial();	// Show details of PCD - MFRC522 Card Reader details
  
  if(!only_local) ticker.attach(120, updateDatabaseFlag);
	Serial.println("setup end");
  digitalWrite(LED_BUILTIN, LOW);

  clearScreen();
}

void loop() {

  if(updating) updateDatabase();

	if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) return;
  
  getUID();

  checkPermition();

  clearScreen();

}

void clearScreen(){
    delay(2000);
    oled.drawBitmap(95, 0, white.data, white.width, white.height, BLACK);
    oled.drawBitmap(95, 0, lock.data, lock.width, lock.height, WHITE);
    oled.display();
  }


void checkPermition(){
  if (local_Permitions.find(uid_buffer) != local_Permitions.end()){
    openingDoor();
  } else if (conn.connected() && !only_local){
    checkOnline();
  } else {
    addLocalLog();
  }

}

void addLocalLog(){
  Serial.printf("################# Local log %s at %s#######################  \n", uid_buffer, getTime());
  logMap[uid_buffer] = getTime();
  oled.drawBitmap(95, 0, white.data, white.width, white.height, BLACK);
  oled.drawBitmap(95, 0, block.data, block.width, block.height, WHITE);
  oled.display();
  

}

void checkOnline(){
  Serial.println("################# ON-LINE #######################");
  sprintf(query, get_sql, uid_buffer);
  std::unordered_map<string, string> results = sqlResults(query);
  (results.find(uid_buffer) != results.end()) ? updateAndOpen(results[uid_buffer]) : addRemoteLog();
}

void updateAndOpen(string name){
  openingDoor();
  local_Permitions[uid_buffer] = name;
}


bool isAlphaNumericWithSpaces(const char* str) {
  while (*str) {
      if (!std::isalnum(*str) && *str != ' ') {
          return false;
      }
      ++str;
  }
  return true;
}

std::unordered_map<std::string, std::string> sqlResults(char* sql_query){
  std::unordered_map<std::string, std::string> resultMap;
  MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
  sprintf(query, sql_query, uid_buffer);
  cur_mem->execute(query);
  cur_mem->get_columns();
  row_values *row;
  do {
    row = cur_mem->get_next_row();
    if (row != NULL) {
      Serial.printf("%s | %s\t",row->values[0], row->values[1]);
      if(isAlphaNumericWithSpaces(row->values[0]) && isAlphaNumericWithSpaces(row->values[1])){
        resultMap[row->values[0]] = row->values[1];
        Serial.printf(" yup all goood \n");
      }else{
        //retry loading
      }
    }
  } while (row != NULL);
  delete cur_mem;
  return resultMap;
}

void getUID(){
  for (int i = 0; i < mfrc522.uid.size; ++i) {
    uid_buffer[2 * i]     = hexmap[(mfrc522.uid.uidByte[i] & 0xF0) >> 4];
    uid_buffer[2 * i + 1] = hexmap[mfrc522.uid.uidByte[i] & 0x0F];
  }
  uid_buffer[mfrc522.uid.size * 2] = '\0';
  Serial.printf("uid: %s\n", uid_buffer);
}


char* getTime(){
  time_t curr_time;
  curr_time = time(NULL);
  return ctime(&curr_time);
}



void openingDoor(){
  Serial.printf("\n --------------------open------------ %s ----------\n", uid_buffer);

  oled.drawBitmap(95, 0, white.data, white.width, white.height, BLACK);
  oled.drawBitmap(95, 0, open_lock.data, open_lock.width, open_lock.height, WHITE);
  oled.display();

  digitalWrite(DOOR_PIN, HIGH);
  delay(200);
  digitalWrite(DOOR_PIN, LOW);
}


void addRemoteLog(){
  Serial.printf("\n --------------------adding------------ %s ---------\n", uid_buffer);
  sprintf(query, put_sql, uid_buffer, getTime());
  executeSQL();
  oled.drawBitmap(95, 0, white.data, white.width, white.height, BLACK);
  oled.drawBitmap(95, 0, block.data, block.width, block.height, WHITE);
  oled.display();
}

void updateDatabaseFlag(){
  updating = true;
}

void updateDatabase(){
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.printf("\n --------------------Data Base updated--------at %s-----\n", getTime());
  
  
  if(WiFi.status() != WL_CONNECTED){
    connectToWiFi();
  }
  if(!conn.connected()){
    connectToSQL();
  }
  if(conn.connected()){
    updateSQLLog();
    updateLastAlive();
  }
  updating = false;
  digitalWrite(LED_BUILTIN, LOW);
}

void updateSQLLog(){
  for(std::pair<string,string> log : logMap){
    sendLocalLog(log);
  }
}

void updateLastAlive(){
  Serial.printf("\n --------------------alive------------ %s ---------\n", getTime());
  sprintf(query, alive_sql, getTime());
  executeSQL();
}

void sendLocalLog(std::pair<string,string> entry){
  Serial.printf("\n --------------------adding------------ %s ---------\n", uid_buffer);
  sprintf(query, put_sql, entry.first.c_str(), entry.second.c_str());
  executeSQL();
}

void connectToSQL() {
  if (conn.connect(sql_ip, sql_port, sql_user, sql_password)) {
    Serial.println("Database connected.");
    oled.drawBitmap(16, 0, white.data, database.height, database.width, BLACK);
    oled.drawBitmap(16, 0, database.data, database.height, database.width, WHITE);
    oled.display();
  }
  else{
    Serial.println("SQL Connection failed.");
    oled.drawBitmap(16, 0, white.data, database.height, database.width, BLACK);
    oled.drawBitmap(16, 0, no_database.data, no_database.height, no_database.width, WHITE);
    oled.display();
  }
}

void connectToWiFi() {
  Serial.printf("Connecting to '%s'\n", wifi_ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(wifi_ssid, wifi_password);
  if (WiFi.waitForConnectResult() == WL_CONNECTED) {
    Serial.print("Connected. IP: ");
    Serial.println(WiFi.localIP());
    oled.drawBitmap(0, 0, white.data, wifi.height, wifi.width, BLACK);
    oled.drawBitmap(0, 0, wifi.data, wifi.height, wifi.width, WHITE);
    oled.display();
  } else {
    Serial.println("WIFI Connection Failed!");
    oled.drawBitmap(0, 0, white.data, wifi.height, wifi.width, BLACK);
    oled.drawBitmap(0, 0, no_wifi.data, no_wifi.height, no_wifi.width, WHITE);
    oled.display();
  }
}

void executeSQL(){
  MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
  Serial.printf("loging query: %s\n", query);
  cur_mem->execute(query);
  delete cur_mem;
}