#include <iostream>
#include <string>
#include <sys/stat.h>
#include <unistd.h>
#include <ctime>
#include <fstream>

using namespace std;

#include "../include/Backup.h"
#include "../include/Functions.h"
#include "../include/Scheduler.h"
#include "../include/LinkedList.h"

int main(int argc, char const *argv[]) {
	string currentDayTime[] = {
		"20:25:52",
	};
	schedule currentDay = {
		"Sunday",
		currentDayTime,
		1
	};

	// parse config (fucks up if put in function cuz memory stuff)
	string filePath = "doc/bsc.conf";
	linkedList *backupDirs = new linkedList();
  linkedList *schedules = new linkedList();
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
          schedules->Add("SEPERATOR");
        }
      } else if (line == "Output") {
        is_output = true;
      } else if (line == "Dirs") {
        is_dir = true;
      } else {
        if (is_dir) {
          backupDirs->Add(line);
        } else if (is_output) {
          output = line;
        } else {
          if (!is_day) { // day name
            is_day = true;
            dayCounter++;
          }
          schedules->Add(line);
        }
      }
    }
  }
  schedules->Add("SEPERATOR");

	// parse schedules
  is_day = true;
  bool is_init = false;
  int timeCounter = 0;
  string dayName;
  linkedList *dayTimes;
  string *backupsTimes;
  schedule *scheduleDay;
  string value;
  schedule **backups = new schedule*[dayCounter];
  int scheduleDayId = 0;
  for (int i = 0; i < schedules->GetSize(); i++) {
    value = schedules->GetValue(i);
    if (value != "SEPERATOR") {
      if (is_day) { // value == day name
        cout << "day: " << value << endl;
        dayName = value;
        is_day = false;
      } else { // value == time
        if (!is_init) {
          dayTimes = new linkedList();
          is_init = true;
        }
        dayTimes->Add(value);
        timeCounter++;
        cout << "time: " << value << endl;
      }
    } else { // end of backup schedule
      scheduleDay = new schedule;
      scheduleDay->day = dayName;
      scheduleDay->size = timeCounter;
      backupsTimes = new string[timeCounter];
      for (int j = 0; j < dayTimes->GetSize(); j++) {
        backupsTimes[j] = dayTimes->GetValue(j);
      }
      delete dayTimes;
      scheduleDay->time = backupsTimes;
      backups[scheduleDayId] = scheduleDay;
      is_day = true;
      is_init = false;
      timeCounter = 0;
      scheduleDayId++;
      cout << endl;
    }
  }
  delete schedules;
	/*
	int sleepTime;
	schedule nextBackup = GetNextBackup(currentDay, backups, dayCounter, &sleepTime);
	cout << sleepTime << endl;
	// sleep(sleepTime);
	for (int i = 0; i < backupDirs->GetSize(); i++) {
		if (Backup(backupDirs->GetValue(i), output, false) == 1) {
			cout << "An error occured" << endl;
		}
	}
	*/
	delete backupDirs;
	for (int i = 0; i < dayCounter; i++) {
		delete[] backups[i]->time;
		delete backups[i];
	}
	delete[] backups;
	return 0;
}
