#pragma once

struct node;

class linkedList {
private:
  node *head, *tail;
public:
  linkedList();
  ~linkedList();
  bool is_empty();
  void Add(string value);
  string GetValue(int id);
  void Print();
  int GetSize();
  int RemoveValue(string value);
  void Free();
};
