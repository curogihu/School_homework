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
  //char name[20];
  int cnt;

}NameData;

int comp( const void *c1, const void *c2);
int getDataCntFromFile(FILE *targetFp);
void closePointers(FILE *fp1, FILE *fp2);

int main(){

	FILE *inFp, *outFp;
	//NameData nameInfo[10];
	//NameData nameInfo;
	int i;
	int dataCnt;
	char tmpIn[255] = {"\0"};
	char tmpClassName[255] = {"\0"};
	char tmpOut[255] = {"\0"};
	/*
	char nameList[][20] = {"ClassName6508 7530",
							"ClassName5660 4682",
							"ClassName3500 444",
							"ClassName6941 5317",
							"ClassName1567 337",
							"ClassName1677 5037",
							"ClassName9929 4267",
							"ClassName1969 3855",
							"ClassName3631 3500",
							"ClassName2976 5639"
							};
*/
	if((inFp = fopen("/Users/hikozuma/Documents/workspace/ProjectByC/sampleFlie.txt", "r")) == NULL){
		printf("Input file open error\n");
		return 0;
	}

	if((outFp = fopen("./output.txt", "w")) == NULL){
		printf("Output file open error\n");
		return 0;
	}

	dataCnt = getDataCntFromFile(inFp);

	if(dataCnt <= 0){
		printf("Program is finished because any data aren't found.\n");
		closePointers(inFp, outFp);
	}

	fseek(inFp, 0, SEEK_SET);

	//nameInfo = (NameData *) malloc(NameData(char) * dataCnt);
	NameData nameInfo[dataCnt];

	for(i = 0; i< dataCnt; i++){
		fgets(tmpIn, sizeof(tmpIn) , inFp);
		sprintf(tmpClassName, "%s", strtok(tmpIn, " "));

		//output ok
		//printf("string = %s, len = %d\n", tmpClassName, strlen(tmpClassName));
		// format is "[className] [repetitionCnt]", including blank.

		nameInfo[i].name = (char *) malloc(sizeof(char) * strlen(tmpClassName) + 1);
		strcpy(nameInfo[i].name, tmpClassName);

		nameInfo[i].cnt = atoi(strtok(NULL, " "));

		printf("%s, %d\n", nameInfo[i].name, (int)strlen(nameInfo[i].name));

//		sprintf(nameInfo[i].name, "%s", strtok(nameList[i], " "));
		//sprint(tmpClassName, "%s", strtok())

		//nameInfo[i].cnt = atoi(strtok(NULL, " "));

		//printf("%s:%d\n", nameInfo[i].name, nameInfo[i].cnt);
	}

	qsort( nameInfo, 10, sizeof(NameData), comp );
	printf("\n\n");

	for(i = 0; i< dataCnt; i++){

		sprintf(tmpOut, "%s %d\n", nameInfo[i].name, nameInfo[i].cnt);

		//fwrite(tmpOut, sizeof(char) * 255, 1, outFp);
		fputs(tmpOut, outFp);
	}

	for(i = 0; i < dataCnt; i++){
		free(nameInfo[i].name);
	}

	closePointers(inFp, outFp);
}

// Caution: Parameter go to last.
int getDataCntFromFile(FILE *targetFp){
	char tmp[255] = {"\0"};
	int cnt = 0;

	while(fgets(tmp, sizeof(tmp) , targetFp) != NULL ) {
		cnt++;
	}

	return cnt;
}

int comp( const void *c1, const void *c2){
	NameData test1 = *(NameData *)c1;
	NameData test2 = *(NameData *)c2;

	int cnt1 = test1.cnt;
	int cnt2 = test2.cnt;

	//if change with cnt1 - cnt2, order will be ascending.
	return cnt2 - cnt1;
}

void closePointers(FILE *fp1, FILE *fp2){
	fclose(fp1);
	fclose(fp2);
}

/*
	if((fp = fopen("sampleFile.txt", "r")) == NULL){
			printf("file open error\n");
			return 0;
	}

	while((tmpChar = fgetc(fp)) != EOF ) {
		printf( "%c" , tmpChar);
	}
*/

/*
	fclose(fp);
*/

