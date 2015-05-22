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
void getRecordFromFile(FILE *targetInFp, NameData *targetNd, int recordCnt);
int comp( const void *c1, const void *c2);
void outputRecordToFile(FILE *targetOutFp, NameData *targetNd, int recordCnt);
void freeStruct(NameData *targetNd, int recordCnt);

int main(){
	FILE *inFp, *outFp;

	if((inFp = fopen(INPUTFILE, "r")) == NULL){
		printf("Error, program couldn't read input file.\n");
		return -1;
	}

	if((outFp = sortDataByCnt(inFp)) == NULL){
		printf("Error, program couldn't sort data.\n");
		return -1;
	}

	return 0;
}

/*
 * When executing this function, input file pointer is closed regardless of consequence.
 *
 * If an error occurs, return NULL.
 * If NO error occurs, return output File pointer.
 */
FILE *sortDataByCnt(FILE *inFp){
	FILE *outFp;
	int dataCnt;
	NameData *nameInfo;

	if((outFp = fopen(OUTPUTFILE, "w")) == NULL){
		printf("Output file open error\n");
		return NULL;
	}

	dataCnt = getRecordCntFromFile(inFp);

	if(dataCnt <= 0){
		printf("Program is finished because any data aren't found.\n");
		closePointers(inFp, outFp);
		return NULL;
	}

	fseek(inFp, 0, SEEK_SET);

	nameInfo = (NameData *) malloc(sizeof(NameData) * dataCnt);

	if(nameInfo == NULL){
		printf("can't allocate the memory.");
		return NULL;
	}

	getRecordFromFile(inFp, nameInfo, dataCnt);
	qsort(nameInfo, dataCnt, sizeof(NameData), comp);

	outputRecordToFile(outFp, nameInfo, dataCnt);
	freeStruct(nameInfo, dataCnt);

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

void getRecordFromFile(FILE *targetInFp, NameData *targetNd, int recordCnt){
	char tmpIn[255] = {"\0"};
	char tmpClassName[255] = {"\0"};
	int i;

	for(i = 0; i < recordCnt; i++){

		fgets(tmpIn, sizeof(tmpIn) , targetInFp);
		sprintf(tmpClassName, "%s", strtok(tmpIn, " "));

		targetNd[i].name = (char *) malloc(sizeof(char) * strlen(tmpClassName) + 1);
		strcpy(targetNd[i].name, tmpClassName);
		targetNd[i].cnt = atoi(strtok(NULL, " "));
	}
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

void outputRecordToFile(FILE *targetOutFp, NameData *targetNd, int recordCnt){
	int i;

	for(i = 0; i < recordCnt; i++){
		fprintf(targetOutFp, "%s %d\n", targetNd[i].name, targetNd[i].cnt);
	}
}

void freeStruct(NameData *targetNd, int recordCnt){
	int i;

	for(i = 0; i < recordCnt; i++){
		free(targetNd[i].name);
	}

	free(targetNd);
}
