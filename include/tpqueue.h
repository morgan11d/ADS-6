// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_

struct SYM {
  char ch;
  int prior;
};

template <typename T>
class TPQueue {
 private:
  struct Node {
    T data;
    Node* next;
    explicit Node(const T& value) : data(value), next(nullptr) {}
  };

  Node* head;

 public:
  TPQueue() : head(nullptr) {}

  ~TPQueue() {
    while (head != nullptr) {
      Node* temp = head;
      head = head->next;
      delete temp;
    }
  }

  TPQueue(const TPQueue&) = delete;
  TPQueue& operator=(const TPQueue&) = delete;

  void push(const T& value) {
    Node* newNode = new Node(value);

    if (head == nullptr || value.prior > head->data.prior) {
      newNode->next = head;
      head = newNode;
      return;
    }

    Node* current = head;
    while (current->next != nullptr &&
           current->next->data.prior >= value.prior) {
      current = current->next;
    }

    newNode->next = current->next;
    current->next = newNode;
  }

  T pop() {
    if (head == nullptr) {
      throw "Queue is empty";
    }

    Node* temp = head;
    T result = head->data;
    head = head->next;
    delete temp;

    return result;
  }

  bool isEmpty() const {
    return head == nullptr;
  }
};

#endif  // INCLUDE_TPQUEUE_H_
