#pragma once

class Memory {
private:
	unsigned long hPID;

public:
	bool Process(char*);
	template <class cData> cData Read(unsigned long);
	template <class cData> void Write(unsigned long, cData);
	unsigned long getPID();
};

extern Memory *gMemory;
