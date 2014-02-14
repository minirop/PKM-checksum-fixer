#include <stdio.h>
#include <stdlib.h>

void fix_checksum(const char * filename);

int main(int argc, char ** argv)
{
	if(argc < 2)
	{
		printf("Usage: pkmcs file.pkm [file2.pkm ...]\n");
		return 1;
	}
	
	for(int i = 1;i < argc;i++)
	{
		fix_checksum(argv[i]);
	}
	
	return 0;
}

void fix_checksum(const char * filename)
{
	FILE * file = fopen(filename, "r+b");
	
	fseek(file, 0x08, SEEK_SET);
	
	int sum = 0;
	for(int i = 0x08;i < 0x88;i+=2)
	{
		int x = 0;
		
		fread(&x, 2, 1, file);
		
		sum += x;
	}
	
	sum &= 0xFFFF;
	
	fseek(file, 0x06, SEEK_SET);
	fwrite(&sum, 2, 1, file);
	
	fclose(file);
}
