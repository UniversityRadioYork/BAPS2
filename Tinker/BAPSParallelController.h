#pragma once

short _stdcall Inp32(short PortAddress);
void _stdcall Out32(short PortAddress, short data);

class BAPSParallelController
{

public:
/*
Register							LPT1	LPT2 
data registar(baseaddress + 0)		0x378	0x278 
status register (baseaddress + 1)	0x379	0x279 
control register (baseaddress + 2)	0x37a	0x27a 
*/
	static int ReadParallelPortPin(int pin)
	{
		//reading the port by I/O address. This may not always be correct, but SHOULD be LPT1 on most machines.
		//Its possible to find the LPT1 address and then give that. How?
		
		Out32(890,32); //set bidirectional bit so we can read the data lines into the register

		int data=Inp32(888); 

		//this section returns the value of the requested data pin, which will be converted to a boolean
		return data;
		switch (pin)
		{
		case 0:
			return data & 128;
			break;
		case 1:
			return data & 64;
			break;
		case 2:
			return data & 32;
			break;
		case 3:
			return data & 16;
			break;
		case 4:
			return data & 8;
			break;
		case 5:
			return data & 4;
			break;
		case 6:
			return data & 4;
			break;
		case 7:
			return data & 1;
			break;
		default:
			return false;
			break;
		}
	}

	static bool WriteParallelPortPin(short data)
	{
		Out32(888,data);
		return false; //cos this currently does jack all.

	}
};