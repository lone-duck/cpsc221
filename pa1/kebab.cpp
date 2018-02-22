//Implementation of Kebab class

#include "kebab.h"

using namespace std;

// default constructor
Kebab::Kebab(){}

// Adds item to the pointy end of the skewer
//   and returns true if skewer has space to add
//   and item is a valid ingredient
// Returns false if skewer is full or ingredient is invalid
bool Kebab::addIngredient(char item){
	if (skewer.size() == maxlength || !isValidIngredient(item)){
		return false;
	} else {
		skewer.push_back(item);
		return true;
	}
	
}

// Adds the ingredients specified by s using addIngredient
//   up to the capacity of the skewer
void Kebab::buildKebab(std::string s){
	size_t current_char = 0;
	while(skewer.size() < maxlength && current_char < s.size()){
		if(isValidIngredient(s.at(current_char))) {
			addIngredient(s.at(current_char));
		}
		current_char++;
	}
	return;
}

// returns the number of meat items on this kebab
unsigned int Kebab::numMeats() const{
	int meatCount = 0;
	for(size_t i = 0; i < skewer.size(); i++){
		if(skewer[i] == 'b' || skewer[i] == 'B'){ meatCount++; }
	}
	return meatCount;
}

// Returns true iff this kebab contains at least the same collection
// of ingredients as k, in any order
// Note that this kebab may contain more total ingredients than k,
// but will return true as long as this kebab's ingredients is
// a super-multiset of k's ingredients
bool Kebab::hasSameIngredients(Kebab& k) const{
	size_t foundUpper;
	size_t foundLower;
	string thoseIngredients = k.listIngredients();
	string theseIngredients = listIngredients();
	for(size_t i = 0; i < thoseIngredients.size(); i++){
		foundUpper = theseIngredients.find(toupper(thoseIngredients.at(i)));
		foundLower = theseIngredients.find(tolower(thoseIngredients.at(i)));
		if(foundUpper == string::npos && foundLower == string::npos){
			return false; 
		} else if (foundUpper != string::npos){
			theseIngredients.erase(foundUpper, 1);
		} else {
			theseIngredients.erase(foundLower, 1);
		}
	}
	return true;
}

// Returns a string representing the ingredients on this kebab
//   in the order in which they are skewered
std::string Kebab::listIngredients() const{
	string ingredientsList = "";
	for(char item: skewer){
		ingredientsList += item;
	}
	return ingredientsList;
}