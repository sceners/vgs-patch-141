//-----------------------------------------------------
#ifndef	_CRC32_H
#define	_CRC32_H
//-----------------------------------------------------
#define CRC32poly		0xEDB88320L
/*First you must run InitCRC32 to generate XOR table.*/
void __stdcall InitCRC32(void);
/*
Before generate your CRC, you must run CRC32 with initvalue 0xFFFFFFFF
After generate your CRC of all data frames, the return value must by XORed
by 0xFFFFFFFF.
*/
unsigned long __stdcall CRC32(unsigned long,void *,unsigned int);
//-----------------------------------------------------
#endif
//-----------------------------------------------------