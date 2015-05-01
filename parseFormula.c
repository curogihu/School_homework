/*
 * parseFormula.c
 *
 *  Created on: 2015/04/30
 *      Author: hikozuma
 */

#include <stdio.h>
#include <ctype.h>	//isdigit
#include <stdlib.h> //atoi

int main(){
	char inputFormula[50];
	char preserveNumStr[11];	//数字１0桁縛り

	double numArr[50] = { 0 };
	char signArr[50] = { '\0' };
	int inputLoop = 0, numStrLoop = 0, numArrLoop = 0, signArrLoop = 0;
	double answerNum = 0;
	int i, j;

	int signArrLen = 0;
	int numArrLen = 0;

	printf("Input a formula :");
	fgets(inputFormula, 30, stdin);

	while (inputFormula[inputLoop] != '\0'){

		if (inputFormula[inputLoop] == '+' ||
				inputFormula[inputLoop] == '-' ||
				inputFormula[inputLoop] == '*' ||
				inputFormula[inputLoop] == '/'){
			signArr[signArrLoop] = inputFormula[inputLoop];
			numArr[numArrLoop] = atoi(preserveNumStr);

			numArrLoop++;
			signArrLoop++;

			for (numStrLoop = 0; numStrLoop < 11; numStrLoop++){
				preserveNumStr[numStrLoop] = '\0';
			}

			numStrLoop = 0;

		}else if (isdigit(inputFormula[inputLoop])){
			preserveNumStr[numStrLoop] = inputFormula[inputLoop];
			numStrLoop++;
		}

		inputLoop++;
	}

	// preserve last number
	numArr[numArrLoop] = atoi(preserveNumStr);
	numArrLoop++;

	numArrLen = numArrLoop;
	signArrLen = signArrLoop;

	for(numArrLoop = 0; numArrLoop < numArrLen - 1; numArrLoop++){
		if(signArr[numArrLoop] == '*'){
			numArr[numArrLoop] = numArr[numArrLoop] * numArr[numArrLoop + 1];

			// numArr slide
			for(i = numArrLoop + 2; i < numArrLen + 1; i++){
				numArr[i - 1] = numArr[i];
			}

			numArr[numArrLen - 1] = 0;
			numArrLen--;

			// slideArr slide
			for(j = numArrLoop + 1; j < signArrLen; j++){
				signArr[j - 1] = signArr[j];
			}

			signArr[signArrLen - 1] = '\0';
			signArrLen--;
		}
	}

	for(numArrLoop = 0; numArrLoop < numArrLen - 1; numArrLoop++){
		if(signArr[numArrLoop] == '/'){
			if(numArr[numArrLoop + 1] == 0){
				printf("Error, divided by 0\n");
				return 0;
			}

			numArr[numArrLoop] = numArr[numArrLoop] / numArr[numArrLoop + 1];

			//slide
			for(i = numArrLoop + 2; i < numArrLen + 1; i++){
				//printf("numArr[%d] = %d, numArr[%d] = %d\n", i -1, numArr[i - 1], i , numArr[i]);
				numArr[i - 1] = numArr[i];
			}

			numArr[numArrLen - 1] = 0;
			numArrLen--;

			//slide
			for(j = numArrLoop + 1; j < signArrLen; j++){
				signArr[j - 1] = signArr[j];
			}

			signArr[signArrLen - 1] = '\0';
			signArrLen--;
		}
	}

	answerNum = numArr[0];

	for(numArrLoop = 1, signArrLoop = 0;
			numArrLoop < numArrLen;
			numArrLoop++, signArrLoop++){

		switch(signArr[signArrLoop]){
			case '+':
				answerNum += numArr[numArrLoop];
				break;

			case '-':
				answerNum -= numArr[numArrLoop];
				break;

		}
	}

	printf("answer = %0.5f\n", answerNum);
}

