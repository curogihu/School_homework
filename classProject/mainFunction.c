/*
 * mainFunction.c
 *
 *  Created on: 2015/05/13
 *      Author: hikozuma
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>		//atoi

typedef struct{
  char *name;
  int cnt;

}NameData;

int comp( const void *c1, const void *c2);
int getRecordCntFromFile(FILE *targetFp);
void closePointers(FILE *fp1, FILE *fp2);

int main(){

	FILE *inFp, *outFp;
	char tmpIn[255] = {"\0"};
	char tmpOut[255] = {"\0"};
	char tmpClassName[255] = {"\0"};
	int i;
	int dataCnt;

	if((inFp = fopen("inputData2.txt", "r")) == NULL){
		printf("Input file open error\n");
		return 0;
	}

	//if((outFp = fopen("./output.txt", "w")) == NULL){
	if((outFp = fopen("outputData.txt", "w")) == NULL){
		printf("Output file open error\n");
		return 0;
	}

	printf("Success, two files are opened.\n");

	dataCnt = getRecordCntFromFile(inFp);

	if(dataCnt <= 0){
		printf("Program is finished because any data aren't found.\n");
		closePointers(inFp, outFp);
	}

	printf("Success, get records count.\n");

	fseek(inFp, 0, SEEK_SET);

	NameData nameInfo[dataCnt];

	for(i = 0; i< dataCnt; i++){
		fgets(tmpIn, sizeof(tmpIn) , inFp);
		sprintf(tmpClassName, "%s", strtok(tmpIn, " "));

		nameInfo[i].name = (char *) malloc(sizeof(char) * strlen(tmpClassName) + 1);
		strcpy(nameInfo[i].name, tmpClassName);

		nameInfo[i].cnt = atoi(strtok(NULL, " "));
	}

	printf("Success, get datas from input file.\n");

	qsort( nameInfo, dataCnt, sizeof(NameData), comp);

	printf("Success, do quick sort.\n");

	for(i = 0; i< dataCnt; i++){
		sprintf(tmpOut, "%s %d\n", nameInfo[i].name, nameInfo[i].cnt);
		fputs(tmpOut, outFp);
	}

	printf("Success, write the sorted data to output file.\n");

	for(i = 0; i < dataCnt; i++){
		free(nameInfo[i].name);
	}

	closePointers(inFp, outFp);

	printf("Success, close input and output file pointers.\n");
}

// Caution: Parameter pointer goes to end.
int getRecordCntFromFile(FILE *targetFp){
	char tmp[255] = {"\0"};
	int cnt = 0;

	while(fgets(tmp, sizeof(tmp) , targetFp) != NULL) {
		cnt++;
	}

	return cnt;
}

int comp( const void *c1, const void *c2){
	NameData test1 = *(NameData *)c1;
	NameData test2 = *(NameData *)c2;

	if(test1.cnt != test2.cnt){
	//if change with cnt1 - cnt2, order will be ascending.
		return test2.cnt - test1.cnt;

	// when both cnt are same, compare both class name.
	// In this case, order becomes ascending.
	}else{
		return strcmp(test1.name, test2.name);
	}
}
/*
int comp( const void *c1, const void *c2){
	NameData test1 = *(NameData *)c1;
	NameData test2 = *(NameData *)c2;

	int cnt1 = test1.cnt;
	int cnt2 = test2.cnt;

	//if change with cnt1 - cnt2, order will be ascending.
	return cnt2 - cnt1;
}
*/

void closePointers(FILE *fp1, FILE *fp2){
	fclose(fp1);
	fclose(fp2);
}
