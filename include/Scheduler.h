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

schedule GetClosestDay(schedule currentDay, schedule* backups, int backupsSize, int *daysLeft);
string GetClosestTime(schedule currentDay, schedule targetDay, int daysLeft);
int GetTimeLeft(schedule currentDay, schedule targetDay, int timeStamp);

schedule GetNextBackup(schedule currentDay, schedule *backups, int backupsSize);
