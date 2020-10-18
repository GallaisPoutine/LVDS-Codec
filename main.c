// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (C) 2020, STMicroelectronics - All Rights Reserved
 * Author(s): Raphaël GALLAIS-POU <raphael.gallais-pou@st.com> for STMicroelectronics.
 */

#include<stdio.h>
#include<stdlib.h>

#define HEX_BASE	16

int main(int argc, char **argv)
{
	if (argc != 2)
		return 1;

	int reg = (int)strtol(argv[1], NULL, HEX_BASE);
	printf("%d\n", reg);
	return 0;
}
