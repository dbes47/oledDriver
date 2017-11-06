#ifndef __OLEDDRIVER_H__
#define __OLEDDRIVER_H__

#include <Arduino.h>
#include <TinyWireM.h>
#include <USI_TWI_Master.h>
#include <avr/pgmspace.h>

//Our Fonts

//5x8 Font
const unsigned char our5x8Font[] PROGMEM = {
	0x3E, 0x51, 0x49, 0x45, 0x3E, // 0  \x30 0
	0x00, 0x42, 0x7F, 0x40, 0x00, // 1  \x31 1
	0x72, 0x49, 0x49, 0x49, 0x46, // 2  \x32 2
	0x21, 0x41, 0x49, 0x4D, 0x33, // 3  \x33 3
	0x18, 0x14, 0x12, 0x7F, 0x10, // 4  \x34 5
	0x27, 0x45, 0x45, 0x45, 0x39, // 5  \x35 6
	0x3C, 0x4A, 0x49, 0x49, 0x31, // 6  \x36 7
	0x41, 0x21, 0x11, 0x09, 0x07, // 7  \x37 8
	0x36, 0x49, 0x49, 0x49, 0x36, // 8  \x38 9
	0x46, 0x49, 0x49, 0x29, 0x1E, // 9	\x39 10
	0x7C, 0x12, 0x11, 0x12, 0x7C, // A  \x41 11
	0x7F, 0x49, 0x49, 0x49, 0x36, // B  \x42 12
	0x3E, 0x41, 0x41, 0x41, 0x22, // C  \x43 13
	0x7F, 0x41, 0x41, 0x41, 0x3E, // D  \x44 14
	0x7F, 0x49, 0x49, 0x49, 0x41, // E  \x45 15
	0x7F, 0x09, 0x09, 0x09, 0x01, // F  \x46 16
	0x3E, 0x41, 0x41, 0x51, 0x73, // G  \x47 17
	0x7F, 0x08, 0x08, 0x08, 0x7F, // H  \x48 18
	0x00, 0x41, 0x7F, 0x41, 0x00, // I  \x49 19
	0x20, 0x40, 0x41, 0x3F, 0x01, // J  \x4a 20
	0x7F, 0x08, 0x14, 0x22, 0x41, // K  \x4b 21
	0x7F, 0x40, 0x40, 0x40, 0x40, // L  \x4c 22
	0x7F, 0x02, 0x1C, 0x02, 0x7F, // M  \x4d 23
	0x7F, 0x04, 0x08, 0x10, 0x7F, // N  \x4e 24
	0x3E, 0x41, 0x41, 0x41, 0x3E, // O  \x4f 25
	0x7F, 0x09, 0x09, 0x09, 0x06, // P  \x50 26
	0x3E, 0x41, 0x51, 0x21, 0x5E, // Q  \x51 27
	0x7F, 0x09, 0x19, 0x29, 0x46, // R  \x52 28
	0x26, 0x49, 0x49, 0x49, 0x32, // S  \x53 29
	0x03, 0x01, 0x7F, 0x01, 0x03, // T  \x54 30
	0x3F, 0x40, 0x40, 0x40, 0x3F, // U  \x55 31
	0x1F, 0x20, 0x40, 0x20, 0x1F, // V  \x56 32
	0x3F, 0x40, 0x38, 0x40, 0x3F, // W  \x57 33
	0x63, 0x14, 0x08, 0x14, 0x63, // X  \x58 34
	0x03, 0x04, 0x78, 0x04, 0x03, // Y  \x59 35
	0x61, 0x59, 0x49, 0x4D, 0x43, // Z  \x5a 36
	0x00, 0x00, 0x14, 0x00 ,0x00, // :   \x3a 37
	0x00, 0xfe, 0x03, 0xfe, 0x50, // Thermometer 38
	0x00, 0xff, 0x00, 0xff, 0x55, // Thermometer 39
	0x60, 0x9f, 0x80, 0x9f, 0x65 // Thermometer 40
};

//#defines for dislplay convinience
#define homeDateStartLoc 0x2F //47
#define homeYearStartLoc 0x35 //53
//Arrow Sprites

//#defines

//Slave address
#define SlaveAddress 						0x3c

//Commands
#define commandMode 						0x80
#define dataMode 							0x40

//Hardware setup commands
#define setContrastControl 					0x81 		//Contrast from 0-0xFF
#define entireDisplayOn 					0xA5
#define resumeDisplayToRAM 					0xA4
#define enableInversion 					0xA7
#define disableInversion 					0xA6
#define setDisplayOn 						0xAF 		//use for wake up from sleep mode
#define setDisplaySleep 					0xAE 		//put to sleep Mode for power saving

//Addressing mode commands
#define setMemoryAddressingMode 			0x20
#define horizontalMode 						0x00
#define verticalMode 						0x01
#define setColumnAddress 					0x21
#define setPageAddress 						0x22
#define setMuxRatio 						0xA8		//0d-63d
#define setDisplayOffset 					0xD3		//0-63d

#define setCOMOutputScanDirectionNormal 	0xC0
#define setCOMOutputScanDirectionRemapped 	0xC8
#define setCOMHardwareConfig 				0xDA		//Use 0x12 for our Display
#define setClockDivider 					0xD5		//Use 0xF0 for fast updates and 0x80 is tested
#define setPrechargePeriod 					0xD9
#define setVCOMHDeselectLevel 				0xDB

//Scrolling mode commands
#define rightHorizontalScroll           	0x26
#define leftHorizontalScroll            	0x27
#define verticalRightHorizontalScroll  		0x29
#define verticalLeftHorizontalScroll   		0x2A
#define activateScrollCmd                   0x2F
#define deactivateScroll                 	0x2E
#define setVerticalScrollArea          		0xA3


//Charge Pump Settings
#define setChargePumpSetting 				0x8D
#define enableChargePump 					0x14
#define disableChargePump 					0x10

//#defines for sprires
#define numberOffset5x8Font					0x0A

//Class Declaration

class oledDriver {
public:
	//Initialises the OLED
	void init();

	//Send one command 
	void sendCommand(char);

	//Send one byte of data
	void sendData(char);

	//Send an arrey of data
	void sendDataArray(char*,int);

	//Generic Test funcion for Display
	void displayFill();

	//Dsplay the time given (incomplete)
	void displayTime(uint8_t, uint8_t);

	//Fill the screen with all zeroes
	void clearScreen();

	///Select area to be changed
	void setAreaToUpdate(char, char, char, char);

	//Display Character at given location
	void display5x8Char(unsigned char, char, char);

	//The time displaying home screen
	void displayHome();

	//Display the Tempretute and Pressure screen
	void displayTempPressure();

	//Display Line on center of the Page
	void displayLine(char);
	
	//horizontal Line
	void horizontalLine(char);
	
};

#endif