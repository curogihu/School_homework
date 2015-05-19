/*
 * mainFunction.c
 *
 *  Created on: 2015/05/13
 *      Author: hikozuma
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INPUTFILE "inputData.txt"
#define OUTPUTFILE "outputData.txt"
#define DEBUG 1

typedef struct{
  char *name;
  int cnt;
}NameData;

FILE *sortDataByCnt(FILE *inFp);
int getRecordCntFromFile(FILE *targetFp);
void closePointers(FILE *fp1, FILE *fp2);
void getRecordFromFile(FILE *targetInFp, NameData *targetNd);
int comp( const void *c1, const void *c2);
void outputRecordToFile(FILE *targetOutFp, NameData *targetNd);

int main(){
	FILE *inFp, *outFp;

	inFp = fopen(INPUTFILE, "r");

	if((outFp = sortDataByCnt(inFp)) == NULL){
		printf("Error, program couldn't sort data");
	}

}

/*
 * When executing this function, input file pointer is closed regardless of consequence.
 *
 * If an error occurs, return NULL.
 * If NO error occurs, return output File pointer.
 */
FILE *sortDataByCnt(FILE *inFp){
	FILE *outFp;
	int i;
	int dataCnt;

	if((outFp = fopen(OUTPUTFILE, "w")) == NULL){
		printf("Output file open error\n");
		return NULL;
	}

#ifdef DEBUG
	printf("Success, two files are opened.\n");
#endif

	dataCnt = getRecordCntFromFile(inFp);

	if(dataCnt <= 0){
		printf("Program is finished because any data aren't found.\n");
		closePointers(inFp, outFp);
		return NULL;
	}

#ifdef DEBUG
	printf("Success, get records count.\n");
#endif

	fseek(inFp, 0, SEEK_SET);

	NameData nameInfo[dataCnt];

	for(i = 0; i< dataCnt; i++){
		getRecordFromFile(inFp, &nameInfo[i]);
	}

#ifdef DEBUG
	printf("Success, get datas from input file.\n");
#endif

	qsort( nameInfo, dataCnt, sizeof(NameData), comp);

#ifdef DEBUG
	printf("Success, do quick sort.\n");
#endif

	for(i = 0; i< dataCnt; i++){
		outputRecordToFile(outFp, &nameInfo[i]);
	}

#ifdef DEBUG
	printf("Success, write the sorted data to output file.\n");
#endif

	for(i = 0; i < dataCnt; i++){
		free(nameInfo[i].name);
	}

	fseek(outFp, 0, SEEK_SET);

#ifdef DEBUG
	printf("Success, close input and output file pointers.\n");
#endif

	return outFp;
}

// Caution: Parameter pointer will be termination after executing.
int getRecordCntFromFile(FILE *targetFp){
	char tmp[255] = {"\0"};
	int cnt = 0;

	while(fgets(tmp, sizeof(tmp) , targetFp) != NULL) {
		cnt++;
	}

	return cnt;
}

void closePointers(FILE *fp1, FILE *fp2){
	fclose(fp1);
	fclose(fp2);
}

void getRecordFromFile(FILE *targetInFp, NameData *targetNd){
	char tmpIn[255] = {"\0"};
	char tmpClassName[255] = {"\0"};

	fgets(tmpIn, sizeof(tmpIn) , targetInFp);
	sprintf(tmpClassName, "%s", strtok(tmpIn, " "));

	targetNd->name = (char *) malloc(sizeof(char) * strlen(tmpClassName) + 1);
	strcpy(targetNd->name, tmpClassName);
	targetNd->cnt = atoi(strtok(NULL, " "));
}

//Order by cnt desc, name asc
int comp(const void *c1, const void *c2){
	NameData test1 = *(NameData *)c1;
	NameData test2 = *(NameData *)c2;

	if(test1.cnt != test2.cnt){
		return test2.cnt - test1.cnt;

	}else{
		return strcmp(test1.name, test2.name);
	}
}

void outputRecordToFile(FILE *targetOutFp, NameData *targetNd){
	char tmpOut[255] = {"\0"};

	sprintf(tmpOut, "%s %d\n", targetNd->name, targetNd->cnt);
	fputs(tmpOut, targetOutFp);
}
