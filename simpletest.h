#ifndef _SIMPLETEST_H_
#define _SIMPLETEST_H_

#include <stdio.h>
#include <stdlib.h>

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

int maxgrade=0; 
int currmaxgrade=0;
int grade=0;

/* or else we will calculate it by the running tests */
/* joke is on you if you use negative grades... */
#define MAXGRADE(max) maxgrade=max

int GETGRADE(){
	return grade;
}

int GETMAXGRADE(){
	if (maxgrade)
		return maxgrade;
	else return currmaxgrade;
}

void GRADEME(){
	if (!maxgrade)
		maxgrade = currmaxgrade;

	if (grade < maxgrade*.7){
		printf("You did %s %d %s out of %d\n", KRED, grade, KNRM, maxgrade);
	}
	else{
		printf("You did %s %d %s out of %d\n", KGRN, grade, KNRM, maxgrade);
	}
}

void DESCRIBE(char* text);
void WHEN(char* text);
void IF(char* text);
void THEN(char* text);

void DESCRIBE(char* text) {
	printf("%s-- %s --%s\n",KCYN, text, KNRM);
}

void WHEN(char* text) {
	printf("%s  when:%s %s\n",KYEL, KNRM, text);
}

void IF(char* text) {
	printf("%s    if:%s %s\n",KYEL, KNRM, text);
}

void THEN(char* text) {
	printf("%s      then:%s %s\n",KYEL, KNRM, text);
}

void isNull(void* ptr, int points) {
	currmaxgrade+=points;
	if (ptr == NULL) {
		printf("%s        PASSED!\n%s", KGRN, KNRM);
		grade+=points;
	} else {
		printf("%s        NOT PASSED!\n        pointer is not null%s\n", KRED, KNRM);
	}
}

void isNotNull(void * ptr, int points) {
	currmaxgrade+=points;
	if (ptr != NULL) {
        printf("%s        PASSED!\n%s", KGRN, KNRM);
        grade+=points;
    } else {
            printf("%s        NOT PASSED!\n        pointer is not null%s\n", KRED, KNRM);
    }
}

void isGreaterThan(int num, int value, int points) {
	currmaxgrade+=points;
	if (num > value) {
		printf("%s        PASSED!\n%s", KGRN, KNRM);
		grade+=points;
	} else {
		printf("%s        NOT PASSED!\n        got: %d > %d %s\n", KRED, num, value, KNRM);
	}
}

void isEqual(int num, int value, int points) {
	currmaxgrade+=points;
	if (num == value) {
		printf("%s        PASSED!\n%s", KGRN, KNRM);
		grade+=points;
	} else {
		printf("%s        NOT PASSED!\n        got: %d == %d %s\n", KRED, num, value, KNRM);
	}
}

void isNotEqual(int num, int value, int points) {
	currmaxgrade+=points;	
	if (num != value) {
		printf("%s        PASSED!\n%s", KGRN, KNRM);
		grade+=points;
	} else {
		printf("%s        NOT PASSED!\n        got: %d != %d %s\n",KRED, num, value, KNRM);
	}
}

void isLesserThan(int num, int value, int points) {
	currmaxgrade+=points;
	if (num < value) {
		printf("%s        PASSED!\n%s", KGRN, KNRM);
		grade+=points;
	} else {
		printf("%s        NOT PASSED!\n        got: %d < %d %s\n",KRED, num, value, KNRM);
	}
}


#endif //_SIMPLETEST_H