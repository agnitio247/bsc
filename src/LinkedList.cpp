#include <iostream>
#include <fstream>

using namespace std;

#include "../include/LinkedList.h"

struct node {
  string data;
  node *next;
};

linkedList::linkedList() {
  head = NULL;
  tail = NULL;
}

bool linkedList::is_empty() {
  return (head == NULL) ? true : false;
}

void linkedList::Add(string value) {
  node *temp = new node;
  temp->data = value;
  temp->next = NULL;

  if (this->is_empty()) {
    head = temp;
    tail = temp;
    temp = NULL;
  } else {
    tail->next = temp;
    tail = temp;
  }
}

string linkedList::GetValue(int id) {
  node *temp = new node;
  temp = head;
  for (int i = 0; i < id; i++) {
    temp = temp->next;
  }
  string value = temp->data;
  return value;
}

void linkedList::Print() {
  node *temp = new node;
  temp = head;
  if (this->is_empty()) {
    cout << "List is empty" << endl;
  } else {
    while (temp != NULL) {
      cout << temp->data << endl;
      temp = temp->next;
    }
  }
}

int linkedList::GetSize() {
  node *temp = new node;
  temp = head;
  if (this->is_empty()) {
    return 0;
  } else {
    int counter = 0;
    while (temp != NULL) {
      counter++;
      temp = temp->next;
    }
    return counter;
  }
  return -1;
}

int linkedList::RemoveValue(string value) {
  if (this->is_empty()) {
    return 1;
  } else {
    if (head->data == value) {
      node *temp = new node;
      temp = head;
      head = head->next;
      delete temp;
      return 0;
    }
    node *current = new node;
    node *previous = new node;
    current = head;
    while (current->data != value) {
      previous = current;
      current = current->next;
    }
    previous->next = current->next;
  }
  return 0;
}
