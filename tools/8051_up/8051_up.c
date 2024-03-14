/**
  ******************************************************************************
  * @file       8051_up.c
  * @brief      用于固件加载并启动8051 Load firmware && Start up the 8051 core
  * @note       Modified by milkv@rjgawuie
  *
  @verbatim
  ==============================================================================

  ==============================================================================
  @endverbatim
  ******************************************************************************
  */

#include "devmem.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define RTC_SRAM_BASE 0x05200000

#define MCU_FW_PATH "/lib/firmware/mars_mcu_fw.bin"


uint32_t boot_addr = RTC_SRAM_BASE;		//Boot from SRAM by default

void get_boot_addr(const char *filename)
{
	FILE *file = fopen(filename, "rb");
	char tmp[100] = {0};
	char *ret = NULL;
	if (file == NULL) 
	{
		printf("No config file, use default boot address.\n");
		return;
    } 
	else 
	{
		ret = fgets(tmp, sizeof(tmp), file);
		if (ret != NULL)
		{
			sscanf(tmp,"%x",&boot_addr);
			printf("8051 will boot on address %x\n",boot_addr);
		}
		else
			printf("wrong param,boot address %x\n",boot_addr);
	}
}

int load_file_to_memory(const char *filename, char **result)
{
	int size = 0;
	FILE *f = fopen(filename, "rb");
	if (f == NULL)
	{
		*result = NULL;
		return -1; // -1 means file opening fail
	}
	fseek(f, 0, SEEK_END);
	size = ftell(f);
	fseek(f, 0, SEEK_SET);
	*result = (char *)malloc(size+1);
	if (size != fread(*result, sizeof(char), size, f))
	{
		free(*result);
		return -2; // -2 means file reading fail
	}
	fclose(f);
	(*result)[size] = 0;
	return size;
}

void trigger_8051()
{
	uint32_t reg;
	reg = boot_addr;
	reg &= 0xFFFFF000;
	reg |= 0x084;
	devmem_writel(0x03000248, 0x1);
	devmem_writel(0x05025020, reg);
	devmem_writel(0x05025018, 0x8107ffff);
	return;
}

int main(int argc, char *argv[])
{
	char *content;
	int size;
	int i;
	unsigned int value;

	get_boot_addr("8051_boot_cfg.ini");

	if((access(MCU_FW_PATH, F_OK)) != -1) {
        printf("load mcu fw: %s\n", MCU_FW_PATH);
        size = load_file_to_memory(MCU_FW_PATH, &content);
	} else {
		size = load_file_to_memory("mars_mcu_fw.bin", &content);
	}

	if (size < 0) {
		puts("Error loading file");
		return 1;
	}

	printf("size = %d\n", size);
	i = 0;

	devmem_writel(0x05025018, 0x8107fffd);			//reset8051

	do {
		value = (unsigned char)content[i] +
				((unsigned char)content[i + 1] << 8) +
		        ((unsigned char)content[i + 2] << 16) +
				((unsigned char)content[i + 3] << 24);

		devmem_writel(boot_addr + i, value);

		i += 4;
	} while(i < size);

	free(content);

	trigger_8051();

	printf("done\n");
	return 0;
}
