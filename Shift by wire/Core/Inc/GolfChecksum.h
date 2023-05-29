#ifndef GOLFCHECKSUM_H
#define GOLFCHECKSUM_H

#include "main.h"


void gen_crc_lookup_table(uint8_t poly, uint8_t crc_lut[]);
void init_crc_lookup_tables(void);
uint8_t volkswagen_crc(unsigned int address, uint64_t d, int l);
uint32_t toyota_compute_checksum(uint8_t * data ,uint8_t lenght,int ID);

uint8_t toyota_checksum(uint32_t address, uint64_t d, uint8_t lenght);








#endif

