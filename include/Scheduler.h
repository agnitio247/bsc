#pragma once

struct schedule {
  string day;
  string* time;
  int size;
};

extern string weekDays[7];

string GetDay(int id);
int GetDayId(string day);
int ConvertTime(string time);
schedule ClosestDay(schedule , schedule* backups, int backupsSize, int *daysLeft);
string ClosestTime(schedule currentDay, schedule targetDay, int daysLeft);
int GetTimeLeft(schedule currentDay, schedule targetDay, int timeStamp);
