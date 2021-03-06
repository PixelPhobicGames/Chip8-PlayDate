#include "Screen.h"

#define FontSetSize 80

const unsigned char FontSet[80] = {
	0xF0, 0x90, 0x90, 0x90, 0xF0,		
	0x20, 0x60, 0x20, 0x20, 0x70,		
	0xF0, 0x10, 0xF0, 0x80, 0xF0,		
	0xF0, 0x10, 0xF0, 0x10, 0xF0,		
	0x90, 0x90, 0xF0, 0x10, 0x10,	
	0xF0, 0x80, 0xF0, 0x10, 0xF0,	
	0xF0, 0x80, 0xF0, 0x90, 0xF0,	
	0xF0, 0x10, 0x20, 0x40, 0x40,	
	0xF0, 0x90, 0xF0, 0x90, 0xF0,	
	0xF0, 0x90, 0xF0, 0x10, 0xF0,	
	0xF0, 0x90, 0xF0, 0x90, 0x90,	
	0xE0, 0x90, 0xE0, 0x90, 0xE0,
	0xF0, 0x80, 0x80, 0x80, 0xF0,
	0xE0, 0x90, 0x90, 0x90, 0xE0,		
	0xF0, 0x80, 0xF0, 0x80, 0xF0,	
	0xF0, 0x80, 0xF0, 0x80, 0x80		
};

void LoadRom(const char *Path){
	int FileSize = 0;
	SDFile* Rom = NULL;	
	Rom = PD->file->open(Path, kFileRead);

	PD->file->seek(Rom, 0, SEEK_END);
	FileSize = PD->file->tell(Rom);
    PD->file->seek(Rom, 0, SEEK_SET);

	PD->file->read(Rom, SystemMemory + 0x200, FileSize);

	if (Rom != NULL){
		PD->system->logToConsole("Loaded Rom Successfully \n");
		RomLoaded = true;
	}
	else {
		PD->system->logToConsole("Rom Failed To Load \n");
	}
	
	PD->file->close(Rom);
}

void LoadCustomRom(const char *Path){
	PD->file->mkdir("Roms Go Here!");
	int FileSize = 0;
	SDFile* Rom = NULL;	
	Rom = PD->file->open(Path, kFileReadData);

	PD->file->seek(Rom, 0, SEEK_END);
	FileSize = PD->file->tell(Rom);
    PD->file->seek(Rom, 0, SEEK_SET);

	PD->file->read(Rom, SystemMemory + 0x200, FileSize);

	if (Rom != NULL){
		PD->system->logToConsole("Loaded Rom Successfully \n");
		RomLoaded = true;
	}
	else {
		PD->system->logToConsole("Rom Failed To Load \n");
	}
	
	PD->file->close(Rom);
}


LCDBitmap *LoadPng(const char *Path)
{
	const char *Error = NULL;
	LCDBitmap *Image = PD->graphics->loadBitmap(Path, &Error);
	return Image;
}


void InitMemory(){
	memset(SystemMemory , 0 , sizeof(SystemMemory));
	memset(SystemStack , 0 , sizeof(SystemStack));
	memset(SystemRegisters , 0 , sizeof(SystemRegisters));

    SystemIRegister = 0x00;
    SystemProgramCounter = 0x200; // Sets it to 512 Where Rom Starts 
	SystemKey = 0;

    for (int i = 0; i < FontSetSize; i++) {
		SystemMemory[i] = FontSet[i];
	}
}

