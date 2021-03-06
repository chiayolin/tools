/*
 * dtob - dtob.c
 * Binary to Decimal and Decimal to Binary Converter
 * Copyright (C) 2014  Chiayo Lin <chiayo.lin@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define MAX 1000

int getaton(int array[MAX]); /* Read ASCII numbers into an array, convert to numbers, return size */
int btod(int binary[MAX], const int size); /* Convert Bin. to Dec. */
int dtob(int decimal, int binary[MAX]); /* Convert Dec. to Bin. */
void printa(const int array[MAX], const int size); /* Print an array */
void reverse(int array[MAX], const int size); /* Reverse an array */
void interactive(); /* Interactive mode */
void help(int type); /* Print help messages base on the varible 'type' */
void info(); /* Print information about this program */

int main(const int argc, char *argv[]) {
	int binary[MAX], decimal;
	int size;
	
	/* Enter interactive mode if there are no command line options */
	if(argc == 1) {
		interactive();
	} 
	
	/* Read the options if argv[0][0] = '-' */
	else if((*++argv)[0] == '-') {
		int binary[MAX], decimal, size;
		char opt = *++argv[0];
		switch(opt) {
			case 'd':
				if(argv[1] == NULL)
					printf("agument to '-%s' is missing, expected a decimal number\n", argv[0]);
				else {
					decimal = atoi(argv[1]);
					size = dtob(decimal, binary);
					printa(binary, size);
				}
				break;

			case 'b':
				if(argv[1] == NULL)
					printf("agument to '-%s' is missing, expected a binary number\n", argv[0]);
				else {
					size = strlen(argv[1]);
					int i;
					for(i = 0; i < size; i++)
						binary[i] = argv[1][i] - '0'; 
					decimal = btod(binary, size);
					printf("%d\n", decimal);
				}
				break;

			case 'h':
				help(1);
				break;

			case 'i':
				interactive();
				break;

			case 'm':
				info();
				break;

			default:
				 printf("dtob: alas, invalid option '-%s' \n", argv[0]);
				 help(0);
				 break;
		}
	}
	
	/* Else, print the error message */
	else {
		printf("dtob: alas, syntax error :-(\n");
		help(0);
		return 1;
	}
			
	return 0;
}	

int dtob(int decimal, int binary[MAX]) {
	int i, size;
	if(decimal == 0) {
		binary[0] = 0;
		return 1;
	} /* To fix decimal = 0 prints a blank */

	for(i = 0, size = 0; decimal != 0; i++, size++) {
		binary[i] = decimal % 2;
		decimal = decimal / 2;
	}
	reverse(binary, size);

	return size; /* Return the size of array */
}

int btod(int binary[MAX], const int size) {
	int i, decimal;
	i = decimal = 0;

	reverse(binary, size);
	for(i = 0; i < size; i++)
		decimal = decimal + (binary[i] * (pow(2, i)));

	return decimal;
}

int getaton(int array[MAX]) {
	int i, c, size;
	getchar(); /* To avoid a return '\n' */

	while((c = getchar()) != '\n') {                                                                                                                             
		array[i] = c - '0'; /* Convert ASCII to interger */
		++i, ++size;
	}
	return size;
}

void printa(const int array[MAX], const int size) {
	int i;
	for(i = 0; i < size; i++)
		printf("%d", array[i]);
	printf("\n");
}

void reverse(int array[MAX], const int size) {
	int temp[MAX], i;
	for(i = 0; i < size; i++)
		temp[i] = array[i]; /* Copy array into a buffer */
	int j;
	for(i = 0, j = size - 1; j >= 0; i++, j--)
		array[i] = temp[j];
}

void interactive() {
	int binary[MAX], decimal, size;

	printf("use h for help\n");
	while(1) {
		printf(">>> ");

		char option;
		scanf("%c", &option);
		switch(option) {
			case 'd': case 'D':
				scanf("%d", &decimal);
				size = dtob(decimal, binary);
				printa(binary, size);
				break;

			case 'b': case 'B':
				size = getaton(binary);
				decimal = btod(binary, size);
				printf("%d\n", decimal);
				break;

			case 'h': case 'H':
				help(2);
				break;
		
			case 'q': case 'Q':
				return;
				break;

			case 'm': case 'M':
				info();
				break;
	
			default:
				if(option == '\n') break;
				else printf("unfortunately, '%c' is not an option\n", option);
				break;
		}
		if(option != '\n' && option != 'b') getchar(); /* Trick to avoid scan a return, '\n' */
	}
}

void help(int type) {
	const char h[] = "print this usage and text\n",
	    	   d[] = "convert decimal to binary\n",
	    	   b[] = "convert binary to decimal\n",
	    	   i[] = "force enter interactived mode\n",
	    	   m[] = "more info about this program\n";

	switch(type) {
		case 0:
			printf("use dtob -h for help\n");
			break;
		case 1:
			printf("usage: dtob [options] [value ...]\n");
			printf("  -h      %s", h);
			printf("  -d      %s", d);
			printf("  -b      %s", b);
			printf("  -i      %s", i);
			printf("  -m      %s", m);
			break;

		case 2:
			printf("list of options:\n");
			printf("  h    %s", h);
			printf("  d    %s", d);
			printf("  b    %s", b);
			printf("  m    %s", m);
			printf("  q    quit\n");
			break;
	}
}

void info() {
	printf("dtob (Version 1.0) Copyrights (C) 2014 Chiayo Lin\n");
	printf("Binary to Decimal and Decimal to Binary Converter\n\n");
	printf("Source Code: <http://github.com/chiayolin/atob/>\n");
	printf("Author     : Chiayo Lin <chiayo.lin@gmail.com>\n\n");
	printf("License:\n");
	printf("  This program comes with ABSOLUTELY NO WARRANTY.\n");
	printf("  This is free software, and you are welcome to \n");
	printf("  redistribute it under the terms of GPL v3.0.\n");
	printf("  <http://www.gnu.org/licenses/>\n\n");
}
