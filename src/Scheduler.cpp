#include <iostream>

using namespace std;

#include "../include/Scheduler.h"
#include "../include/Functions.h"

string weekDays[] = {
  "Monday",
  "Tuesday",
  "Wednesday",
  "Thursday",
  "Friday",
  "Saturday",
  "Sunday"
};

string GetDay(int id) {
  return weekDays[id-1];
}

int GetDayId(string day) {
  for (int i = 0; i < 7; i++) {
    if (weekDays[i] == day) {
      return i+1;
    }
  }
  return -1;
}

int ConvertTime(string time) {
  string hours = Split(time, ':', 0);
  string minutes = Split(time, ':', 1);
  string seconds = Split(time, ':', 2);
  int output = stoi(hours)*3600 + stoi(minutes)*60 + stoi(seconds);
  return output;
}

int GetTimeLeft(schedule currentDay, schedule targetDay, int timeStamp) { // timeStamp -> number of days between current and target
  int secondsUntilTargetDay = timeStamp*24*60*60;
  int timeLeft;
  if (ConvertTime(targetDay.time[0]) > ConvertTime(currentDay.time[0])) {
    timeLeft = secondsUntilTargetDay + (ConvertTime(targetDay.time[0]) - ConvertTime(currentDay.time[0]));
  } else {
    if (targetDay.day == currentDay.day) {
      secondsUntilTargetDay = 7*24*60*60;
    }
    timeLeft = secondsUntilTargetDay - (ConvertTime(currentDay.time[0]) - ConvertTime(targetDay.time[0]));
  }
  return timeLeft;
}

schedule GetClosestDay(schedule currentDay, schedule* backups, int backupsSize, int *daysLeft) {
  int timeStamp;
  int lowerTimeStamp = 7; // actually higher
  schedule lowerTimeStampDay;
  for (int i = 0; i < backupsSize; i++) { // each day
    for (int j = 0; j < backups[i].size; j++) { // each time in day
      // calculate time stamp between backup time and current time
      if (GetDayId(backups[i].day) >= GetDayId(currentDay.day) && ConvertTime(currentDay.time[0]) < ConvertTime(backups[i].time[j])) {
        timeStamp = GetDayId(backups[i].day) - GetDayId(currentDay.day);
        if (timeStamp < lowerTimeStamp) {
          lowerTimeStamp = timeStamp;
          lowerTimeStampDay = backups[i];
        }
      } else {
        timeStamp = 7 - (GetDayId(currentDay.day) - GetDayId(backups[i].day));
        if (timeStamp < lowerTimeStamp) {
          lowerTimeStamp = timeStamp;
          lowerTimeStampDay = backups[i];
        }
      }
    }
  }
  *daysLeft = lowerTimeStamp;
  return lowerTimeStampDay;
}

string GetClosestTime(schedule currentDay, schedule targetDay, int daysLeft) {
  int lowerTimeStamp = 7*24*60*60;
  schedule backupSchedule;
  string lowerTimeStampTime = "ok";
  int timeStamp;
  string backupScheduleTime[1];
  for (int i = 0; i < targetDay.size; i++) {
    backupScheduleTime[0] = {targetDay.time[i]};
    backupSchedule = {targetDay.day, backupScheduleTime, 1};
    timeStamp = GetTimeLeft(currentDay, backupSchedule, daysLeft);
    if (timeStamp < lowerTimeStamp) {
      lowerTimeStamp = timeStamp;
      lowerTimeStampTime = backupScheduleTime[0];
    }
  }

  return lowerTimeStampTime;
}

schedule GetNextBackup(schedule currentDay, schedule *backups, int backupsSize, int *timeLeft) {
  int daysLeft;
	schedule closestDay = GetClosestDay(currentDay, backups, backupsSize, &daysLeft);
	string closestTime = GetClosestTime(currentDay, closestDay, daysLeft);
	string nextBackupTime[] = {closestTime};
	schedule nextBackup = {
		closestDay.day,
		nextBackupTime,
		1
	};
  *timeLeft = GetTimeLeft(currentDay, nextBackup, daysLeft);
	return nextBackup;
}
