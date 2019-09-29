#include <iostream>
#include <string>
#include <sys/stat.h>

using namespace std;

#include "../include/Backup.h"
#include "../include/Functions.h"
#include "../include/Scheduler.h"

int main(int argc, char const *argv[]) {
	string currentDayTime[] = {
		"20:25:52",
	};
	schedule currentDay = {
		"Sunday",
		currentDayTime,
		1
	};

	string fridayTime[] = {
		"08:30:00",
		"12:00:15"
	};
	schedule friday = {
		"Friday",
		fridayTime,
		2
	};

	string wednesdayTime[] = {
		"08:30:00",
		"13:30:00",
		"14:00:20"
	};
	schedule wednesday = {
		"Wednesday",
		wednesdayTime,
		3
	};

	schedule backups[] = {
		friday,
		wednesday
	};

	int backupsSize = sizeof(backups)/sizeof(backups[0]);

	schedule nextBackup = GetNextBackup(currentDay, backups, backupsSize);
	return 0;
}
