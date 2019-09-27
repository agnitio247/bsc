#include <iostream>

using namespace std;

#include "../include/Scheduler.h"

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
