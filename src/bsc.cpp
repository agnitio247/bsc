#include <iostream>
#include <string>
#include <sys/stat.h>
#include <unistd.h>
#include <ctime>
#include <chrono>
#include <fstream>
#include <stdlib.h>

using namespace std;

#include "../include/Backup.h"
#include "../include/Functions.h"
#include "../include/Scheduler.h"
#include "../include/LinkedList.h"

// TODO : fix bug where program crashes if there is no time before current time 

int main(int argc, char const *argv[]) {
	// parse config
	string filePath = "doc/bsc.conf";
	linkedList backupDirs;
  linkedList schedules;
  ifstream in(filePath);
  if (!in.is_open()) {
    cerr << "Error: unable to open file" << endl;
    return 1;
  }
  string line;
  bool is_output = false;
  bool is_dir = false;
  bool is_day = false;
  string output;
  int dayCounter = 0;
  while (getline(in, line)) {
    if (line[0] != '#') {
      if (line.empty()) {
        if (is_output) {
          is_output = false;
        } else if (is_dir) {
          is_dir = false;
        } else if (is_day) {
          is_day = false;
          schedules.Add("SEPERATOR");
        }
      } else if (line == "Output") {
        is_output = true;
      } else if (line == "Dirs") {
        is_dir = true;
      } else {
        if (is_dir) {
          backupDirs.Add(line);
        } else if (is_output) {
          output = line;
        } else {
          if (!is_day) { // day name
            is_day = true;
            dayCounter++;
          }
          schedules.Add(line);
        }
      }
    }
  }
  schedules.Add("SEPERATOR");

	// parse schedules
  is_day = true;
  bool is_init = false;
  int timeCounter = 0;
  string dayName;
  linkedList *dayTimes;
  string *backupsTimes;
  schedule scheduleDay;
  string value;
  schedule backups[dayCounter];
  int scheduleDayId = 0;
  for (int i = 0; i < schedules.GetSize(); i++) {
    value = schedules.GetValue(i);
    if (value != "SEPERATOR") {
      if (is_day) { // value == day name
        dayName = value;
        is_day = false;
      } else { // value == time
        if (!is_init) {
          dayTimes = new linkedList();
          is_init = true;
        }
        dayTimes->Add(value);
        timeCounter++;
      }
    } else { // end of backup schedule
      scheduleDay.day = dayName;
      scheduleDay.size = timeCounter;
      backupsTimes = new string[timeCounter];
      for (int j = 0; j < dayTimes->GetSize(); j++) {
        backupsTimes[j] = dayTimes->GetValue(j);
      }
      delete dayTimes;
      scheduleDay.time = backupsTimes;
      backups[scheduleDayId] = scheduleDay;
      is_day = true;
      is_init = false;
      timeCounter = 0;
      scheduleDayId++;
    }
  }

	// TODO : better verbose
	int sleepTime;
	schedule nextBackup;
	schedule currentDay;
	string currentDayDay;
	string currentDayTime;
	auto currentTime = std::chrono::system_clock::now();
	time_t currentTime_t;

	while (true) {
		currentTime = std::chrono::system_clock::now();
		currentTime_t = std::chrono::system_clock::to_time_t(currentTime);
		currentDayDay = Split(ctime(&currentTime_t), ' ', 0);
		if (currentDayDay == "Wed") {
			currentDayDay = currentDayDay + "nesday";
		} else if (currentDayDay == "Sat") {
			currentDayDay = currentDayDay + "urday";
		} else if (currentDayDay == "Thu") {
			currentDayDay = currentDayDay + "rsday";
		} else if (currentDayDay == "Tue") {
			currentDayDay = currentDayDay + "sday";
		} else {
			currentDayDay = currentDayDay + "day";
		}
		currentDayTime = Split(ctime(&currentTime_t), ' ', -2);
		currentDay.day = currentDayDay;
		string currentDayTimeArray[] = {currentDayTime};
		currentDay.time = currentDayTimeArray;
		currentDay.size = 1;

		nextBackup = GetNextBackup(currentDay, backups, dayCounter, &sleepTime);

		cout << "Next backup " << nextBackup.day << " at " << nextBackup.time[0] << "..." << endl;

		sleep(sleepTime);
		cout << endl;
		for (int i = 0; i < backupDirs.GetSize(); i++) {
			cout << backupDirs.GetValue(i) << endl;
			if (Backup(backupDirs.GetValue(i), output, true) == 1) {
				cout << "An error occured" << endl;
			}
		}
		delete[] nextBackup.time;
		cout << "Done" << endl;
		cout << endl;
	}

	for (int i = 0; i < dayCounter; i++) {
		delete[] backups[i].time;
	}
	return 0;
}
