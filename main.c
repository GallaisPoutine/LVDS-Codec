// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (C) 2020, STMicroelectronics - All Rights Reserved
 * Author(s): Raphaël GALLAIS-POU <raphael.gallais-pou@st.com> for STMicroelectronics.
 * gcc -DDSKW_TOGGLE main.c
 */

#include<stdio.h>
#include<stdlib.h>

#include "lvds.h"

int LVDS_Decode(int reg, int *bitmap, int lsb)
{
/*        int bitmap[7];*/

        if (reg > 0xFFFFF || reg < 0x0)
                return 1;
        if (!((lsb == 0) || (lsb == 1)))
                return 1;

/*        printf("%08x\n", (BIT_0_Msk));*/
/*        printf("%08x\n", (reg & BIT_0_Msk) >> BIT_0_Pos);*/

        if (!lsb)
        {
                bitmap[0] = ((reg & BIT_0_Msk) >> BIT_0_Pos);
                bitmap[1] = ((reg & BIT_1_Msk) >> BIT_1_Pos);
                bitmap[2] = ((reg & BIT_2_Msk) >> BIT_2_Pos);
        } else {

                bitmap[3] = ((reg & BIT_3_Msk) >> BIT_3_Pos);
                bitmap[4] = ((reg & BIT_4_Msk) >> BIT_4_Pos);
                bitmap[5] = ((reg & BIT_5_Msk) >> BIT_5_Pos);
                bitmap[6] = ((reg & BIT_6_Msk) >> BIT_6_Pos);
        }

        return 0;
}

int LVDS_Convert(int bit, char *str)
{
        switch (bit)
        {
        case HAL_LVDS_MAP_R_0:          str = "<R0>";           break;
        case HAL_LVDS_MAP_R_1:          str = "<R1>";           break;
        case HAL_LVDS_MAP_R_2:          str = "<R2>";           break;
        case HAL_LVDS_MAP_R_3:          str = "<R3>";           break;
        case HAL_LVDS_MAP_R_4:          str = "<R4>";           break;
        case HAL_LVDS_MAP_R_5:          str = "<R5>";           break;
        case HAL_LVDS_MAP_R_6:          str = "<R6>";           break;
        case HAL_LVDS_MAP_R_7:          str = "<R7>";           break;
        case HAL_LVDS_MAP_G_0:          str = "<G0>";           break;
        case HAL_LVDS_MAP_G_1:          str = "<G1>";           break;
        case HAL_LVDS_MAP_G_2:          str = "<G2>";           break;
        case HAL_LVDS_MAP_G_3:          str = "<G3>";           break;
        case HAL_LVDS_MAP_G_4:          str = "<G4>";           break;
        case HAL_LVDS_MAP_G_5:          str = "<G5>";           break;
        case HAL_LVDS_MAP_G_6:          str = "<G6>";           break;
        case HAL_LVDS_MAP_G_7:          str = "<G7>";           break;
        case HAL_LVDS_MAP_B_0:          str = "<B0>";           break;
        case HAL_LVDS_MAP_B_1:          str = "<B1>";           break;
        case HAL_LVDS_MAP_B_2:          str = "<B2>";           break;
        case HAL_LVDS_MAP_B_3:          str = "<B3>";           break;
        case HAL_LVDS_MAP_B_4:          str = "<B4>";           break;
        case HAL_LVDS_MAP_B_5:          str = "<B5>";           break;
        case HAL_LVDS_MAP_B_6:          str = "<B6>";           break;
        case HAL_LVDS_MAP_B_7:          str = "<B7>";           break;
        case HAL_LVDS_MAP_H_S:          str = "<HS>";           break;
        case HAL_LVDS_MAP_V_S:          str = "<VS>";           break;
        case HAL_LVDS_MAP_D_E:          str = "<DE>";           break;
        case HAL_LVDS_MAP_C_E:          str = "<CE>";           break;
        case HAL_LVDS_MAP_C_I:          str = "<CI>";           break;
        case HAL_LVDS_MAP_TOG:          str = "<TO>";           break;
        case HAL_LVDS_MAP_ONE:          str = "<01>";           break;
        case HAL_LVDS_MAP_ZER:          str = "<00>";           break;
        default:                                                break;
        }

        return 0;
}

int main(int argc, char **argv)
{
	int bitmap[7] = {0};
        char* str=0;

/*        if (argc != 2)*/
/*                return 1;*/

/*        int reg = (int)strtol(argv[1], NULL, HEX_BASE);*/
/*        printf("%d\n", reg);*/

        // JEIDA-RGB888 DL0 :   G2 R7 R6 R5 R4 R3 R2
        //                      0A 07 06 05 04 03 02
        LVDS_Decode(0x000028E6, &bitmap, 0);
        LVDS_Decode(0x00029062, &bitmap, 1);

        for (int i=0; i<7; i++)
        {
                printf("%d %d\n", bitmap[i], HAL_LVDS_MAP_G_2);
                LVDS_Convert(bitmap[i], str);
                printf("%s", str);
        }

        printf("%02x %02x %02x %02x %02x %02x %02x\n",
               bitmap[0], bitmap[1], bitmap[2], bitmap[3], bitmap[4], bitmap[5], bitmap[6]);

	return 0;
}
