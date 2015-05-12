/*
 * parseFormula.c
 *
 *  Created on: 2015/04/30
 *      Author: hikozuma
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(){

	//printf("abcdefg");

	char inputFormulaArr[50] = "1 + 22 + 333 - 4444 - 555";
	int numArr[50];
	char signArr[50];
	char inputNumArr[50];

	int ans = 0;

	int i, j = 0, k = 0, l = 0;

	//printf("%s\n", "abcde");
	//fgets(inputFormulaArr,50, stdin);

	for(i = 0; inputFormulaArr[i] != '\0'; i++){

		switch (inputFormulaArr[i]){
			case '+':
			case '-':
			case '*':
			case '/':

				//number
				numArr[l] = atoi(inputNumArr[j]);
				l++;

				//sign
				signArr[k] = inputFormulaArr[i];
				k++;

				//initilize
				for(j = 0; j < 50; j++){
					inputNumArr[j] = '\0';
				}

				j = 0;

				break;

			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				inputNumArr[j] = inputFormulaArr[i];
				j++;

				break;

			case ' ':
				//number
				numArr[l] = atoi(inputNumArr[j]);
				l++;

				//initilize
				for(j = 0; j < 50; j++){
					inputNumArr[j] = '\0';
				}

				j = 0;

				break;
		}
	}

	ans = numArr[0];
	//k = 0;

	for(i = 1, k = 0; i < 50; i++){

		if(signArr[k] == '*'){
			ans *= numArr[i];

			//slide num, sign Array
			break;

		}else if(signArr[k] == '/'){
			ans /= numArr[i];

			//slide num, sign Array
			break;
		}
	}


	for(i = 1, k = 0; i < 50; i++){

		switch(signArr[k]){
			case '+':
				ans += numArr[i];
				break;

			case '-':
				ans -= numArr[i];
				break;
		}
	}


	return 0;
}

