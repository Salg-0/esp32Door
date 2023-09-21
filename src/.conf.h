#ifndef CONF_H
#define CONF_H

#include <string>
#include <unordered_map>

#define only_local true // if true, only local database is used else sql database is used

// [wifi]
#define wifi_ssid "your_ssid"
#define wifi_password "your_password"

// [sql]
#define sql_ip {0, 0, 0, 0}
#define sql_user "sql_user"
#define sql_password "sql_password"
#define sql_database_table "sql_database.table_name"

#define sql_port sql_port

const std::unordered_map<std::string, std::string> local = 
{
{"card_uid",      	 "user_name"     },
};


// bitmaps

// Define a struct to hold bitmap data and its size
struct Bitmap {
    const unsigned char* data;
    int width;
    int height;
};


// 'TSB_oficial', 32x16px
const unsigned char TSB_bitmap [] PROGMEM = {
	0xff, 0xe3, 0xff, 0xf8, 0xff, 0xe7, 0xff, 0xfc, 0xc0, 0x00, 0x00, 0x0e, 0xc0, 0x00, 0x00, 0x06, 
	0xf3, 0xee, 0x03, 0x0e, 0xf3, 0xef, 0x83, 0x3c, 0x33, 0x07, 0xe3, 0x3c, 0x33, 0x00, 0x73, 0x0e, 
	0x33, 0x00, 0x33, 0x07, 0x30, 0x00, 0x33, 0x07, 0x30, 0x00, 0x73, 0x0e, 0x3f, 0xff, 0xe3, 0xfc, 
	0x3f, 0xff, 0x83, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
const Bitmap TSB = {TSB_bitmap, 32, 16};

//16 X 16
const unsigned char wifi_bitmap [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x0f, 0xf0, 0x3f, 0xfc, 0x70, 0x0e, 0xc7, 0xe3, 0x1f, 0xf8, 0x38, 0x1c, 
	0x13, 0xc8, 0x0f, 0xf0, 0x04, 0x20, 0x01, 0x80, 0x03, 0xc0, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00
};
const Bitmap wifi = {wifi_bitmap, 16, 16};

const unsigned char no_wifi_bitmap [] PROGMEM = {
	0x40, 0x00, 0x60, 0x00, 0x33, 0xf0, 0x39, 0xfc, 0x7c, 0x0e, 0xc6, 0x63, 0x1f, 0x38, 0x39, 0x9c, 
	0x13, 0xc8, 0x0f, 0xe0, 0x04, 0x30, 0x01, 0x98, 0x03, 0xcc, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00
};
const Bitmap no_wifi = {no_wifi_bitmap, 16, 16};

const unsigned char lock_bitmap [] PROGMEM = {
	0x00, 0x07, 0xe0, 0x00, 0x00, 0x1f, 0xf8, 0x00, 0x00, 0x7f, 0xfe, 0x00, 0x00, 0xff, 0xff, 0x00, 
	0x00, 0xfc, 0x3f, 0x00, 0x01, 0xf0, 0x0f, 0x80, 0x01, 0xe0, 0x07, 0x80, 0x03, 0xe0, 0x07, 0xc0, 
	0x03, 0xc0, 0x03, 0xc0, 0x03, 0xc0, 0x03, 0xc0, 0x03, 0xc0, 0x03, 0xc0, 0x03, 0xc0, 0x03, 0xc0, 
	0x03, 0xc0, 0x03, 0xc0, 0x0f, 0xff, 0xff, 0xf0, 0x0f, 0xff, 0xff, 0xf0, 0x0f, 0xff, 0xff, 0xf0, 
	0x0f, 0xff, 0xff, 0xf0, 0x0f, 0xff, 0xff, 0xf0, 0x0f, 0xfc, 0x3f, 0xf0, 0x0f, 0xf8, 0x1f, 0xf0, 
	0x0f, 0xf8, 0x1f, 0xf0, 0x0f, 0xf8, 0x1f, 0xf0, 0x0f, 0xfc, 0x3f, 0xf0, 0x0f, 0xfc, 0x3f, 0xf0, 
	0x0f, 0xfc, 0x3f, 0xf0, 0x0f, 0xfc, 0x3f, 0xf0, 0x0f, 0xfc, 0x3f, 0xf0, 0x0f, 0xfc, 0x3f, 0xf0, 
	0x0f, 0xff, 0xff, 0xf0, 0x0f, 0xff, 0xff, 0xf0, 0x0f, 0xff, 0xff, 0xf0, 0x0f, 0xff, 0xff, 0xf0
};
const Bitmap lock = {lock_bitmap, 32, 32};

const unsigned char open_lock_bitmap [] PROGMEM = {
	0x07, 0xf0, 0x00, 0x00, 0x0f, 0xfc, 0x00, 0x00, 0x1f, 0xfe, 0x00, 0x00, 0x3f, 0xff, 0x00, 0x00, 
	0x3e, 0x1f, 0x00, 0x00, 0x78, 0x0f, 0x80, 0x00, 0x78, 0x07, 0x80, 0x00, 0xf0, 0x07, 0x80, 0x00, 
	0xf0, 0x03, 0x80, 0x00, 0xf0, 0x03, 0xc0, 0x00, 0xf0, 0x03, 0xc0, 0x00, 0xf0, 0x03, 0xc0, 0x00, 
	0xf0, 0x03, 0xc0, 0x00, 0x00, 0x1f, 0xff, 0xfe, 0x00, 0x1f, 0xff, 0xff, 0x00, 0x1f, 0xff, 0xff, 
	0x00, 0x1f, 0xff, 0xff, 0x00, 0x1f, 0xff, 0xff, 0x00, 0x1f, 0xf1, 0xff, 0x00, 0x1f, 0xe0, 0xff, 
	0x00, 0x1f, 0xe0, 0xff, 0x00, 0x1f, 0xe0, 0xff, 0x00, 0x1f, 0xe1, 0xff, 0x00, 0x1f, 0xe1, 0xff, 
	0x00, 0x1f, 0xe1, 0xff, 0x00, 0x1f, 0xe1, 0xff, 0x00, 0x1f, 0xe1, 0xff, 0x00, 0x1f, 0xf1, 0xff, 
	0x00, 0x1f, 0xff, 0xff, 0x00, 0x1f, 0xff, 0xff, 0x00, 0x1f, 0xff, 0xff, 0x00, 0x1f, 0xff, 0xfe
};
const Bitmap open_lock = {open_lock_bitmap, 32, 32};

const unsigned char database_bitmap [] PROGMEM = {
	0x0f, 0xf0, 0x70, 0x0e, 0x40, 0x02, 0x60, 0x06, 0x7f, 0xfe, 0x41, 0x82, 0x40, 0x02, 0x78, 0x1e, 
	0x4f, 0xf2, 0x40, 0x02, 0x40, 0x02, 0x7f, 0xfe, 0x40, 0x02, 0x40, 0x02, 0x70, 0x1e, 0x0f, 0xf0
};
const Bitmap database = {database_bitmap, 16, 16};

const unsigned char no_database_bitmap [] PROGMEM = {
	0x8f, 0xf0, 0xc0, 0x0c, 0x60, 0x02, 0x70, 0x06, 0x78, 0xfe, 0x4c, 0x02, 0x46, 0x02, 0x7b, 0x1e, 
	0x4f, 0x82, 0x40, 0x42, 0x40, 0x32, 0x7f, 0xf8, 0x41, 0x9c, 0x40, 0x06, 0x30, 0x1f, 0x0f, 0xf1
};

const Bitmap no_database = {no_database_bitmap, 16, 16};

const unsigned char white_bit [] PROGMEM = {
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};

const Bitmap white = {white_bit, 32, 32};

// 'block', 32x32px
const unsigned char block_bitmap [] PROGMEM = {
	0x00, 0x0f, 0xf0, 0x00, 0x00, 0x7f, 0xfe, 0x00, 0x01, 0xff, 0xff, 0x80, 0x03, 0xff, 0xff, 0xc0, 
	0x07, 0xe0, 0x07, 0xe0, 0x0f, 0x80, 0x03, 0xf0, 0x1f, 0x00, 0x07, 0xf8, 0x3e, 0x00, 0x0f, 0xfc, 
	0x3c, 0x00, 0x1f, 0xfc, 0x78, 0x00, 0x3f, 0xfe, 0x78, 0x00, 0x7f, 0xde, 0x70, 0x00, 0xff, 0x8e, 
	0xf0, 0x01, 0xff, 0x0f, 0xf0, 0x03, 0xfe, 0x0f, 0xf0, 0x07, 0xfc, 0x0f, 0xf0, 0x0f, 0xf8, 0x0f, 
	0xf0, 0x1f, 0xf0, 0x0f, 0xf0, 0x3f, 0xe0, 0x0f, 0xf0, 0x7f, 0xc0, 0x0f, 0xf0, 0xff, 0x80, 0x0f, 
	0x71, 0xff, 0x00, 0x0e, 0x7b, 0xfe, 0x00, 0x1e, 0x7f, 0xfc, 0x00, 0x1e, 0x3f, 0xf8, 0x00, 0x3c, 
	0x3f, 0xf0, 0x00, 0x7c, 0x1f, 0xe0, 0x00, 0xf8, 0x0f, 0xc0, 0x01, 0xf0, 0x07, 0xe0, 0x07, 0xe0, 
	0x03, 0xff, 0xff, 0xc0, 0x01, 0xff, 0xff, 0x80, 0x00, 0x7f, 0xfe, 0x00, 0x00, 0x0f, 0xf0, 0x00
};
const Bitmap block = {block_bitmap, 32, 32};


#endif