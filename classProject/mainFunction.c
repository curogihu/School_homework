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
  char name[20];
  int cnt;

}NameData;

int comp( const void *c1, const void *c2);

int main(){

	FILE *inFp, *outFp;
	NameData nameInfo[10];
	int i;
	int classNameLen = 0, dataCnt = 0;
	char tmpIn[255] = {"\0"};
	char tmpOut[255] = {"\0"};
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
/*
	if((inFp = fopen("sampleFile.txt", "r")) == NULL){
		printf("Input file open error\n");
		return 0;
	}
*/

	if((outFp = fopen("output.txt", "w")) == NULL){
		printf("Output file open error\n");
		return 0;
	}

	for(i = 0; i< 10; i++){
		// format is "[className] [repetitionCnt]", including blank.
		sprintf(nameInfo[i].name, "%s", strtok(nameList[i], " "));
		nameInfo[i].cnt = atoi(strtok(NULL, " "));
/*
		printf("%s:%d\n", nameInfo[i].name, nameInfo[i].cnt);
*/
	}

	qsort( nameInfo, 10, sizeof(NameData), comp );
	printf("\n\n");

	for(i = 0; i< 10; i++){
/*
		printf("%s %d\n", nameInfo[i].name, nameInfo[i].cnt);
*/
		sprintf(tmpOut, "%s %d\n", nameInfo[i].name, nameInfo[i].cnt);

		printf("value = %s", tmpOut);
		/* ファイルにデータを書き込み */
		//fwrite(tmpOut, sizeof(char) * 255, 1, outFp);
		fputs(tmpOut, outFp);
	}

	//fclose(inFp);
	fclose(outFp);
}

int comp( const void *c1, const void *c2){
	NameData test1 = *(NameData *)c1;
	NameData test2 = *(NameData *)c2;

	int cnt1 = test1.cnt;
	int cnt2 = test2.cnt;

	//if change with cnt1 - cnt2, order will be ascending.
	return cnt2 - cnt1;
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

