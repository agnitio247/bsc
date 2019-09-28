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

schedule ClosestDay(schedule currentDay, schedule* backups, int backupsSize) {
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
  return lowerTimeStampDay;
}
