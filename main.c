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
        if (reg > 0xFFFFF || reg < 0x0)
                return 1;
        if (!((lsb == 0) || (lsb == 1)))
                return 1;

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

int LVDS_DecodeLane(int lsbreg, int msbreg, int *bitmap, char *lane)
{
        char str[5] = {0};

	LVDS_Decode(msbreg, bitmap, 0);
        LVDS_Decode(lsbreg, bitmap, 1);

        for (int i=0; i<7; i++)
        {
                LVDS_Convert(bitmap[i], str);
                snprintf(lane + i*4*sizeof(char), 5, "%s", str);
        }

	return 0;
}

int LVDS_Convert(int bit, char *str)
{
        switch (bit)
        {
        case HAL_LVDS_MAP_R_0:          snprintf(str, 5, "<R0>");           break;
        case HAL_LVDS_MAP_R_1:          snprintf(str, 5, "<R1>");           break;
        case HAL_LVDS_MAP_R_2:          snprintf(str, 5, "<R2>");           break;
        case HAL_LVDS_MAP_R_3:          snprintf(str, 5, "<R3>");           break;
        case HAL_LVDS_MAP_R_4:          snprintf(str, 5, "<R4>");           break;
        case HAL_LVDS_MAP_R_5:          snprintf(str, 5, "<R5>");           break;
        case HAL_LVDS_MAP_R_6:          snprintf(str, 5, "<R6>");           break;
        case HAL_LVDS_MAP_R_7:          snprintf(str, 5, "<R7>");           break;
        case HAL_LVDS_MAP_G_0:          snprintf(str, 5, "<G0>");           break;
        case HAL_LVDS_MAP_G_1:          snprintf(str, 5, "<G1>");           break;
        case HAL_LVDS_MAP_G_2:          snprintf(str, 5, "<G2>");           break;
        case HAL_LVDS_MAP_G_3:          snprintf(str, 5, "<G3>");           break;
        case HAL_LVDS_MAP_G_4:          snprintf(str, 5, "<G4>");           break;
        case HAL_LVDS_MAP_G_5:          snprintf(str, 5, "<G5>");           break;
        case HAL_LVDS_MAP_G_6:          snprintf(str, 5, "<G6>");           break;
        case HAL_LVDS_MAP_G_7:          snprintf(str, 5, "<G7>");           break;
        case HAL_LVDS_MAP_B_0:          snprintf(str, 5, "<B0>");           break;
        case HAL_LVDS_MAP_B_1:          snprintf(str, 5, "<B1>");           break;
        case HAL_LVDS_MAP_B_2:          snprintf(str, 5, "<B2>");           break;
        case HAL_LVDS_MAP_B_3:          snprintf(str, 5, "<B3>");           break;
        case HAL_LVDS_MAP_B_4:          snprintf(str, 5, "<B4>");           break;
        case HAL_LVDS_MAP_B_5:          snprintf(str, 5, "<B5>");           break;
        case HAL_LVDS_MAP_B_6:          snprintf(str, 5, "<B6>");           break;
        case HAL_LVDS_MAP_B_7:          snprintf(str, 5, "<B7>");           break;
        case HAL_LVDS_MAP_H_S:          snprintf(str, 5, "<HS>");           break;
        case HAL_LVDS_MAP_V_S:          snprintf(str, 5, "<VS>");           break;
        case HAL_LVDS_MAP_D_E:          snprintf(str, 5, "<DE>");           break;
        case HAL_LVDS_MAP_C_E:          snprintf(str, 5, "<CE>");           break;
        case HAL_LVDS_MAP_C_I:          snprintf(str, 5, "<CI>");           break;
        case HAL_LVDS_MAP_TOG:          snprintf(str, 5, "<TO>");           break;
        case HAL_LVDS_MAP_ONE:          snprintf(str, 5, "<01>");           break;
        case HAL_LVDS_MAP_ZER:          snprintf(str, 5, "<00>");           break;
        default:				                            break;
        }

        return 0;
}

int main(int argc, char **argv)
{
	int	bitmap[7]	= {0};
	char	lane[36]	= {0};

	if (argc != 3)
	{
		printf("./a.out lsbreg msbreg\n");
		printf("Example :\n");
		printf("./a.out 0x000FFFDE 0x00007BDF\n");
		return 1;
	}

	int lsbreg = (int)strtol(argv[1], NULL, HEX_BASE);
	int msbreg = (int)strtol(argv[2], NULL, HEX_BASE);

	LVDS_DecodeLane(lsbreg, msbreg, bitmap, lane);

	printf("%s\n", lane);
        printf(" %02x  %02x  %02x  %02x  %02x  %02x  %02x\n",
               bitmap[0], bitmap[1], bitmap[2], bitmap[3], bitmap[4], bitmap[5], bitmap[6]);

	return 0;
}
