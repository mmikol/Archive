#include <list>
#include <map>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

vector<pair<string, int>> sorted_word_counts(list<string> words) {
  auto dictionary = map<string, int>();
  
  for (auto word : words) {
    ++dictionary[word];
  }

  vector<pair<string, int>> v(dictionary.begin(), dictionary.end());
  sort(v.begin(), v.end(), [](auto x, auto y) { return x.second > y.second; });
  
  return v;
}

struct Say {
  string words;
  
  auto operator()() { 
    return words; 
  }
  
  Say operator()(string next_word) { 
    if (!words.length()) {
      return { words + next_word };
    }
    return { words + " " + next_word }; 
  }
} say;

template<typename T>

class Queue {
  struct Node { 
    T data;
    Node* next;
  };
  Node* head;
  Node* tail;
  int size;
  
public: 
  Queue(): head(nullptr), tail(nullptr), size() {}
  
  // Prohibit copying
  Queue(Queue&) = delete;
  Queue& operator=(Queue&) = delete;

  // Allow moves
  Queue(Queue&&) = default;
  Queue& operator=(Queue&&) = default;

  int get_size() {
    return size;
  }
  
  void enqueue(T data) {
    Node* enqueue_node = new Node{ data, nullptr };
    
    if (size == 0) {
      head = tail = enqueue_node;
      size++;
      return;
    }

    tail->next = enqueue_node;
    tail = enqueue_node;
    size++;
  }

  T dequeue() {
    if (size == 0) {
      throw underflow_error("Cannot dequeue from empty queue");
    } 

    Node* dequeue_node = head;
    T dequeue_data = dequeue_node->data;

    if (size == 1) {
      head = tail = nullptr;
    } else {
      head = head->next;
    }

    delete dequeue_node;

    size--;

    return dequeue_data;
  }

  friend ostream& operator<<(ostream& stream, const Queue& queue) {
    Node* current_node = queue.head;

    while (current_node != nullptr) {
      stream << "(" << current_node->data << ")";
      if (current_node->next != nullptr) {
        stream << "->";
      }
      current_node = current_node->next;
    }

    stream << "\n";
    
    return stream;
  }
};

