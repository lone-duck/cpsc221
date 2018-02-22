// File:        main.cpp
// Author:      Geoff T
// Date:        2017-09-18
// Description: Test driver for CPSC 221 PA1
//              Only basic cases are included. You are responsible
//              for adding your own code to thoroughly test all functions of the
//              classes implemented in this assignment.

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>

#include "kebab.h"
#include "linkedlist.h"
#include "grill.h"

using namespace std;

// forward function declarations
void runScriptedTests();
void runInteractiveTest();
void displayMenu();
void handleQueryShowGrill(Grill& grill);
void handleQueryBuyX(Grill& grill);
void handleQueryBuyList(Grill& grill);
void handleQueryNewKebab(Grill& grill);
void handleQuerySwap(Grill& grill);
void handleQuerySort(Grill& grill);
void list_print(LinkedList& ll);
void vec_print(vector<string> strings);

int main()
{
  runScriptedTests();
  runInteractiveTest();

  return 0;
}

void runScriptedTests()
{
  //testing Kebab: 
  //addIngredient - check
  //buildKebab - check
  //numMeats - check
  //hasSameIngredients - check
  //listIngredients - check

  Kebab k1;
  Kebab k2;
  Kebab k3;
  Kebab k4;
  Kebab k5;
  Kebab* k6 = new Kebab;

  cout << "TESTING KEBAB: \n\n\n" << endl;

  cout << "k1 should be empty: " << k1.listIngredients() << endl;
  k1.addIngredient(' ');
  cout << "k1 should be empty: " << k1.listIngredients() << endl;
  k1.buildKebab("bmtbmt");
  cout << "k1 should contain 'bmtbmt': " << k1.listIngredients() << endl;
  k2.buildKebab("");
  cout << "k2 should be empty: " << k2.listIngredients() << endl;
  k2.buildKebab("BmT");
  cout << "k2 should contain 'BmT': " << k2.listIngredients() << endl;
  cout << "k1.numMeats should return 2: " << k1.numMeats() << endl;
  cout << "k2.numMeats should return 1: " << k2.numMeats() << endl;
  k3.buildKebab("tmpsTMPS");
  cout << "k3 should contain 'tmpsTMPS': " << k3.listIngredients() << endl;
  cout << "k3.numMeats should return 0: " << k3.numMeats() << endl;
  k3.addIngredient('b'); 
  cout << "k3 should contain 'tmpsTMPS': " << k3.listIngredients() << endl;
  k4.addIngredient('m');
  cout << "k1.hasSameIngredients(k4) should return 1: " 
  << k1.hasSameIngredients(k4) << endl; 
  cout << "k2.hasSameIngredients(k4) should return 1: " 
  << k2.hasSameIngredients(k4) << endl; 
  cout << "k3.hasSameIngredients(k4) should return 1: " 
  << k3.hasSameIngredients(k4) << endl; 
  cout << "k1.hasSameIngredients(k5) should return 1: " 
  << k1.hasSameIngredients(k5) << endl; 
  cout << "k1.hasSameIngredients(k3) should return 0: "
  << k1.hasSameIngredients(k3) << endl;
  k6->buildKebab("tttttttttttt");
  cout << "ingredients in k6: " << k6->listIngredients() << endl;
  cout << "k1.hasSameIngredients(k2) should return 1: " 
  << k1.hasSameIngredients(k2) << endl;
  cout << "k2.hasSameIngredients(k1) should return 0: " 
  << k2.hasSameIngredients(k1) << endl;


  delete k6;
  k6 = NULL;

  //testing LinkedList:
  //constructor - check
  //copy constructor - check
  //destructor - check
  //insertFront - check
  //insertBack - check
  //insertAt - check
  //removeAt - check
  //size - check
  //isEmpty - check
  //contains - check
  //elementAt - check
  //operator=

  cout << " \n\n\n\nTESTING LINKEDLIST: \n" << endl;


  LinkedList ll1;
  LinkedList ll2;
  LinkedList ll3;
  LinkedList ll4;

  //created to ensure all kebab objects are deleted
  LinkedList deleteList;

  Kebab* b = new Kebab;
  Kebab* t = new Kebab;
  Kebab* m = new Kebab;
  Kebab* p = new Kebab;
  Kebab* s = new Kebab;
  b->buildKebab("b");
  t->buildKebab("t");
  m->buildKebab("m");
  p->buildKebab("p");
  s->buildKebab("s");
  Kebab* B = new Kebab;
  Kebab* T = new Kebab;
  Kebab* M = new Kebab;
  Kebab* P = new Kebab;
  Kebab* S = new Kebab;
  B->buildKebab("B");
  T->buildKebab("T");
  M->buildKebab("M");
  P->buildKebab("P");
  S->buildKebab("S");
  Kebab* btmps = new Kebab;
  Kebab* BMT = new Kebab;
  Kebab* bmt = new Kebab;
  Kebab* BmTbMt = new Kebab;
  btmps->buildKebab("btmps");
  BMT->buildKebab("BMT");
  bmt->buildKebab("bmt");
  BmTbMt->buildKebab("BmTbMt");
  deleteList.insertFront(B);
  deleteList.insertFront(T);
  deleteList.insertFront(M);
  deleteList.insertFront(P);
  deleteList.insertFront(S);
  deleteList.insertFront(b);
  deleteList.insertFront(t);
  deleteList.insertFront(m);
  deleteList.insertFront(p);
  deleteList.insertFront(s);
  deleteList.insertFront(btmps);
  deleteList.insertFront(BMT);
  deleteList.insertFront(bmt);

  //test insertFront, insertBack, size, isEmpty
  //elementAt implicitly tested via list_print function
  cout << "Contents of ll1: ";
  list_print(ll1);
  cout << "Expected       : " << "[]" << endl;

  cout << "\n" << endl;
  cout << "Check elementAt returns NULL for out of range index: "
  << (ll1.elementAt(20) == NULL) << endl;

  cout << "\n" << endl;
  cout << "Size of ll1: " << ll1.size() << endl;
  cout << "ll1.isEmpty returns: " << ll1.isEmpty() << endl;
  
  cout << "\n" << endl;
  ll1.insertBack(b);
  cout << "Contents of ll1: ";
  list_print(ll1);
  cout << "Expected       : " << "[b]" << endl;

  cout << "\n" << endl;
  cout << "Size of ll1: " << ll1.size() << endl;
  cout << "ll1.isEmpty returns: " << ll1.isEmpty() << endl;

  cout << "\n" << endl;
  ll1.insertBack(t);
  cout << "Contents of ll1: ";
  list_print(ll1);
  cout << "Expected       : " << "[b, t]" << endl;
  
  cout << "\n" << endl;
  ll1.insertBack(m);
  cout << "Contents of ll1: ";
  list_print(ll1);
  cout << "Expected       : " << "[b, t, m]" << endl;

  cout << "\n" << endl;
  ll1.insertBack(p);
  cout << "Contents of ll1: ";
  list_print(ll1);
  cout << "Expected       : " << "[b, t, m, p]" << endl;

  cout << "\n" << endl;
    ll1.insertBack(s);
  cout << "Contents of ll1: ";
  list_print(ll1);
  cout << "Expected       : " << "[b, t, m, p, s]" << endl;

  cout << "\n" << endl;
  ll1.insertFront(S);
  cout << "Contents of ll1: ";
  list_print(ll1);
  cout << "Expected       : " << "[S, b, t, m, p, s]" << endl;  

  //test removeAt
  cout << "\n" << endl;
  cout << "Remove first item in ll1..." << endl;
  cout << "Expect to remove: S ~ Actually remove: " 
  << ll1.removeAt(0)->listIngredients() <<endl;
  cout << "Contents of ll1: ";
  list_print(ll1);
  cout << "Expected       : " << "[b, t, m, p, s]" << endl;
  cout << "Size of ll1: " << ll1.size() << endl;

  cout << "\n" << endl;
  cout << "Remove last item in ll1..." << endl;
  cout << "Expect to remove: s ~ Actually remove: " 
  << ll1.removeAt(ll1.size() - 1)->listIngredients() <<endl;
  cout << "Contents of ll1: ";
  list_print(ll1);
  cout << "Expected       : " << "[b, t, m, p]" << endl;
  cout << "Size of ll1: " << ll1.size() << endl;

  cout << "\n" << endl;
  cout << "Remove item at position 2 in ll1..." << endl;
  cout << "Expect to remove: m ~ Actually remove: " 
  << ll1.removeAt(2)->listIngredients() <<endl;
  cout << "Contents of ll1: ";
  list_print(ll1);
  cout << "Expected       : " << "[b, t, p]" << endl;
  cout << "Size of ll1: " << ll1.size() << endl;

  cout << "\n" << endl;
  cout << "Remove first item in ll1..." << endl;
  cout << "Expect to remove: b ~ Actually remove: " 
  << ll1.removeAt(0)->listIngredients() <<endl;
  cout << "Contents of ll1: ";
  list_print(ll1);
  cout << "Expected       : " << "[t, p]" << endl;
  cout << "Size of ll1: " << ll1.size() << endl;

  cout << "\n" << endl;
  cout << "Remove first item in ll1..." << endl;
  cout << "Expect to remove: t ~ Actually remove: " 
  << ll1.removeAt(0)->listIngredients() <<endl;
  cout << "Contents of ll1: ";
  list_print(ll1);
  cout << "Expected       : " << "[p]" << endl;
  cout << "Size of ll1: " << ll1.size() << endl;

  cout << "\n" << endl;
  cout << "Remove first item in ll1..." << endl;
  cout << "Expect to remove: p ~ Actually remove: " 
  << ll1.removeAt(0)->listIngredients() <<endl;
  cout << "Contents of ll1: ";
  list_print(ll1);
  cout << "Expected       : " << "[]" << endl;
  cout << "Size of ll1: " << ll1.size() << endl;

  cout << "\n" << endl;
  cout << "Remove first item in ll1..." << endl;
  cout << "Expect to remove: NULL ~ It is null??: " 
  << (ll1.removeAt(0) == NULL) <<endl;
  cout << "Contents of ll1: ";
  list_print(ll1);
  cout << "Expected       : " << "[]" << endl;
  cout << "Size of ll1: " << ll1.size() << endl;

  cout << "\n" << endl;
  cout << "Fill ll1 with 8 b's..." << endl;
  ll1.insertFront(b);
  ll1.insertFront(b);
  ll1.insertFront(b);
  ll1.insertFront(b);
  ll1.insertFront(b);
  ll1.insertFront(b);
  ll1.insertFront(b);
  ll1.insertFront(b);
  cout << "Contents of ll1: ";
  list_print(ll1);
  cout << "Expected       : " << "[b, b, b, b, b, b, b, b]" << endl;

  //test insertAt
  cout << "\n" << endl;
  cout << "Insert BMT at position 4..." << endl;
  ll1.insertAt(BMT, 4);
  cout << "Contents of ll1: ";
  list_print(ll1);
  cout << "Expected       : " << "[b, b, b, b, BMT, b, b, b, b]" << endl;


  cout << "\n" << endl;
  cout << "Insert T at last position..." << endl;
  ll1.insertAt(T, ll1.size());
  cout << "Contents of ll1: ";
  list_print(ll1);
  cout << "Expected       : " << "[b, b, b, b, BMT, b, b, b, b, T]" << endl;

  cout << "\n" << endl;
  cout << "Insert T at position 0..." << endl;
  ll1.insertAt(T, 0);
  cout << "Contents of ll1: ";
  list_print(ll1);
  cout << "Expected       : " << "[T, b, b, b, b, BMT, b, b, b, b, T]" << endl;

  cout << "\n" << endl;
  cout << "Insert T at position 20 (invalid)..." << endl;
  ll1.insertAt(T, 20);
  cout << "Contents of ll1: ";
  list_print(ll1);
  cout << "Expected       : " << "[T, b, b, b, b, BMT, b, b, b, b, T]" << endl;

  //test removing and replacing last element
  cout << "\n" << endl;
  cout << "Remove last item in ll1..." << endl;
  cout << "Expect to remove: T ~ Actually remove: ";
  Kebab* removed = ll1.removeAt(ll1.size() - 1); 
  cout << removed->listIngredients() <<endl;
  cout << "Contents of ll1: ";
  list_print(ll1);
  cout << "Expected       : " << "[T, b, b, b, b, BMT, b, b, b, b]" << endl;
  cout << "Size of ll1: " << ll1.size() << endl;  
  cout << "Add item back in ll1..." << endl;
  ll1.insertBack(removed);
  cout << "Contents of ll1: ";
  list_print(ll1);
  cout << "Expected       : " << "[T, b, b, b, b, BMT, b, b, b, b, T]" << endl;
  cout << "Size of ll1: " << ll1.size() << endl;  
  

  //test copy constructor

  cout << "\n" << endl;
  cout << "Make llCopy from ll1 using copy constructor..." << endl;
  LinkedList llCopy(ll1);
  cout << "Contents of llCopy: ";
  list_print(ll1);
  cout << "Expected          : " << "[T, b, b, b, b, BMT, b, b, b, b, T]" << endl;
  
  cout << "\n" << endl;
  cout << "Make llCopy2 from ll3 (empty list) using copy constructor..." << endl;
  LinkedList llCopy2(ll3);
  cout << "Contents of llCopy2: ";
  list_print(ll3);
  cout << "Expected           : " << "[]" << endl;

  //test contains

  cout << "\n" << endl;
  cout << "Empty ll1..." << endl;
  while(!(ll1.isEmpty())){ll1.removeAt(0);}
  cout << "Contents of ll1: ";
  list_print(ll1);
  cout << "Expected       : " << "[]" << endl;

  cout << "\n" << endl;
  cout << "Check if ll1 contains a Kebab with 'b'..." << endl;
  cout << "Expected: 0 ~ Result: " 
  << ll1.contains(*b) << endl;

  cout << "\n" << endl;
  cout << "Add some Kebabs to ll1..." << endl;
  ll1.insertFront(BMT);
  ll1.insertFront(T);
  ll1.insertFront(S);
  ll1.insertFront(t);
  ll1.insertFront(s);
  ll1.insertFront(m);
  ll1.insertFront(M); 
  ll1.insertFront(M);
  cout << "Contents of ll1: ";
  list_print(ll1);

  cout << "\n" << endl;
  cout << "Check if ll1 contains a Kebab with 'p'..." << endl;
  cout << "Expected: 0 ~ Result: " 
  << ll1.contains(*p) << endl;

  cout << "\n" << endl;
  cout << "Check if ll1 contains a Kebab with 'bmt'..." << endl;
  cout << "Expected: 1 ~ Result: " 
  << ll1.contains(*bmt) << endl;

  cout << "\n" << endl;
  cout << "Check if ll1 contains a Kebab with 'btmps'..." << endl;
  cout << "Expected: 0 ~ Result: " 
  << ll1.contains(*btmps) << endl;

  cout << "\n" << endl;
  cout << "Check if ll1 contains a Kebab with 'b'..." << endl;
  cout << "Expected: 1 ~ Result: " 
  << ll1.contains(*b) << endl;

  cout << "\n" << endl;
  cout << "Check if ll1 contains a Kebab with 'BmTbMt'..." << endl;
  cout << "Expected: 0 ~ Result: " 
  << ll1.contains(*BmTbMt) << endl;

  cout << "\n" << endl;
  cout << "Create ll2..." << endl;
  ll2.insertFront(BmTbMt);
  cout << "Contents of ll2: ";
  list_print(ll2);
  cout << "Check if ll2 contains a Kebab with 'bmt'..." << endl;
  cout << "Expected: 1 ~ Result: " 
  << ll1.contains(*bmt) << endl;
  cout << "Check if ll2 contains a Kebab with 'BMT'..." << endl;
  cout << "Expected: 1 ~ Result: " 
  << ll1.contains(*BMT) << endl;

  //test operator=
  LinkedList* locBefore = &ll1;
  ll1 = ll1;
  cout << "\n" << endl;
  cout << "Check if ll1's location is the same after ll1 = ll1 runs..." << endl;
  cout << "Expected: 1 ~ Result: " << (locBefore == &ll1) << endl;

  //ll1 must be emptied to avoid double delete
  while(!(ll1.isEmpty())){ll1.removeAt(0);} 
  cout << "\n" << endl;
  cout << "Check that after running ll1 = llCopy, contents are the same but addresses differ..." << endl;
  ll1 = llCopy;
  cout << "String representations equal: " << endl;
  cout << "llCopy: ";
  list_print(llCopy);
  cout << "ll1:    ";
  list_print(ll1);
  cout << "Location not equal: Expected: 1 ~ Result: " << (&llCopy != &ll1) << endl;

  while(!(ll1.isEmpty())){ll1.removeAt(0);}


  //Testing Grill...
  //constructor - check
  //swap - check
  //request(int) - check
  //request(Kebab&) - check
  //addKebab - check
  //sortByMeat - 
  //showKebabs - check

  //variables for testing
  Kebab* gk1 = new Kebab;
  Kebab* gk2 = new Kebab;
  Kebab* gk3 = new Kebab;
  Kebab* gk4 = new Kebab;
  Kebab* gk5 = new Kebab;

  gk1->buildKebab("btmpssssss");
  gk2->buildKebab("bbbbbbbbbb");
  gk3->buildKebab("TmPbPpbsYII");
  gk4->buildKebab("m");
  gk5->buildKebab("sbsbsbsbsbsbsbsbs");

  cout << " \n\n\n\nTESTING GRILL: \n" << endl;

  //create grill
  cout << "\n" << endl;
  cout << "Creating Grill object..." << endl;
  Grill g;

  cout << "\n" << endl;
  cout << "Grill contains: " << endl;
  cout << "Expected: []" << endl;
  cout << "Result:   ";
  vec_print(g.showKebabs());

  //testing adding items to grill
  g.addKebab(*gk1);
  cout << "\n" << endl;
  cout << "Grill contains: " << endl;
  cout << "Expected: [btmpssss]" << endl;
  cout << "Result:   ";
  vec_print(g.showKebabs());

  g.addKebab(*gk2);
  cout << "\n" << endl;
  cout << "Grill contains: " << endl;
  cout << "Expected: [btmpssss, bbbbbbbb]" << endl;
  cout << "Result:   ";
  vec_print(g.showKebabs());

  g.addKebab(*gk3);
  cout << "\n" << endl;
  cout << "Grill contains: " << endl;
  cout << "Expected: [btmpssss, bbbbbbbb, TmPbPpbs]" << endl;
  cout << "Result:   ";
  vec_print(g.showKebabs());

  g.addKebab(*gk4);
  cout << "\n" << endl;
  cout << "Grill contains: " << endl;
  cout << "Expected: [btmpssss, bbbbbbbb, TmPbPpbs, m]" << endl;
  cout << "Result:   ";
  vec_print(g.showKebabs());

  g.addKebab(*gk5);
  cout << "\n" << endl;
  cout << "Grill contains: " << endl;
  cout << "Expected: [btmpssss, bbbbbbbb, TmPbPpbs, m, sbsbsbsb]" << endl;
  cout << "Result:   ";
  vec_print(g.showKebabs());

  //testing swap

  g.swap(1,2);
  cout << "\n" << endl;
  cout << "swap(1,2)"<< endl;
  cout << "Grill contains: " << endl;
  cout << "Expected: [bbbbbbbb, btmpssss, TmPbPpbs, m, sbsbsbsb]" << endl;
  cout << "Result:   ";
  vec_print(g.showKebabs());


  g.swap(1,4);
  cout << "\n" << endl;
  cout << "swap(1,4)"<< endl;
  cout << "Grill contains: " << endl;
  cout << "Expected: [m, btmpssss, TmPbPpbs, bbbbbbbb, sbsbsbsb]" << endl;
  cout << "Result:   ";
  vec_print(g.showKebabs());

  g.swap(2,5);
  cout << "\n" << endl;
  cout << "swap(2,5)"<< endl;
  cout << "Grill contains: " << endl;
  cout << "Expected: [m, sbsbsbsb, TmPbPpbs, bbbbbbbb, btmpssss]" << endl;
  cout << "Result:   ";
  vec_print(g.showKebabs());

  g.swap(3,4);
  cout << "\n" << endl;
  cout << "swap(3,4)"<< endl;
  cout << "Grill contains: " << endl;
  cout << "Expected: [m, sbsbsbsb, bbbbbbbb, TmPbPpbs, btmpssss]" << endl;
  cout << "Result:   ";
  vec_print(g.showKebabs());

  g.swap(3,7);
  cout << "\n" << endl;
  cout << "swap(3,7)"<< endl;
  cout << "Grill contains: " << endl;
  cout << "Expected: [m, sbsbsbsb, bbbbbbbb, TmPbPpbs, btmpssss]" << endl;
  cout << "Result:   ";
  vec_print(g.showKebabs());

  //test remove(int)
  Kebab* req1 = g.request(1);
  cout << "\n" << endl;
  cout << "g.request(1); expected: m ~ actual: " << req1->listIngredients() << endl;
  cout << "Grill contains: " << endl;
  cout << "Expected: [sbsbsbsb, bbbbbbbb, TmPbPpbs, btmpssss]" << endl;
  cout << "Result:   "; 
  vec_print(g.showKebabs());
  cout << "put it back..." << endl;
  g.addKebab(*req1);
  cout << "Grill contains: " << endl;
  cout << "Expected: [sbsbsbsb, bbbbbbbb, TmPbPpbs, btmpssss, m]" << endl;
  cout << "Result:   "; 
  vec_print(g.showKebabs());
  cout << "remove again, from back..." << endl;
  req1 = g.request(5);
  cout << "Grill contains: " << endl;
  cout << "Expected: [sbsbsbsb, bbbbbbbb, TmPbPpbs, btmpssss]" << endl;
  cout << "Result:   "; 
  vec_print(g.showKebabs());
  cout << "put it back, again..." << endl;
  g.addKebab(*req1);
  cout << "Grill contains: " << endl;
  cout << "Expected: [sbsbsbsb, bbbbbbbb, TmPbPpbs, btmpssss, m]" << endl;
  cout << "Result:   "; 
  vec_print(g.showKebabs());

  //test remove()
  req1 = new Kebab;
  req1->buildKebab("tmpp");
  Kebab* req2 = g.request(*req1);
  cout << "\n" << endl;
  cout << "g.request(tmpp); expected: TmPbPpbs ~ actual: " << req2->listIngredients() << endl;
  cout << "Grill contains: " << endl;
  cout << "Expected: [sbsbsbsb, bbbbbbbb, btmpssss, m]" << endl;
  cout << "Result:   "; 
  vec_print(g.showKebabs());
  cout << "Add back, as well as requesting kebab... " << endl;
  g.addKebab(*req2);
  cout << "Grill contains: " << endl;
  cout << "Expected: [sbsbsbsb, bbbbbbbb, btmpssss, m, TmPbPpbs]" << endl;
  cout << "Result:   "; 
  vec_print(g.showKebabs());
  g.addKebab(*req1);
  cout << "Grill contains: " << endl;
  cout << "Expected: [sbsbsbsb, bbbbbbbb, btmpssss, m, TmPbPpbs, tmpp]" << endl;
  cout << "Result:   "; 
  vec_print(g.showKebabs());  

  req1 = new Kebab;
  req1->buildKebab("pppp");
  req2 = g.request(*req1);
  cout << "\n" << endl;
  cout << "g.request(tmpp) returns NULL; expected: 1~ actual: " << (req2 == NULL) << endl;
  cout << "Grill contains: " << endl;
  cout << "Expected: [sbsbsbsb, bbbbbbbb, btmpssss, m, TmPbPpbs, tmpp]" << endl;
  cout << "Result:   "; 
  vec_print(g.showKebabs());
  cout << "Add requesting kebab" << endl;
  g.addKebab(*req1);
  cout << "Grill contains: " << endl;
  cout << "Expected: [sbsbsbsb, bbbbbbbb, btmpssss, m, TmPbPpbs, tmpp, pppp]" << endl;
  cout << "Result:   "; 
  vec_print(g.showKebabs());  

  //test sortByMeat
  g.sortByMeat();
  cout << "\n" << endl;
  cout << "Testing sortByMeat..." << endl;
  cout << "Grill contains: " << endl;
  cout << "Expected: [bbbbbbbb, sbsbsbsb, TmPbPpbs, btmpssss, m, tmpp, pppp]" << endl;
  cout << "Result:   "; 
  vec_print(g.showKebabs());  

  while(!(ll1.isEmpty())){ll1.removeAt(0);}
}

void runInteractiveTest()
{
  // create a Grill and populate it with some Kebabs
  Grill g;
  Kebab* freshkebab;
  freshkebab = new Kebab();
  freshkebab->buildKebab("TMTBPP");
  g.addKebab(*freshkebab);
  freshkebab = new Kebab();
  freshkebab->buildKebab("B 3%#SN,M[PM TBSB54M,ZDROB8RTZ3 564 /][98Z3");
  g.addKebab(*freshkebab);
  freshkebab = new Kebab();
  freshkebab->buildKebab("BMB");
  g.addKebab(*freshkebab);

  string inputchoice = "";
  int choice = 0;

  while (choice != 8)
  {
    displayMenu();
    // get the menu choice from standard input
    getline(cin, inputchoice);
    choice = atoi(inputchoice.c_str());

    switch (choice)
    {
    case 1: // See the kebabs
      handleQueryShowGrill(g);
      break;
    case 2: // Buy a kebab by pointing
      handleQueryBuyX(g);
      break;
    case 3: // Buy a kebab by listing ingredients
      handleQueryBuyList(g);
      break;
    case 4: // Make a new kebab
      handleQueryNewKebab(g);
      break;
    case 5: // Swap two kebabs on the grill
      handleQuerySwap(g);
      break;
    case 6: // Descending sort the kebabs by meat amount
      handleQuerySort(g);
      break;
    case 8: // End
      cout << "Thank you, come again!" << endl;
      break;
    default: // invalid option
      cout << "Invalid choice." << endl;
      break;
    }
  }
}

// prints the options menu to screen
void displayMenu()
{
  cout << "*****************************************\n"
       << "* Welcome to Speedy Kebab terminal      *\n"
       << "* What would you like to do?            *\n"
       << "*                                       *\n"
       << "* Customer operations:                  *\n"
       << "* 1. See the kebabs on the grill        *\n"
       << "* 2. Buy a kebab by number              *\n"
       << "* 3. Buy a kebab by listing ingredients *\n"
       << "*                                       *\n"
       << "* Staff operations:                     *\n"
       << "* 4. Make a new kebab                   *\n"
       << "* 5. Swap two kebabs                    *\n"
       << "* 6. Sort by meat amounts               *\n"
       << "*                                       *\n"
       << "* 8. End                                *\n"
       << "*****************************************" << endl;
  cout << "Please enter your choice: ";
}

void handleQueryShowGrill(Grill& grill)
{
  vector<string> kebabs = grill.showKebabs();
  int numkebabs = kebabs.size();
  // pad all kebab strings with " " to make them SKEWER_SIZE
  for (int i = 0; i < numkebabs; i++)
  {
    if (kebabs[i].length() < SKEWER_SIZE)
    {
      while (kebabs[i].length() < SKEWER_SIZE)
        kebabs[i] = kebabs[i] + " ";
    }
    cout << i + 1 << "\t";
  }
  cout << endl;
  for (int i = 0; i < numkebabs; i++)
    cout << "~~~\t";
  cout << endl;
  for (int chars = 0; chars < SKEWER_SIZE; chars++)
  {
    for (int k = 0; k < numkebabs; k++)
    {
      cout << kebabs[k][chars] << "\t";
    }
    cout << endl;
  }
}

void handleQueryBuyX(Grill& grill)
{
  string inputchoice = "";
  int choice = 0;
  cout << "Enter the number of the kebab: ";
  getline(cin, inputchoice);
  choice = atoi(inputchoice.c_str());
  Kebab* purchased = grill.request((unsigned int)choice);
  if (purchased != NULL)
    cout << "Thank you, enjoy!\n" << endl;
  else
    cout << "Sorry, I cannot help you with that.\n" << endl;
  delete purchased;
}

void handleQueryBuyList(Grill& grill)
{
  string wanted;
  cout << "Enter the first character of each ingredient you want: ";
  getline(cin, wanted);
  Kebab wantedkebab;
  wantedkebab.buildKebab(wanted);
  Kebab* purchased = grill.request(wantedkebab);
  if (purchased != NULL)
    cout << "Thank you, enjoy!\n" << endl;
  else
    cout << "Sorry, I cannot help you with that.\n" << endl;
  delete purchased;
}

void handleQueryNewKebab(Grill& grill)
{
  string ilist;
  cout << "Enter the first character of each ingredient to use: ";
  getline(cin, ilist);
  Kebab* freshkebab = new Kebab();
  freshkebab->buildKebab(ilist);
  grill.addKebab(*freshkebab);
  cout << "A fresh kebab is on the grill!\n" << endl;
}

void handleQuerySwap(Grill& grill)
{
  string inputchoice = "";
  int k1 = 0;
  cout << "Enter the number of the first kebab: ";
  getline(cin, inputchoice);
  k1 = atoi(inputchoice.c_str());
  int k2 = 0;
  cout << "Enter the number of the second kebab: ";
  getline(cin, inputchoice);
  k2 = atoi(inputchoice.c_str());
  if (grill.swap((unsigned int)k1, (unsigned int)k2))
    cout << "Kebabs swapped.\n" << endl;
  else
    cout << "Sorry, you cannot do that.\n" << endl;
}

void handleQuerySort(Grill& grill)
{
  grill.sortByMeat();
  cout << "More meat on the left!\n" << endl;
}

void list_print(LinkedList& ll){
  cout << "[";
  for(int i = 0; i < ll.size(); i++){
    cout << ll.elementAt(i)->listIngredients();
    if(i != ll.size() - 1){ cout << ", ";}
  }
  cout << "]" << endl;
}

void vec_print(vector<string> strings){
  cout << "[";
  for(int i = 0; i < strings.size(); i++){
    cout << strings[i];
    if(i != strings.size() - 1){ cout << ", ";}
  }
  cout << "]" << endl;
}

