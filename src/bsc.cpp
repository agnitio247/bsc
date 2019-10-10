#include <iostream>
#include <string>
#include <sys/stat.h>
#include <unistd.h>
#include <ctime>

using namespace std;

#include "../include/Backup.h"
#include "../include/Functions.h"
#include "../include/Scheduler.h"
#include "../include/Config.h"

int main(int argc, char const *argv[]) {
	string source = "/home/alex/Pictures";
	string dest = "/home/alex/Desktop";

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
	int sleepTime;
	schedule nextBackup = GetNextBackup(currentDay, backups, backupsSize, &sleepTime);
	cout << sleepTime << endl;
	if (Backup(source, dest, false) == 0) {
		cout << "Backup done in " << endl;
	} else {
		cout << "Something went wrong..." << endl;
	}
	return 0;
}
