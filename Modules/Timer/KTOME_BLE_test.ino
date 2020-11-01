//======================================================================
//
//  Keep Talking Or the Microcontroller Explodes!
//
//    - bcorwen, 4/7/20
//======================================================================
//
//  Module: Timer (MASTER)
//
//  version 0.1.0
//
//  Goal for this version: Get this thing going!
//
//======================================================================

//**********************************************************************
// LIBRARIES
//**********************************************************************
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <Wire.h>
#include <CAN.h>
//#include <Adafruit_GFX.h>
//#include <Adafruit_LEDBackpack.h>
//#include <Entropy.h>
//#include <LiquidCrystal.h>

//**********************************************************************
// GLOBAL VARIABLES
//**********************************************************************
#define PIN_CAN_TX  GPIO_NUM_26
#define PIN_CAN_RX  GPIO_NUM_27
//#define PIN_PIEZO   GPIO_NUM_2
#define PIN_LED     GPIO_NUM_12
#define PIN_BUTTON  GPIO_NUM_36

//Adafruit_7segment timer_display = Adafruit_7segment(); // Default pins: I2C SCL = GPIO22, I2C SDA = CPIO21

// Game
byte gamemode = 0;
bool game_ready = false;

int module_array[12];
bool module_detected = false;
bool module_inited = false;
byte module_count = 0;
byte spec_mod_count = 0;

// Timer
long timeleft;
int gamelength = 300; //seconds
long thismillis;
//long delta_t;
char timestr[5] = "----";
bool hardcore_mode = false;
byte strike_number = 0;
byte strikelimit = 3;
char sec_tick_over;
long buzz_timer;
byte time_scale; // Quadruple the time scale: 4 = 1x speed (normal), 5 = 1.25x speed (1 strike), etc...
long blinktime;
long blinkperiod = 250; // Milliseconds
bool blinkbool;
long buzzerinterrupt;

// Widgets
char serial_number[7];
bool serial_vowel;
bool serial_odd;
bool serial_even;
//
//byte battery_number;
//byte port_number;
//byte ind_number;
//byte widget_types[5];
//
//bool parallel_port;
//bool ind_frk;
//bool ind_car;

// CAN                      [ Module type ][ID][ unused ]
#define CAN_ID            0b10000000000000000000000000000 // ID for Master (timer)
#define CAN_MASK          0b10000000000000000000000000000 // Filter for the Master (timer)

#define CAN_TO_MASTER     0b10000000000000000000000000000
#define CAN_TO_WIRES      0b01000000000000000000000000000
#define CAN_TO_BUTTON     0b00100000000000000000000000000
#define CAN_TO_KEYPAD     0b00010000000000000000000000000
#define CAN_TO_SIMON      0b00001000000000000000000000000
#define CAN_TO_WHOS       0b00000100000000000000000000000
#define CAN_TO_MEMORY     0b00000010000000000000000000000
#define CAN_TO_MORSE      0b00000001000000000000000000000
#define CAN_TO_CWIRES     0b00000000100000000000000000000
#define CAN_TO_WIRESQ     0b00000000010000000000000000000
#define CAN_TO_MAZE       0b00000000001000000000000000000
#define CAN_TO_PASSWORD   0b00000000000100000000000000000
#define CAN_TO_VENT       0b00000000000010000000000000000
#define CAN_TO_CAPACITOR  0b00000000000001000000000000000
#define CAN_TO_KNOB       0b00000000000000100000000000000
#define CAN_TO_STD_MOD    0b01111111111100000000000000000
#define CAN_TO_NEEDY_MOD  0b00000000000011100000000000000
#define CAN_TO_ALL_MOD    0b01111111111111100000000000000
#define CAN_MUID_1        0b00000000000000010000000000000
#define CAN_MUID_2        0b00000000000000001000000000000
#define CAN_MUID_3        0b00000000000000000100000000000
#define CAN_MUID_4        0b00000000000000000010000000000
#define CAN_MUID_ALL      0b00000000000000011110000000000

#define CAN_MANUALSETUP   0b01110000110000000000000000000

char buffer_msg[9][16];
int buffer_can_id[16];
byte buffer_pointer_r;
byte buffer_pointer_w;
char msg_received[9];
int msg_rec_id;

// BLE
bool deviceConnected = false;
String BLE_value;
String BLE_state = "";
#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"
String temp_holder;

class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;
    };
    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
    }
};

class MyCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
      std::string value = pCharacteristic->getValue();
      if (value.length() > 0) {
        BLE_value = "";
        for (int i = 0; i < value.length(); i++) {
          BLE_value = BLE_value + value[i];
        }
        Serial.print("BLE_value = ");
        Serial.println(BLE_value);

        // Add in switch/case or if/else to set flags based on BLE_value input.
        BLE_state = "";
        if (BLE_value.substring(0, 2) == "t=") {
          temp_holder = BLE_value.substring(2);
          gamelength = temp_holder.toInt();
          BLE_state = "ok";
        } else if (BLE_value.substring(0, 2) == "h=") { // Hardcore selector
          if (BLE_value.substring(2) == "0") {
            hardcore_mode = false;
          } else {
            hardcore_mode = true;
          }
          BLE_state = "ok";
        } else if (BLE_value == "ml") { // Request for list of connected modules
          for (byte i = 1; i < 15; i++) {
            if (i > 1) {
              BLE_state = BLE_state + " ";
            }
            spec_mod_count = 0;
            for (byte j = 0; j < module_count; j++) {
              if ((module_array[j] & CAN_TO_ALL_MOD) == (CAN_TO_MASTER >> i)) {
                spec_mod_count++;
              }
            }
            BLE_state = BLE_state + char(spec_mod_count + '0'); // Space=separated list of numbers corresponding to the amount of modules detected in the bomb
          }
        } else if (BLE_value == "mL") { // Request for list of connected modules
          gamemode = 0;
          for (byte i = 1; i < 15; i++) {
            if (i > 1) {
              BLE_state = BLE_state + " ";
            }
            spec_mod_count = 0;
            for (byte j = 0; j < module_count; j++) {
              if ((module_array[j] & CAN_TO_ALL_MOD) == (CAN_TO_MASTER >> i)) {
                spec_mod_count++;
              }
            }
            BLE_state = BLE_state + char(spec_mod_count + '0'); // Space=separated list of numbers corresponding to the amount of modules detected in the bomb
          }
        } else if (BLE_value == "ri") { // Request master to re-run initialisation of connect modules
          BLE_state = "ok";
          gamemode = 0;
        } else if (BLE_value == "mms") { // Start manual module setup
          BLE_state = "b 2 3"; // Space=separated list of manual setup instructions: first char is letter coded to module type, then numbers corresponding to app array
        } else if (BLE_value == "?") { // Check/confirm manual setup
          BLE_state = "ok"; // "!" if incorrect on check, otherwise send next manual module setup as above; "ok" when completed setup for all modules
        } else if (BLE_value == "gs") { // Start game
          game_ready = true;
          BLE_state = "ok";
        } else if (BLE_value == "check") { // LEGACY - unused
          BLE_state = "";
          // Add in statements to change BLE_state, which will be sent back to phone
          BLE_state = "timer = " + char(gamelength);
        }
        pCharacteristic->setValue(BLE_state.c_str()); // Return status
        Serial.print("BLE_state = ");
        Serial.println(BLE_state);
      }
    }
};

//**********************************************************************
// FUNCTIONS: Main
//**********************************************************************
void setup() {

  // Start serial connection
  Serial.begin(115200);
  while (!Serial);
  Serial.println("== KTOME: Timer ==");

  // Start CAN bus
  CAN.setPins(PIN_CAN_RX, PIN_CAN_TX);
  // start the CAN bus at 500 kbps
  if (!CAN.begin(500E3)) {
    Serial.println("Starting CAN failed!");
    while (1);
  }
  //  CAN.filterExtended(CAN_ID, CAN_MASK);
  CAN.onReceive(onReceive);

  // Start BLE
  BLEDevice::init("KTOME");
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());
  BLEService *pService = pServer->createService(SERVICE_UUID);
  BLECharacteristic *pCharacteristic = pService->createCharacteristic(CHARACTERISTIC_UUID, BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE | BLECharacteristic::PROPERTY_NOTIFY | BLECharacteristic::PROPERTY_INDICATE);
  pCharacteristic->setCallbacks(new MyCallbacks());
//  pCharacteristic->setValue("Starting...");
  pService->start();
  BLEAdvertising *pAdvertising = pServer->getAdvertising();
  pAdvertising->start();

  // Randomiser
  //  Entropy.initialize();
  //  randomSeed(Entropy.random());
  esp_random();

  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, LOW);

  pinMode(PIN_BUTTON, INPUT_PULLUP);

}

void loop() {

  switch (gamemode) {
    case 0: // First time set-up
      Serial.println(F("Module search..."));
      initialisation();
      gamemode = 1;
      break;
    case 1: // Game in set-up
      Serial.println(F("Game set-up..."));
      phoneSetup();
      break;
    case 2: // Game running
      Serial.println(F("Game starting!"));
      gameRunning();
      break;
    case 3: // Game wash-up: stand-by state, showing outcome and waiting for new game to be trigger from phone

      break;
  }
}

//**********************************************************************
// FUNCTIONS: Game Initialisation
//**********************************************************************

// Comm with modules to determine what's connected

void initialisation() {

  delay(2000);

  byte max_module_copies = 4;
  char CAN_message[2];
  memset(module_array, 0, sizeof(module_array));

  Serial.println("Starting search for modules...");
  module_count = 0;
  

  //  for (byte c_type = 0; c_type < 14; c_type++) { // Non-shortcut to look through all modules

  //  for (byte c_type = 0; c_type < 1; c_type++) { // Shortcut to just look for wires modules for now...
  //    for (byte c_muid = 0; c_muid < max_module_copies; c_muid++) {
  //      module_detected = false;
  //      CAN_message[0] = 'P';
  //      CAN_message[1] = '\0';
  //      CANSend((CAN_TO_WIRES >> c_type) | (CAN_MUID_1 >> c_muid), CAN_message, 1);
  //
  //      module_detected = false;
  //      digitalWrite(PIN_LED, HIGH);
  //      delay(100);
  //      if (msg_waiting) {
  //        CANReceive();
  //        if (module_detected) {
  //          module_array[module_count] = ((CAN_TO_WIRES >> c_type) | (CAN_MUID_1 >> c_muid));
  //          module_count++;
  //          Serial.print("Module count: ");
  //          Serial.println(module_count);
  //          Serial.print("Module id: ");
  //          padZerosCAN((CAN_TO_WIRES >> c_type) | (CAN_MUID_1 >> c_muid));
  //          Serial.println((CAN_TO_WIRES >> c_type) | (CAN_MUID_1 >> c_muid), BIN);
  //        }
  //      }
  //      digitalWrite(PIN_LED, LOW);
  //      delay(900);
  //    }
  //  }

  // Why are we cycling through all modules and sending a message for each? Just send one message to all!
  CAN_message[0] = 'P';
  CAN_message[1] = '\0';
  CANSend((CAN_TO_ALL_MOD | CAN_MUID_ALL), CAN_message, 1);
  
  //  CANSend(0b01000000000000001000000000000, CAN_message, 1);
  //  CANSend(0b11000000000000001000000000000, CAN_message, 1);
  //  CANSend(0b01000000000000001010000000000, CAN_message, 1);
  //  CANSend(0b11000000000000001010000000000, CAN_message, 1);
  //  CANSend(0b01000000000000001000000000000, CAN_message, 1);
  //  CANSend((CAN_TO_WIRES | CAN_MUID_2), CAN_message, 1);
  //  Serial.println((CAN_TO_WIRES | CAN_MUID_2) - 0b01000000000000001000000000000);
  
  delay(500);

  do { // There are outstanding messages
    CANReceive();
    if (module_detected) {
      module_array[module_count] = (msg_rec_id & (CAN_TO_ALL_MOD | CAN_MUID_ALL));
      Serial.print("Module count: ");
      Serial.println(module_count + 1);
      Serial.print("Module id: 0b");
      padZerosCAN(module_array[module_count]);
      Serial.println(module_array[module_count], BIN);
      module_count++;
    }
  } while (buffer_pointer_r != buffer_pointer_w);

  Serial.println("All modules polled. Connected modules: ");
  for (byte ii = 0; ii < module_count; ii ++) {
    Serial.print("0b");
    padZerosCAN(module_array[ii]);
    Serial.println(module_array[ii], BIN);
  }


}

//**********************************************************************
// FUNCTIONS: Game Setup
//**********************************************************************

// Comm with phone to set up a game

void phoneSetup() {

  bool game_ready = false;

  widgetGenerate(); // Generate widgets
  serialGenerate(); // Generate serial #

  moduleCheck();

  long timer_int;

  do {

    thismillis = millis();
    bool led_state;

    if (thismillis > timer_int) {
      timer_int = thismillis + 250;
      if (led_state) {
        digitalWrite(PIN_LED, LOW);
        led_state = false;
      } else {
        digitalWrite(PIN_LED, HIGH);
        led_state = true;
      }
    }

  } while (!game_ready && (gamemode == 1));

}

void moduleCheck() {

  char CAN_message[2];

  // Send request to modules to generate games
  CANSend((CAN_TO_ALL_MOD | CAN_MUID_ALL), "I", 1);
  delay(750);
  // Need to check that all modules have replied that they have completed their setup!

  byte mods_setup = 0;
  do { // There are outstanding modules to set up
    CANReceive();
    if (module_inited) {
      Serial.print("Module 0b");
      padZerosCAN(msg_rec_id - CAN_TO_MASTER);
      Serial.print(msg_rec_id - CAN_TO_MASTER, BIN);
      Serial.println(" has set-up a scenario!");
      mods_setup++;
      Serial.print(module_count - mods_setup);
      Serial.println(" modules are left to report in.");
    }
  } while (mods_setup != module_count);

  // Receive games back
  for (byte ii = 0; ii < module_count; ii++) {
    Serial.print("Checking manual for module ");
    Serial.println(ii + 1);
    //    Serial.print("0b");
    //    padZerosCAN(module_array[ii] & CAN_MANUALSETUP);
    //    Serial.println(module_array[ii] & CAN_MANUALSETUP, BIN);
    if ((module_array[ii] & CAN_MANUALSETUP) > 0 ) { // This module needs manual setup
      Serial.println("Needs manual setup!");
      CAN_message[0] = 'C';
      CAN_message[1] = '\0';
      CANSend(module_array[ii], CAN_message, 1);
      delay(500);
      if (buffer_pointer_r != buffer_pointer_w) {
        CANReceive();
        if (module_array[ii] & CAN_TO_WIRES > 0 ) {

        } else if ((module_array[ii] & CAN_TO_BUTTON) > 0 ) {

        } else if ((module_array[ii] & CAN_TO_KEYPAD) > 0 ) {
          Serial.println("Keypad setup incoming...");
          byte keypad_r1 = msg_received[1] - '0';
          byte keypad_r2 = msg_received[2] - '0';
          byte keypad_r3 = msg_received[3] - '0';
          byte keypad_r4 = msg_received[4] - '0';
          Serial.print("Keypad key IDs: ");
          Serial.print(keypad_r1);
          Serial.print(", ");
          Serial.print(keypad_r2);
          Serial.print(", ");
          Serial.print(keypad_r3);
          Serial.print(", ");
          Serial.println(keypad_r4);
        } else if ((module_array[ii] & CAN_TO_CWIRES) > 0 ) {

        } else if ((module_array[ii] & CAN_TO_WIRESQ) > 0 ) {

        }
        // msg_received is available to pull the info from...
      }
    } else {
      Serial.println("Does not need manual setup!");
    }
  }
}

void widgetGenerate () {
  //  byte widget_number = random(2) + 4;
  //  battery_number = random(3) + random(3); // Number from 0-4, with a bias towards 2
  //  if (widget_number > battery_number) {
  //    ind_number = random(1 + widget_number - battery_number);
  //    port_number = widget_number - (battery_number + ind_number);
  //  } else {
  //    port_number = 0;
  //    ind_number = 0;
  //  }
  //  ind_car = false;
  //  ind_frk = false;
  //  bool isthisacopy = false;
  //  lcd.clear();
  //  lcd.setCursor(0, 0);
  //  for (byte i = 0; i < widget_number; i++) {
  //    if (i < battery_number) { // Add battery
  //      widget_types[i] = random(2); // AA or D
  //    } else if (i < (battery_number + ind_number)) { // Add indicator
  //      if (i > 0) {
  //        do {
  //          isthisacopy = false;
  //          widget_types[i] = random(23) + 10; // All inds (11 types), off and on (x2)
  //          for (byte j = 0; j < i; j++) {
  //            if (widget_types[i] % 2 == widget_types[j] % 2) {
  //              isthisacopy = true;
  //            }
  //          }
  //        } while (isthisacopy = true);
  //        if (widget_types[i] == 15) {
  //          ind_car = true; // 14 = off, 15 = on
  //        } else if (widget_types[i] == 17) {
  //          ind_frk = true; // 16 = off, 17 = on
  //        }
  //      }
  //    } else { // Add port
  //      widget_types[i] = random(4) + 40; // Parallel, serial, other
  //      if (widget_types[i] == 40) {
  //        parallel_port = true;
  //      }
  //    }
  //    if (i > 0) {
  //      lcd.print(":");
  //    }
  //    //    lcd.sprintf(widget_types[i], "%02d");
  //    lcd.print(widget_types[i], DEC);
  //  }
}

void serialGenerate () {

  serial_vowel = 0;
  serial_odd = 0;
  serial_even = 0;

  for (int i = 0; i < 6; i++) {
    if (i == 3 || i == 4) {
      serial_number[i] = char_generator(1);
    } else if (i == 2) {
      serial_number[i] = char_generator(0);
    } else if (i == 5) {
      serial_number[i] = char_generator(0);
      if (serial_number[i] % 2 == 1) {
        serial_even = 1;
      } else {
        serial_odd = 1;
      }
    } else {
      serial_number[i] = char_generator(2);
    }
  }
  serial_number[6] = '\0';
  Serial.print(F("Serial #: "));
  Serial.println(serial_number);
  //    Serial.print("Vowels?: ");
  //    Serial.println(serial_vowel);
  //    Serial.print("Even?: ");
  //    Serial.println(serial_odd);
  //    Serial.print("Odds?: ");
  //    Serial.println(serial_even);
}

char char_generator(bool alphanum_type) {
  char temp;
  byte dice_roll;

  if (alphanum_type == 0) {
    dice_roll = random(0, 10);
  } else if (alphanum_type == 1) {
    dice_roll = random(10, 35);
  } else {
    dice_roll = random(0, 35);
  }

  if (dice_roll < 10) {
    temp = dice_roll + '0';
  } else {
    temp = dice_roll + 'A' - 10;
    if (temp == 'A' || temp == 'E' || temp == 'I' || temp == 'O' || temp == 'U') {
      serial_vowel = 1;
      if (temp == 'O') {
        temp = 'E';
      }
    } else if (temp == 'Y') {
      temp = 'Z';
    }
  }
  return temp;
}

//**********************************************************************
// FUNCTIONS: Game Managers
//**********************************************************************

// Managing timer

// Listening to modules

// Game win/loss

void gameRunning() {

  bool game_running = true;

  thismillis = millis();

  while (game_running) {

    // Loop through all checks to do in a single "frame" when the game is in progress

    // Strike update
    // Game win/loss check
    // Timer update
    timerUpdate();

  }



}

//**********************************************************************
// FUNCTIONS: Game functions
//**********************************************************************

void timerUpdate() {

  long delta_t = millis() - thismillis;
  thismillis += delta_t;

  timeleft = timeleft - (delta_t * (1 + strike_number * 0.25)); // Updates the time left with the change in the time since last updating, modified by the time scale due to strikes

  if (timeleft >= 60000) { // Over 1 minute on the clock...
    timestr[0] = (int)(timeleft / 600000) + 48;
    timestr[1] = (int)((timeleft % 600000) / 60000) + 48;
    timestr[2] = (int)((timeleft % 60000) / 10000) + 48;
    timestr[3] = (int)((timeleft % 10000) / 1000) + 48;
  }
  else if (timeleft < 0) { // Timer ran out
    timeleft = 0;
    //      for (int i = 0; i < 4; i++) {
    //        timestr[i] = "0";
    //      }
    timestr[0] = '-';
    timestr[1] = '-';
    timestr[2] = '-';
    timestr[3] = '-';
    //    game_lose(1);
  }
  else { // Under 1 minute left...
    timestr[0] = (int)(timeleft / 10000) + 48;
    timestr[1] = (int)((timeleft % 10000) / 1000) + 48;
    timestr[2] = (int)((timeleft % 1000) / 100) + 48;
    timestr[3] = (int)((timeleft % 100) / 10) + 48;
  }

}

void timerWrite() { // Write "timestr" char array to the timer display

  //  timer_display.writeDigitNum(0, (int)(timestr[0] - 48));
  //  timer_display.writeDigitNum(1, (int)(timestr[1] - 48));
  //  timer_display.writeDigitNum(3, (int)(timestr[2] - 48));
  //  timer_display.writeDigitNum(4, (int)(timestr[3] - 48));
  //  timer_display.drawColon(true);
  //  timer_display.writeDisplay();

}




//**********************************************************************
// FUNCTIONS: Communications
//**********************************************************************

void CANSend(int id, char msg_data[], byte msg_len) {
  Serial.print("Sending packet ... ");
  digitalWrite(PIN_LED, HIGH);

  CAN.beginExtendedPacket(id);
  for (int i = 0; i < msg_len; i++) {
    CAN.write(msg_data[i]);
  }
  //  CAN.write(msg_data, msg_len);
  CAN.endPacket();

  Serial.print(" with id: 0b");
  padZerosCAN(id);
  Serial.print(id, BIN);
  Serial.print(" - \"");
  Serial.print(msg_data);
  Serial.println("\"");
  digitalWrite(PIN_LED, LOW);
}

void onReceive(int packet_size) {

  if ((CAN.packetId() & CAN_MASK) == CAN_ID) {

    for (byte i = 0; i < packet_size; i++) {
      //    msg_received[i] = CAN.read();
      buffer_msg[i][buffer_pointer_w] = CAN.read();
    }
    //  msg_received[packet_size] = '\0';
    buffer_msg[packet_size][buffer_pointer_w] = '\0';

    buffer_can_id[buffer_pointer_w] = CAN.packetId();

    if (buffer_pointer_w == 15) {
      buffer_pointer_w = 0;
    } else {
      buffer_pointer_w++;
    }

  }

}

void CANReceive() {

  Serial.print("Read pointer: ");
  Serial.println(buffer_pointer_r);
  Serial.print("Write pointer: ");
  Serial.println(buffer_pointer_w);
  if (buffer_pointer_r != buffer_pointer_w) { // Outstanding messages to handle
    for (byte ii = 0; ii < 9; ii++) {
      msg_received[ii] = buffer_msg[ii][buffer_pointer_r];
    }
    msg_rec_id = buffer_can_id[buffer_pointer_r];

    if (buffer_pointer_r == 15) {
      buffer_pointer_r = 0;
    } else {
      buffer_pointer_r++;
    }

    Serial.print("Received ");
    Serial.print("packet with id 0b");
    padZerosCAN(msg_rec_id);
    Serial.print(msg_rec_id, BIN);

    Serial.print(" - \"");
    Serial.print(msg_received);
    Serial.println("\"");

    if (msg_received[0] == 'p' && gamemode == 0) {
      module_detected = true;
      Serial.println("Module detected!");
    }
    else if (msg_received[0] == 'i' && gamemode == 1) {
      module_inited = true;
      Serial.println("Module has declare it is setup!");
    }
    else if (msg_received[0] == 'c' && gamemode == 1) {
      Serial.println("Module is transmitting it's manual setup needs!");
    }
  }
}

//**********************************************************************
// FUNCTIONS: Misc. Functions
//**********************************************************************

void padZerosCAN(int id) {
  if (id < (1 << 28)) {
    Serial.print("0");
  }
  if (id < (1 << 27)) {
    Serial.print("0");
  }
  if (id < (1 << 26)) {
    Serial.print("0");
  }
  if (id < (1 << 25)) {
    Serial.print("0");
  }
  if (id < (1 << 24)) {
    Serial.print("0");
  }
  if (id < (1 << 23)) {
    Serial.print("0");
  }
  if (id < (1 << 22)) {
    Serial.print("0");
  }
  if (id < (1 << 21)) {
    Serial.print("0");
  }
  if (id < (1 << 20)) {
    Serial.print("0");
  }
  if (id < (1 << 19)) {
    Serial.print("0");
  }
  if (id < (1 << 18)) {
    Serial.print("0");
  }
  if (id < (1 << 17)) {
    Serial.print("0");
  }
  if (id < (1 << 16)) {
    Serial.print("0");
  }
  if (id < (1 << 15)) {
    Serial.print("0");
  }
  if (id < (1 << 14)) {
    Serial.print("0");
  }
  if (id < (1 << 13)) {
    Serial.print("0");
  }
  if (id < (1 << 12)) {
    Serial.print("0");
  }
  if (id < (1 << 11)) {
    Serial.print("0");
  }
  if (id < (1 << 10)) {
    Serial.print("0");
  }
  if (id < (1 << 9)) {
    Serial.print("0");
  }
  if (id < (1 << 8)) {
    Serial.print("0");
  }
  if (id < (1 << 7)) {
    Serial.print("0");
  }
  if (id < (1 << 6)) {
    Serial.print("0");
  }
  if (id < (1 << 5)) {
    Serial.print("0");
  }
  if (id < (1 << 4)) {
    Serial.print("0");
  }
  if (id < (1 << 3)) {
    Serial.print("0");
  }
  if (id < (1 << 2)) {
    Serial.print("0");
  }
  if (id < (1 << 1)) {
    Serial.print("0");
  }
  //  if (id<(1)) {Serial.print("0");}
}