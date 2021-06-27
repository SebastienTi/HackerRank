#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <set>
#include <cassert>
using namespace std;

struct Node{
   Node* next;
   Node* prev;
   int value;
   int key;
   Node(Node* p, Node* n, int k, int val):prev(p),next(n),key(k),value(val){};
   Node(int k, int val):prev(NULL),next(NULL),key(k),value(val){};
};

class Cache{
   
   protected: 
   map<int,Node*> mp; //map the key to the node in the linked list
   int cp;  //capacity
   Node* tail; // double linked list tail pointer
   Node* head; // double linked list head pointer
   virtual void set(int, int) = 0; //set function
   virtual int get(int) = 0; //get function

};

class LRUCache: public Cache {
    public:
        explicit LRUCache(int capacity);
        void set(int key, int value) override;
        int get(int key) override;
    
    private:
       void updateHead(Node* node);
       void addNode(Node* node);
    
};

LRUCache::LRUCache(int capacity){
    cp = capacity; 
    head = NULL;
    tail = NULL;
}

/* Place the node chosen to the head place */
void LRUCache::updateHead(Node* node){
    /* Create connection between the two nodes around the chosen node */
    if(node->next)
        node->next->prev = node->prev;
    
    if(node->prev)
        node->prev->next = node->next;

    /* Reset node value to become the head */
    node->prev = NULL;

    node->next = head;

    if(head) {
        head->prev = node;
    }
    head = node;
}

int LRUCache::get(int key) {
    
    if(mp.find(key) != mp.end()) {        
        return mp[key]->value;
    }
    
    return -1;
}

/* Add a node to the list */
void LRUCache::addNode(Node* node) {
    if(head == NULL) {
        tail = node; // Initiate tail address when we add the first value
    } else {
        head->prev = node;
    }
    
    /* Set node as head and add it to the map */
    head = node;
    mp.emplace(node->key, node);
}

void LRUCache::set(int key, int value) {
    /* Case if the key already exists */
    if(mp.find(key) != mp.end()) { 
        mp[key]->value = value; // update the value in the map
        updateHead(mp[key]); // update the head
        
        return;    
    }
    
    /* If the key doesn't exist we have to create one node */
    auto* newNode = new Node(NULL, head, key, value);
    if(mp.size() < cp) { // If the list is not full
        addNode(newNode); 
    } else {
        /* If the list is full we have to erase the last node and update the tail */
        mp.erase(tail->key);
        Node* tempNode = tail;
        tail = tail->prev;
        tail->next = NULL;
        
        delete tempNode;
        
        /* We can add a new node */
        addNode(newNode);
    } 
       
}

int main() {
   int n, capacity,i;
   cin >> n >> capacity;
   LRUCache l(capacity);
   for(i=0;i<n;i++) {
      string command;
      cin >> command;
      if(command == "get") {
         int key;
         cin >> key;
         cout << l.get(key) << endl;
      } 
      else if(command == "set") {
         int key, value;
         cin >> key >> value;
         l.set(key,value);
      }
   }
   return 0;
}

