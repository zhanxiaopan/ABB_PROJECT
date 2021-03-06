/*
 * This is to generate MAC randomly and store the result in EEPROM.
 */
#include "RandomMAC.h"
#include "hw_sysctl.h"

#include "bsp_eeprom_const.h"

#include <stdio.h>

/* 'M', 'A', 'C', '!'*/
#define EEPROM_FLAG_MAC_EXIST (0x4D434121)

/* 
 * Here we utilize the "trick" that those l_mac* would be stored
 * in consecutive memory in most C compilers.
 * That means: &l_mac1 = &l_mac0 + 1, &l_mac2 = &l_mac1 + 1, ...
 * To avoid memory leak, l_mac6, l_mac7 is also defined as placeholder.
*/
uint8_t mac_ready = 0;

/**
 * The bytes n.o. 0-5 for MAC
 */
uint8_t MAC0;
uint8_t MAC1;
uint8_t MAC2;
uint8_t MAC3;
uint8_t MAC4;
uint8_t MAC5;

/**
 * This func should be called earlier than 
 * the initialization of Ethernet! 
 * 
 * It generates or restores the MAC.
 */
void gen_mac_addr() {
    if(!mac_ready) {
        uint8_t l_mac[8];
        uint32_t flag_mac_exist = 0;
        EEPROMRead ((uint32_t*)&flag_mac_exist, EEPROM_ADDR_MAC_EXIST, 4);

        // Check whether mac exist already and then read or generate mac addr accordingly.
        if (flag_mac_exist == EEPROM_FLAG_MAC_EXIST) {
            // MAC is set already. Read it from EEPROM
            EEPROMRead ((uint32_t*)&l_mac[0], EEPROM_ADDR_MAC0, 8);
        }
        else {
            // No mac generated for this board yet

			//The first three bytes should be fixed 
			//otherwise, the Profinet IP addr config 
			//may fail!! 
            l_mac[0] =  0x00;
            l_mac[1] =  0x1A;
            l_mac[2] =  0xB6;
            
            // seed the rng with adc noise
            rng_seed();
            l_mac[3] = rng_rand_byte();
            l_mac[4] = rng_rand_byte();
            l_mac[5] = rng_rand_byte();

			//save the generated MAC addr in the EEPROM
            flag_mac_exist = EEPROM_FLAG_MAC_EXIST;
            EEPROMProgram ((uint32_t*)&flag_mac_exist, EEPROM_ADDR_MAC_EXIST, 4);
            EEPROMProgram ((uint32_t*)&l_mac[0], EEPROM_ADDR_MAC0, 8);
        }
        mac_ready = 1;

        MAC0 = l_mac[0];
        MAC1 = l_mac[1];
        MAC2 = l_mac[2];
        MAC3 = l_mac[3];
        MAC4 = l_mac[4];
        MAC5 = l_mac[5];
    }
}
