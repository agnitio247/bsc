#pragma once

string Split(string input, char seperator, int id);
bool IsDir(string path);
bool IsFile(string path);
string* ListDir(string path, int *size);
