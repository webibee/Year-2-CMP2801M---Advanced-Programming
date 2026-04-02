#define _CRT_SECURE_NO_WARNINGS
#include "Account.h"
#include <ctime>

char* currentDateAndTime() {
	time_t now = time(0);
	char* currDateTime = ctime(&now);
	return currDateTime;
}