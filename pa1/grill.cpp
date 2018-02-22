//Implementation of Grill class

#include "grill.h"

//default constructor
Grill::Grill(){}

// Switches the kebabs at pos1 and pos2
// Returns true if positions are valid and swap can be performed
// Returns false if positions are invalid
bool Grill::swap(unsigned int pos1, unsigned int pos2){
	if (rack.elementAt(pos1 - 1) == NULL || 
		rack.elementAt(pos2 - 1) == NULL){
		return false;
	}
	if (pos1 == pos2){
		return true;
	}

	unsigned int gPos;
	unsigned int lPos;

	if(pos1 > pos2){
		gPos = pos1;
		lPos = pos2;
	} else {
		gPos = pos2;
		lPos = pos1;
	}

	if (gPos != rack.size()){	
		Kebab* k1 = rack.removeAt(gPos - 1);
		Kebab* k2 = rack.removeAt(lPos - 1);
		rack.insertAt(k1, lPos - 1);
		rack.insertAt(k2, gPos - 1);
	} else {
		Kebab* k1 = rack.removeAt(gPos - 1);
		Kebab* k2 = rack.removeAt(lPos - 1);
		rack.insertAt(k1, lPos - 1);
		rack.insertBack(k2);
	}	

	return true;
}

// remove and return the kebab at a 1-indexed
// position on the grill
// return NULL if pos invalid
Kebab* Grill::request(unsigned int pos){
	if (rack.elementAt(pos - 1) == NULL){
		return NULL;
	} else {
		return rack.removeAt(pos - 1);
	}
}

// remove and return the leftmost kebab matching
// at least the ingredients of r, in any order
// return NULL if no match found
Kebab* Grill::request(Kebab& r){
	for(size_t pos = 1; pos <= rack.size(); pos++){
		if(rack.elementAt(pos - 1)->hasSameIngredients(r)){
			return rack.removeAt(pos - 1);
		}
	}
	return NULL;
}

void Grill::addKebab(Kebab& n){
	rack.insertBack(&n);
}

// arrange in decreasing order of # of meat items
void Grill::sortByMeat(){
	unsigned int maxPossible = SKEWER_SIZE;
	unsigned int max;
	bool swapped;
	size_t maxIndex;
	unsigned int candNumMeats;

	for(size_t current = 1; current <= rack.size(); current++){
		max = rack.elementAt(current - 1)->numMeats();
		maxIndex = current; // 1-based index
		swapped = false;
		
		//if current == maxPossible, do nothing
		if(max != maxPossible){
			//either find a maxPossible value, or find the max existing
			for(size_t candidate = current + 1; 
				candidate <= rack.size(); candidate++){
				candNumMeats = rack.elementAt(candidate - 1)->numMeats();
				//note use of candidate - 1 since element at is 0-based
				//if maxPossible, swap and break
				if(candNumMeats == maxPossible){
					swap(current, candidate);
					swapped = true;
					break;
				}
				if(candNumMeats > max){
					max = candNumMeats;
					maxIndex = candidate;
				}

			}

			if(!swapped){
				if(max < maxPossible){ maxPossible = max; }
				swap(current, maxIndex);
			}


		}
	}
}

// returns a vector containing the string representation of all
//   kebabs on the grill
std::vector<std::string> Grill::showKebabs() const{
	std::vector<std::string> grillImage;
	for(size_t pos = 1; pos <= rack.size(); pos++){
		grillImage.push_back(rack.elementAt(pos - 1)->listIngredients());
	}
	return grillImage;
}