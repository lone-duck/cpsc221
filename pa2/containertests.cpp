// file:        containertests.cpp
// author:      Geoff T
// date:        2017-10-07
// description: A few general tests for CPSC 221 PA2 container classes
//              You should add your own test cases!

#include <cstdlib>
#include <iostream>
#include <string>

#include "arrayclass.h"
#include "stack.h"
#include "queue.h"

using namespace std;

// forward function declarations
void arrayClassTests();
void stackTests();
void queueTests();
template <typename T>
void printArrayClass(ArrayClass<T>&);
template <typename T>
void printStack(Stack<T>&);
template <typename T>
void printQueue(Queue<T>&);
void printResult(bool);
void split(const string& str, const string& delim, Queue<string>& parts);

// program entry
int main()
{
  arrayClassTests();
  stackTests();
  queueTests();

  cout<<"Testing split..."<<endl;
  Queue<string> q;
  string str = "There was an old lady who swallowed a fly";
  split(str, " ", q);
  printQueue(q);

  // Windows-specific, remove before distribution
#ifdef _WIN32
  system("pause");
#endif
  return 0;
}

void split(const string& str, const string& delim, Queue<string>& parts) {
  size_t start, end = 0;
  while (end < str.size()) {
    start = end;
    while (start < str.size() && (delim.find(str[start]) != string::npos)) {
      start++;  // skip initial whitespace
    }
    end = start;
    while (end < str.size() && (delim.find(str[end]) == string::npos)) {
      end++; // skip to end of word
    }
    if (end-start != 0) {  // just ignore zero-length strings.
      parts.enqueue(string(str, start, end-start) + "!");
    }
  }
}

void printResult(bool result){
  if(result){
    cout << "PASSED" << endl;
  }else{
    cout << "FAILED" << endl;
  }
}


template <typename T>
void printStack(Stack<T>& st){
  Stack<T> pst = st;
  while(!pst.isEmpty()){
    cout << pst.pop() << " ";
  }
  cout << endl;
}

template <typename T>
void printQueue(Queue<T>& q){
  Queue<T> pq = q;
  while(!pq.isEmpty()){
    cout << pq.dequeue() << " ";
  }
  cout << endl;
}

template <typename T>
void printArrayClass(ArrayClass<T>& ac){
  for(int i = 0; i < ac.size(); i++){
    cout << ac[i] << " ";
  }
  cout << endl;
}





void arrayClassTests()
{
  cout << "Entered arrayClassTests..." << endl;
  ArrayClass<int> ac1;
  ArrayClass<int> ac2(10);

  cout << "\nac1 and ac2 created." << endl;
  cout << "\nac1 has size 0: " << endl;
  printResult(ac1.size() == 0);
  cout << "\nac1 has DEFAULTCAPACITY: " << endl;
  printResult(ac1.capacity() == DEFAULTCAPACITY);
  cout << "\nac2 has size 0: " << endl;
  printResult(ac2.size() == 0);
  cout << "\nac2 has capacity 10: " << endl;
  printResult(ac2.capacity() == 10);
  cout << "\nac1 and ac2 are both empty: "<< endl;
  printResult(ac1.empty() && ac2.empty());
  cout << "\nPushing numbers 0 through 12 to ac1..." << endl;
  for (int i = 0; i <= 12; i++)
  {
    ac1.pushBack(i);
  }
  cout << "\nac1 now contains:   ";
  printArrayClass(ac1);
  cout << "\nac1 should contain: 0 1 2 3 4 5 6 7 8 9 10 11 12" << endl;
  cout << "\nac1 size is 13:" << endl;
  printResult(ac1.size() == 13);
  cout << "\nac1 capacity is 16:" << endl;
  printResult(ac1.capacity() == 16);
  
  cout << "\nCycling ac1 items to start from index 3 (and value 3) ..." << endl;
  ac1.startFrom(3);
  cout << "\nac1 now contains:   ";
  printArrayClass(ac1);
  cout << "\nac1 should contain: 3 4 5 6 7 8 9 10 11 12 0 1 2 " << endl;

  cout << "\nPushing 31 to ac2" << endl;
  ac2.pushBack(31);
  cout << "\nac2 now contains:   ";
  printArrayClass(ac2);
  cout << "\nac2 should contain: 31" << endl;
  cout << "\nRunning shrinkToFit on ac2" << endl;
  ac2.shrinkToFit();
  cout << "\nac2 size is 1:" << endl;
  printResult(ac2.size() == 1);
  cout << "\nac2 capacity is 1:" << endl;
  printResult(ac2.capacity() == 1);

  cout << "\nac1 resized down to 3..." << endl;
  ac1.resize(3);
  cout << "\nac1 now contains:   ";
  printArrayClass(ac1);
  cout << "\nac1 should contain: 3 4 5" << endl;
  cout << "\nac1 has size 3: " << endl;
  printResult(ac1.size() == 3);
  cout << "\nac1 has capacity 3: " << endl;
  printResult(ac1.capacity() == 3);

  cout << "\nac1 resized up to 35..." << endl;
  ac1.resize(35);
  cout << "\nac1 now contains:   ";
  printArrayClass(ac1);
  cout << "\nac1 should contain: 3 4 5" << endl;
  cout << "\nac1 has size 3: " << endl;
  printResult(ac1.size() == 3);
  cout << "\nac1 has capacity 35: " << endl;
  printResult(ac1.capacity() == 35);

  cout << "\nCalling popBack 4 times on ac1..." << endl;
  cout << "\nFirst call..." << endl;
  ac1.popBack();
  cout << "\nac1 now contains:   ";
  printArrayClass(ac1);
  cout << "\nac1 should contain: 3 4" << endl;
  cout << "\nac1 has size 2: " << endl;
  printResult(ac1.size() == 2);
  cout << "\nac1 has capacity 35: " << endl;
  printResult(ac1.capacity() == 35);
  cout << "\nac1 is not empty:" << endl;
  printResult(!ac1.empty());
  cout << "\nSecond call..." << endl;
  ac1.popBack();
  cout << "\nac1 now contains:   ";
  printArrayClass(ac1);
  cout << "\nac1 should contain: 3" << endl;
  cout << "\nac1 has size 1: " << endl;
  printResult(ac1.size() == 1);
  cout << "\nac1 has capacity 35: " << endl;
  printResult(ac1.capacity() == 35);
  cout << "\nac1 is not empty:" << endl;
  printResult(!ac1.empty());
  cout << "\nThird call..." << endl;
  ac1.popBack();
  cout << "\nac1 now contains:   ";
  printArrayClass(ac1);
  cout << "\nac1 should contain: " << endl;
  cout << "\nac1 has size 0: " << endl;
  printResult(ac1.size() == 0);
  cout << "\nac1 has capacity 35: " << endl;
  printResult(ac1.capacity() == 35);
  cout << "\nac1 is empty:" << endl;
  printResult(ac1.empty());
  cout << "\nFourth call..." << endl;
  ac1.popBack();
  cout << "\nac1 now contains:   ";
  printArrayClass(ac1);
  cout << "\nac1 should contain: " << endl;
  cout << "\nac1 has size 0: " << endl;
  printResult(ac1.size() == 0);
  cout << "\nac1 has capacity 35: " << endl;
  printResult(ac1.capacity() == 35);
  cout << "\nac1 is empty:" << endl;
  printResult(ac1.empty());

  cout << "\nPushing 6 zeroes to ac1..." << endl;
  for (int i = 0; i < 6; i++)
  {
    ac1.pushBack(0);
  }
  cout << "\nac1 now contains:   ";
  printArrayClass(ac1);
  cout << "\nac1 should contain: 0 0 0 0 0 0 " << endl;
  cout << "\nac1 size is 6:" << endl;
  printResult(ac1.size() == 6);
  cout << "\nac1 capacity is 35:" << endl;
  printResult(ac1.capacity() == 35);

  cout << "\nTesting at()..." << endl;
  cout << "\nChange indices 0, 2, 4 to 1, 2, 3..." << endl;
  ac1.at(0) = 1;
  ac1.at(2) = 2; 
  ac1.at(4) = 3;
  cout << "\nac1 now contains:   ";
  printArrayClass(ac1);
  cout << "\nac1 should contain: 1 0 2 0 3 0 " << endl;
  cout << "\nac1 size is 6:" << endl;
  printResult(ac1.size() == 6);
  cout << "\nac1 capacity is 35:" << endl;
  printResult(ac1.capacity() == 35);
  cout << "\nTry accessing index 6..." << endl;
  try
  {
    cout << ac1.at(ac1.size());
  }
  catch (out_of_range e)
  {
    cout << "PASSED" << endl;
    cout << e.what() << endl;
  }
  cout << "\nTry accessing index -1.." << endl;
  try
  {
    cout << ac1.at(-1);
  }
  catch (out_of_range e)
  {
    cout << "PASSED" << endl;
    cout << e.what() << endl;
  }
  cout << "\nat(4) should return 3: " << endl;
  printResult(ac1.at(4) == 3);

  cout << "\nTesting operator[]..." << endl;
  cout << "\nChange indices 1, 3, 5 to 1, 2, 3..." << endl;
  ac1[1] = 1;
  ac1[3] = 2; 
  ac1[5] = 3;
  cout << "\nac1 now contains:   ";
  printArrayClass(ac1);
  cout << "\nac1 should contain: 1 1 2 2 3 3 " << endl;
  cout << "\nac1 size is 6:" << endl;
  printResult(ac1.size() == 6);
  cout << "\nac1 capacity is 35:" << endl;
  printResult(ac1.capacity() == 35);
  cout << "\nTry accessing index 6..." << endl;
  try
  {
    cout << ac1[ac1.size()];
  }
  catch (out_of_range e)
  {
    cout << "PASSED" << endl;
    cout << e.what() << endl;
  }
  cout << "\nTry accessing index -1.." << endl;
  try
  {
    cout << ac1[-1];
  }
  catch (out_of_range e)
  {
    cout << "PASSED" << endl;
    cout << e.what() << endl;
  }
  cout << "\nac1[4] should return 3: " << endl;
  printResult(ac1[5] == 3);

  cout << "\nA reminder: ac2 contains... ";
  printArrayClass(ac2);
  cout << "\nac2.front() returns 31" << endl;
  printResult(ac2.front() == 31);
  cout << "\nac2.front() == ac2.back()" << endl;
  printResult(ac2.front() == ac2.back());
  cout << "\nac1.front() returns 1" << endl;
  printResult(ac1.front() == 1);
  cout << "\nac1.back() returns 3" << endl;
  printResult(ac1.back() == 3);  

  cout << "\nAssigning ac2 = ac1" << endl;
  ac2 = ac1;
  cout << "\nAssigning ac3 = ac1" << endl;
  ArrayClass<int> ac3 = ac1;

  cout << "\nac1 contains:       ";
  printArrayClass(ac1);
  cout << "\nac1 should contain: 1 1 2 2 3 3" << endl;
  cout << "\nac1 has size 6: " << endl;
  printResult(ac1.size() == 6);
  cout << "\nac1 has capacity 35: " << endl;
  printResult(ac1.capacity() == 35);

  cout << "\nac2 contains:       ";
  printArrayClass(ac2);
  cout << "\nac2 should contain: 1 1 2 2 3 3" << endl;
  cout << "\nac2 has size 6: " << endl;
  printResult(ac2.size() == 6);
  cout << "\nac2 has capacity 35: " << endl;
  printResult(ac2.capacity() == 35);

  cout << "\nac3 contains:       ";
  printArrayClass(ac3);
  cout << "\nac3 should contain: 1 1 2 2 3 3" << endl;
  cout << "\nac3 has size 6: " << endl;
  printResult(ac3.size() == 6);
  cout << "\nac3 has capacity 35: " << endl;
  printResult(ac3.capacity() == 35);

  cout << "\nac3.shrinkToFit()..." << endl;
  ac3.shrinkToFit();
  cout << "\nac3 contains:       ";
  printArrayClass(ac3);
  cout << "\nac3 should contain: 1 1 2 2 3 3" << endl;
  cout << "\nac3 has size 6: " << endl;
  printResult(ac3.size() == 6);
  cout << "\nac3 has capacity 6: " << endl;
  printResult(ac3.capacity() == 6);
  cout << "\nac2 has capacity 35: " << endl;
  printResult(ac2.capacity() == 35);
  cout << "\nac1 has capacity 35: " << endl;
  printResult(ac1.capacity() == 35);

  cout << "\nTesting erase() on ac1..." << endl;
  ac1.erase(1);
  cout << "\nac1 contains:       ";
  printArrayClass(ac1);
  cout << "\nac1 should contain: 1 2 2 3 3" << endl;
  cout << "\nac1 has size 5: " << endl;
  printResult(ac1.size() == 5);
  ac1.erase(2);
  cout << "\nac1 contains:       ";
  printArrayClass(ac1);
  cout << "\nac1 should contain: 1 2 3 3" << endl;
  cout << "\nac1 has size 6: " << endl;
  printResult(ac1.size() == 4);
  ac1.erase(2);
  cout << "\nac1 contains:       ";
  printArrayClass(ac1);
  cout << "\nac1 should contain: 1 2 3" << endl;
  cout << "\nac1 has size 6: " << endl;
  printResult(ac1.size() == 3);
  cout << "\nac3 contains:       ";
  printArrayClass(ac3);
  cout << "\nac3 should contain: 1 1 2 2 3 3" << endl;
  cout << "\nTry ac1.erase(ac1.size())" << endl;
  try
  {
    ac1.erase(ac1.size());
  }
  catch (out_of_range e)
  {
    cout << "PASSED" << endl;
    cout << e.what() << endl;
  }
  cout << "\nArbitrary startFrom test..." << endl;
  ac3.startFrom(4);
  cout << "\nac3 contains:       ";
  printArrayClass(ac3);
  cout << "\nac3 should contain: 3 3 1 1 2 2" << endl;
  ac3.startFrom(0);
  cout << "\nac3 contains:       ";
  printArrayClass(ac3);
  cout << "\nac3 should contain: 3 3 1 1 2 2" << endl;
  ac3.startFrom(ac3.size());
  cout << "\nac3 contains:       ";
  printArrayClass(ac3);
  cout << "\nac3 should contain: 3 3 1 1 2 2" << endl;
  ac3.startFrom(ac3.size() + 1);
  cout << "\nac3 contains:       ";
  printArrayClass(ac3);
  cout << "\nac3 should contain: 3 3 1 1 2 2" << endl;

  cout << "\nTesting insert..." << endl;
  ac3.insert(0, 0);
  cout << "\nac3 contains:       ";
  printArrayClass(ac3);
  cout << "\nac3 should contain: 0 3 3 1 1 2 2" << endl;
  cout << "\nac3 has size 7: " << endl;
  printResult(ac3.size() == 7);
  ac3.insert(ac3.size(), 0);
  cout << "\nac3 contains:       ";
  printArrayClass(ac3);
  cout << "\nac3 should contain: 0 3 3 1 1 2 2 0" << endl;
  cout << "\nac3 has size 8: " << endl;
  printResult(ac3.size() == 8);  
  ac3.insert(4, 0);
  cout << "\nac3 contains:       ";
  printArrayClass(ac3);
  cout << "\nac3 should contain: 0 3 3 1 0 1 2 2 0" << endl;
  cout << "\nac3 has size 9: " << endl;
  printResult(ac3.size() == 9);  
  cout << "\nac1 contains:       ";
  printArrayClass(ac1);
  cout << "\nac1 should contain: 1 2 3" << endl;
  cout << "\nTry inserting at size + 1:" << endl;
  try
  {
    ac3.insert(ac3.size() + 1, 5);
  }
  catch (out_of_range e)
  {
    cout << "PASSED\n";
    cout << e.what() << endl;
  }

  ArrayClass<int> ac4;
  cout << "ArrayClass ac4 created. Attempting to call [], at, front, back..." << endl;
  try
  {
    cout << ac4[0];
  }
  catch (out_of_range e)
  {
    cout << "caught exception - ";
    cout << e.what() << endl;
  }
  try
  {
    cout << ac4.at(0);
  }
  catch (out_of_range e)
  {
    cout << "caught exception - ";
    cout << e.what() << endl;
  }
  try
  {
    cout << ac4.front();
  }
  catch (out_of_range e)
  {
    cout << "caught exception - ";
    cout << e.what() << endl;
  }
  try
  {
    cout << ac4.back();
  }
  catch (out_of_range e)
  {
    cout << "caught exception - ";
    cout << e.what() << endl;
  }

  cout << "\nBasic operations with string..." << endl;
  ArrayClass<string> ac5;
  ac5.pushBack("What ");
  ac5.pushBack("is ");
  ac5.pushBack("up???");
  printArrayClass(ac5);

  cout << "Exiting arrayClassTests...\n" << endl;
}

void stackTests()
{
  cout << "Entered stackTests..." << endl;

  Stack<int> st1;
  Stack<string> st2;

  cout << "\nst1 and st2 both empty: " << endl;
  printResult(st1.isEmpty() && st2.isEmpty());

  cout << "Stacks st1 and st2 created. Pushing 10 items to st1 and 5 items to st2..." << endl;
  st1.push(0);
  st1.push(1);
  st1.push(2);
  st1.push(3);
  st1.push(4);
  st1.push(5);
  st1.push(6);
  st1.push(7);
  st1.push(8);
  st1.push(9);

  st2.push("lol");
  st2.push("haha");
  st2.push("jk");
  st2.push("brb");
  st2.push("sup");

  cout << "\nst1.size() is 10" << endl;
  printResult(st1.size() == 10);
  cout << "\nst2.size() is 5" << endl;
  printResult(st2.size() == 5);
  cout << "\nst1 contains:       ";
  printStack(st1);
  cout << "\nst2 should contain: 9 8 7 6 5 4 3 2 1 0" << endl;
  cout << "\nst2 contains:       ";
  printStack(st2);
  cout << "\nst2 should contain: sup brb jk haha lol" << endl;

  cout << "\nCheck peek on full st1: " << endl;
  printResult(st1.peek() == 9);
  cout << "\nCheck peek on full st2: " << endl;
  printResult(st2.peek() == "sup");

  cout << "\nPop both... " << endl;
  st1.pop();
  st2.pop();


  cout << "\nst1.size() is 9" << endl;
  printResult(st1.size() == 9);
  cout << "\nst2.size() is 4" << endl;
  printResult(st2.size() == 4);
  cout << "\nst1 contains:       ";
  printStack(st1);
  cout << "\nst2 should contain: 8 7 6 5 4 3 2 1 0" << endl;
  cout << "\nst2 contains:       ";
  printStack(st2);
  cout << "\nst2 should contain: brb jk haha lol" << endl;

  cout << "\nTesting st3 = st1, st4 = st2..." << endl;
  Stack<int> st3 = st1;
  Stack<string> st4 = st2;
  cout << "\nst3 contains:       ";
  printStack(st3);
  cout << "\nst3 should contain: 8 7 6 5 4 3 2 1 0" << endl;
  cout << "\nst4 contains:       ";
  printStack(st4);
  cout << "\nst4 should contain: brb jk haha lol" << endl;
  cout << "\nPop st3, st4..." << endl;
  st3.pop();
  st4.pop();
  cout << "\nst3 contains:       ";
  printStack(st3);
  cout << "\nst3 should contain: 7 6 5 4 3 2 1 0" << endl;
  cout << "\nst4 contains:       ";
  printStack(st4);
  cout << "\nst4 should contain: jk haha lol" << endl;
  cout << "\nPop st3, st4..." << endl;
  cout << "\nst1 contains:       ";
  printStack(st1);
  cout << "\nst2 should contain: 8 7 6 5 4 3 2 1 0" << endl;
  cout << "\nst2 contains:       ";
  printStack(st2);
  cout << "\nst2 should contain: brb jk haha lol" << endl;

  cout << "\nNone are empty:" << endl;
  printResult(!st1.isEmpty() && !st2.isEmpty() && !st3.isEmpty() && !st4.isEmpty());
  cout << "\nst3.size() is 8:" << endl;
  printResult(st3.size() == 8);
  cout << "\nst4.size() is 3:" << endl;
  printResult(st4.size() == 3);

  cout << "\nEmpty st1, st2..." << endl;
  while(!st1.isEmpty()){
    st1.pop();
  }
  while(!st2.isEmpty()){
    st2.pop();
  }


  try
  {
    cout << st1.peek();
  }
  catch (out_of_range e)
  {
    cout << "PASSED" << endl;
    cout << e.what() << endl;
  }
  try
  {
    cout << st1.pop();
  }
  catch (out_of_range e)
  {
    cout << "PASSED" << endl;
    cout << e.what() << endl;
  }

    try
  {
    cout << st2.peek();
  }
  catch (out_of_range e)
  {
    cout << "PASSED" << endl;
    cout << e.what() << endl;
  }
  try
  {
    cout << st2.pop();
  }
  catch (out_of_range e)
  {
    cout << "PASSED" << endl;
    cout << e.what() << endl;
  }


   cout << "Exiting stackTests...\n" << endl;
}

void queueTests()
{
  cout << "Entered queueTests..." << endl;

  Queue<int> q1;
  Queue<string> q2;

  cout << "\nQueues q1 and q2 created." << endl;
  cout << "\nq1 and q2 empty:" << endl;
  printResult(q1.isEmpty() && q2.isEmpty());
  cout << "\nEnqueueing 5 items to q1 and q2 each." << endl;
  for(int i = 0; i < 5; i++){
    q1.enqueue(i);
  }
  q2.enqueue("h");
  q2.enqueue("e");
  q2.enqueue("l");
  q2.enqueue("l");
  q2.enqueue("o");
  cout << "\nq1 and q2 not empty:" << endl;
  printResult(!q1.isEmpty() && !q2.isEmpty());
  cout << "\nq1 and a2 both have size 5:" << endl;
  printResult(q1.size() == 5 && q2.size() == 5);
  cout << "\nq1 contains:       ";
  printQueue(q1);
  cout << "\nq1 should contain: 0 1 2 3 4" << endl;
  cout << "\nq2 contains:       ";
  printQueue(q2);
  cout << "\nq2 should contain: h e l l o" << endl;
  cout << "\nCreate q3 = q1..." << endl;
  Queue<int> q3 = q1;
  cout << "\nq3 size is 5:"<<endl;
  printResult(q3.size() == 5);
  cout << "\nq3 contains:       ";
  printQueue(q3);
  cout << "\nq3 should contain: 0 1 2 3 4" << endl;
  cout << "\nDequeue from both q1 and q2..." << endl;
  q1.dequeue();
  q2.dequeue();
  cout << "\nq1 and a2 both have size 4:" << endl;
  printResult(q1.size() == 4 && q2.size() == 4);
  cout << "\nq1 contains:       ";
  printQueue(q1);
  cout << "\nq1 should contain: 1 2 3 4" << endl;
  cout << "\nq2 contains:       ";
  printQueue(q2);
  cout << "\nq2 should contain: e l l o" << endl;
  cout << "\nq3 contains:       ";
  printQueue(q3);
  cout << "\nq3 should contain: 0 1 2 3 4" << endl;
  cout << "\nCheck peek on full queues: " << endl;
  printResult(q1.peek() == 1 && q2.peek() == "e" && q3.peek() == 0);

  cout << "\nAdding values 5 through 99 to q1..." << endl;
  for(int i = 5 ; i < 100; i++){
    q1.enqueue(i);
  }
  cout << "\nq1's size is 99:" << endl;
  printResult(q1.size() == 99);
  cout << "\nDequeueing 94 times..." << endl;
  for(int i = 0; i < 94; i++){
    q1.dequeue();
  }
  cout << "\nq1's size is 5:" << endl;
  printResult(q1.size() == 5);
  cout << "\nq1 contains:       ";
  printQueue(q1);
  cout << "\nq1 should contain: 95 96 97 98 99" << endl;

  Queue<string> q4;
  cout << "Queue q4 created. Attempting to call peek, dequeue..." << endl;
  try
  {
    cout << q4.peek();
  }
  catch (out_of_range e)
  {
    cout << "caught exception - ";
    cout << e.what() << endl;
  }
  try
  {
    cout << q4.dequeue();
  }
  catch (out_of_range e)
  {
    cout << "caught exception - ";
    cout << e.what() << endl;
  }

  q2.dequeue();
  printQueue(q2);
  q2.dequeue();
  printQueue(q2);
  q2.enqueue("w");
  q2.enqueue(" ");
  q2.enqueue("a");
  q2.enqueue("n");
  q2.enqueue("d");
  q2.enqueue(" ");
  q2.enqueue("b");
  q2.enqueue("e");
  q2.enqueue("h");
  q2.enqueue("o");
  q2.enqueue("l");
  q2.enqueue("d");
  printQueue(q2);

  cout << "Exiting queueTests...\n" << endl;
}