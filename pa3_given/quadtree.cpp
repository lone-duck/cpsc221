/**
 * @file quadtree.cpp
 * Quadtree class implementation.
 */

#include <cstddef>
#include <cstdlib>
#include <iostream>

using namespace std;

#include "quadtree.h"
#include "png.h"

// Quadtree
//   - parameters: none
//   - constructor for the Quadtree class; makes an empty tree
Quadtree::Quadtree() : root(NULL), res(0){
}

// Quadtree
//   - parameters: PNG const & source - reference to a const PNG
//                    object, from which the Quadtree will be built
//                 int resolution - resolution of the portion of source
//                    from which this tree will be built
//   - constructor for the Quadtree class; creates a Quadtree representing
//        the resolution by resolution block in the upper-left corner of
//        source
Quadtree::Quadtree(PNG const& source, int setresolution): Quadtree() {
	res = setresolution;
	buildTree(source, setresolution);
}

// Quadtree
//   - parameters: Quadtree const & other - reference to a const Quadtree
//                    object, which the current Quadtree will be a copy of
//   - copy constructor for the Quadtree class
Quadtree::Quadtree(Quadtree const& other): root(copy(other.root)), res(other.res) {
}

// ~Quadtree
//   - parameters: none
//   - destructor for the Quadtree class
Quadtree::~Quadtree(){
	clear(root);
}

// operator=
//   - parameters: Quadtree const & other - reference to a const Quadtree
//                    object, which the current Quadtree will be a copy of
//   - return value: a const reference to the current Quadtree
//   - assignment operator for the Quadtree class
Quadtree const& Quadtree::operator=(Quadtree const& other){
	//inspiration taken from lab_trees
	if (this != &other){
		clear(root);
		res = other.res;
		root = copy(other.root);
	}
	return *this;
}

// buildTree (public interface)
//   - parameters: PNG const & source - reference to a const PNG
//                    object, from which the Quadtree will be built
//                 int resolution - resolution of the portion of source
//                    from which this tree will be built
//   - transforms the current Quadtree into a Quadtree representing
//        the resolution by resolution block in the upper-left corner of
//        source
void Quadtree::buildTree(PNG const& source, int setresolution){
	
	//clear the contents of this tree, copy resolution
	//and contents of source
	clear(root);
	res = setresolution;
	root = buildTree(source, 0, 0, res);
}

// getPixel (public interface)
//   - parameters: int x, int y - coordinates of the pixel to be retrieved
//   - return value: an RGBAPixel representing the desired pixel of the
//        underlying bitmap
//   - retrieves and returns the pixel at coordinates (x, y) in the
//        underlying bitmap
RGBAPixel Quadtree::getPixel(int x, int y) const {
	
	//if index is invalid or tree is empty, return default pixel
	if(x >= res || y >= res || x < 0 || y < 0 || root == NULL){
		return RGBAPixel();
	//otherwise, use recursive getPixel to locate
	} else {
		return getPixel(root, 0, 0, res, x, y);
	}
}

// decompress (public interface)
//   - parameters: none
//   - return value: a PNG object representing this quadtree's underlying
//        bitmap
//   - constructs and returns this quadtree's underlying bitmap
PNG Quadtree::decompress() const{
	
	//if tree is empty, return default PNG
	if(root == NULL){
		return PNG();
	}

	//otherwise, create default png of size res
	PNG image(res, res);
	//call recursive decompress with this image
	decompress(root, image, 0, 0, res);
	return image;

}

/**
* Recursive private helper method for decompress.
* Recursively fills in a PNG images pixels with Quadtrees underlying 
* bitmap. If a node has been pruned, "blocks out" the region it 
* corresponds to with that node's pixel. 
*/
void Quadtree::decompress(QuadtreeNode* subRoot, PNG& image, int local_x0,
	int local_y0, int local_res) const {
	
	//if this node is a leaf (pruned or otherwise)...
	if(subRoot->nwChild == NULL){
		//assign the square that corresponds to this node
		//in the PNG to be this node's pixel
		for(int x = local_x0; x < local_x0 + local_res; x++){
			for(int y = local_y0; y < local_y0 + local_res; y++){
				*image(x, y) = subRoot->element;
			}
		}
	//otherwise, recursively do this operation on all descendants
	}else{
		decompress(subRoot->nwChild, image, local_x0, local_y0,
		 local_res/2);
		decompress(subRoot->neChild, image, local_x0 + local_res/2,
		 local_y0, local_res/2);
		decompress(subRoot->swChild, image, local_x0,
		 local_y0 + local_res/2, local_res/2);
		decompress(subRoot->seChild, image, local_x0 + local_res/2,
		 local_y0 + local_res/2, local_res/2);
	}
}

// clockwiseRotate (public interface)
//   - parameters: none
//   - transforms this quadtree into a quadtree representing the same
//        bitmap, rotated 90 degrees clockwise
void Quadtree::clockwiseRotate(){

	//in the single pixel or empty tree case, trivial operation
	if(res == 1 || root == NULL){
		return;
	}

	//call recursive clockwiseRotate
	clockwiseRotate(root);
}

// Private recursive helper function for clockwiseRotate
void Quadtree::clockwiseRotate(QuadtreeNode* subRoot){

	//if leaf, do nothing
	if(subRoot->nwChild == NULL){
		return;
	}

	//rotate this nodes children
	QuadtreeNode* temp = subRoot->nwChild;
	subRoot->nwChild = subRoot->swChild;
	subRoot->swChild = subRoot->seChild;
	subRoot->seChild = subRoot->neChild;
	subRoot->neChild = temp;
	//recursively rotate grandchildren, etc.
	clockwiseRotate(subRoot->nwChild);
	clockwiseRotate(subRoot->neChild);
	clockwiseRotate(subRoot->swChild);
	clockwiseRotate(subRoot->seChild);

}



// prune (public interface)
//   - parameters: int tolerance - an integer representing the maximum
//                    "distance" which we will permit between a node's color
//                    (i.e. the average of its descendant leaves' colors)
//                    and the color of each of that node's descendant leaves
//   - for each node in the quadtree, if the "distance" between the average
//        of that node's descendant leaves' colors and the color of each of
//        that node's descendant leaves is at most tolerance, this function
//        deletes the subtrees beneath that node; we will let the node's
//        color "stand in for" the colors of all (deleted) leaves beneath it
void Quadtree::prune(int tolerance){
	
	//cannot prune empty tree
	if(root == NULL){
		return;
	}

	//call recursive prune
	prune(root, tolerance);
}

/**
* Recursive helper method for prune.
* @param subRoot root of subtree to be pruned
* @param tolerance the given tolerance
*/
void Quadtree::prune(QuadtreeNode* subRoot, int tolerance){

	//base case; if no children, cannot prune.
	if(subRoot->nwChild == NULL){
		return;
	}

	//check if node is prunable (tolerance condition met)
	if(isPrunable(subRoot, tolerance)){
		//clear all children. 
		//subroot's element already contains the average.
		clear(subRoot->nwChild);
		clear(subRoot->neChild);
		clear(subRoot->swChild);
		clear(subRoot->seChild);
		subRoot->nwChild = NULL;
		subRoot->neChild = NULL;
		subRoot->swChild = NULL;
		subRoot->seChild = NULL;
	} else {
		//prune all subtrees
		prune(subRoot->nwChild, tolerance);
		prune(subRoot->neChild, tolerance);
		prune(subRoot->swChild, tolerance);
		prune(subRoot->seChild, tolerance);
	}


}


/**
* Helper function for prune.
* Given a tolerance, determines whether the passed node is
* prunable or not.
* @param subRoot The node to be checked
* @param tolerance The tolerance
*/
bool Quadtree::isPrunable(const QuadtreeNode* subRoot, int tolerance) const {

	//cannot prune a leaf
	if(subRoot->nwChild == NULL){
		return false;
	}

	//compare this node's element with all leaves
	return leafCompare(subRoot->element, subRoot->nwChild, tolerance) &&
		   leafCompare(subRoot->element, subRoot->neChild, tolerance) &&
		   leafCompare(subRoot->element, subRoot->swChild, tolerance) &&
		   leafCompare(subRoot->element, subRoot->seChild, tolerance);
}

/**
* Helper function for isPrunable. Given a pixel, a subtree, and a tolerance,
* returns true if pixels of all leaves of this subtree are within tolerance
* of parameter px.
* @param px the comparison pixel
* @param subRoot the root of the subtree to be checked
* @param tolerance the given tolerance
*/ 
bool Quadtree::leafCompare(const RGBAPixel& px, const QuadtreeNode* subRoot, int tolerance) const {
	//base case, we've reach a leaf
	if(subRoot->nwChild == NULL){
		//check that this leaf's elemenet is within tolerance
		return(colorDistance(px, subRoot->element) <= tolerance);
	} else {
		//return AND of all lower leaf compares
		return leafCompare(px, subRoot->nwChild, tolerance) &&
	           leafCompare(px, subRoot->neChild, tolerance) &&
	           leafCompare(px, subRoot->swChild, tolerance) &&
	           leafCompare(px, subRoot->seChild, tolerance);
	}
}

/**
* Determines the distance between the colors of two pixels
*/
int Quadtree::colorDistance(const RGBAPixel& px1, const RGBAPixel& px2) const{
	return (px2.red - px1.red) * (px2.red - px1.red) +
		   (px2.green - px1.green) * (px2.green - px1.green) +
		   (px2.blue - px1.blue) * (px2.blue - px1.blue); 

}

// pruneSize (public interface)
//   - parameters: int tolerance - an integer representing the maximum
//                    "distance" which we will permit between a node's color
//                    (i.e. the average of its descendant leaves' colors)
//                    and the color of each of that node's descendant leaves
//   - returns the number of leaves which this quadtree would contain if it
//        was pruned using the given tolerance; does not actually modify the
//        tree
int Quadtree::pruneSize(int tolerance) const{
	
	//pruneSize is 0 for a tree of size 0
	if(root == NULL){
		return 0;
	}

	//pass to recursive pruneSize
	return pruneSize(root, tolerance);
}

/**
* Recursive helper for pruneSize. 
*/
int Quadtree::pruneSize(QuadtreeNode* subRoot, int tolerance) const {

	//if this is a leaf or would be made into a leaf when pruned
	//with given tolerance, return 1
	if(subRoot->nwChild == NULL || isPrunable(subRoot, tolerance)){
		return 1;
	//otherwise return sum of pruneSize of children
	} else {
		return pruneSize(subRoot->nwChild, tolerance) +
			   pruneSize(subRoot->neChild, tolerance) +
			   pruneSize(subRoot->swChild, tolerance) +
			   pruneSize(subRoot->seChild, tolerance);
	}


}

// idealPrune (public interface)
//   - parameters: int numLeaves - an integer representing the number of
//                    leaves we wish the quadtree to have, after pruning
//   - returns the minimum tolerance such that pruning with that tolerance
//        would yield a tree with at most numLeaves leaves
int Quadtree::idealPrune(int numLeaves) const{	
	//performs a lower bound binary search on the possible 
	//range of tolerances. Inspired by code from various stack
	//posts and the like.
	int low = 0;
	int high = 3*255*255;
	while(low < high){
		int mid = (low + high) / 2;
		if(numLeaves >= pruneSize(mid)){
			high = mid;
		}else{
			low = mid + 1;
		}
	}
	return low;
}

// QuadtreeNode
//   - parameters: none
//   - constructor for the QuadtreeNode class; creates an empty
//        QuadtreeNode, with all child pointers NULL
Quadtree::QuadtreeNode::QuadtreeNode()
{
    neChild = seChild = nwChild = swChild = NULL;
}

// QuadtreeNode
//   - parameters: RGBAPixel const & elem - reference to a const
//        RGBAPixel which we want to store in this node
//   - constructor for the QuadtreeNode class; creates a QuadtreeNode
//        with element elem and all child pointers NULL
Quadtree::QuadtreeNode::QuadtreeNode(RGBAPixel const& elem)
{
    element = elem;
    neChild = seChild = nwChild = swChild = NULL;
}

/**
 * Private helper function for clear that clears beneath the parameter node.
 * Largely copied from lab_trees code.
 * @param subRoot The current node in the recursion
 */
void Quadtree::clear(QuadtreeNode* subRoot){
	//if subtree empty, trivial case
	if(subRoot == NULL){
		return;
	}

	//clear all subtrees, delete this subroot
	clear(subRoot->nwChild);
	clear(subRoot->neChild);
	clear(subRoot->swChild);
	clear(subRoot->seChild);
	delete subRoot;


}

/**
* Private recursive buildTree helper function.
* @param source The source image this Quadtree is based on
* @param local_x0 The x coordinate for the upper left pixel of the 
*   square the returned node represents
* @param local_y0 The y coordinate for the upper left pixel of the 
*   square the returned node represents
* @param local_res The resolution of the square the returned node represents
*/
Quadtree::QuadtreeNode* Quadtree::buildTree(PNG const& source, int local_x0, 
	int local_y0, int local_res){
	
	//if local res == 1, return node represents 1 pixel (the one at local_x0, local_y0)
	if (local_res == 1) {
		return new QuadtreeNode(*source(local_x0, local_y0));
	//otherwise...
	} else {
		//construct a new node
		QuadtreeNode* newNode = new QuadtreeNode();
		//children are built accordingly
		newNode->nwChild = buildTree(source, local_x0, 
			local_y0, local_res/2);
		newNode->neChild = buildTree(source, local_x0 + local_res/2, 
			local_y0, local_res/2);
		newNode->swChild = buildTree(source, local_x0, 
			local_y0 + local_res/2, local_res/2);
		newNode->seChild = buildTree(source, local_x0 + local_res/2, 
			local_y0 + local_res/2, local_res/2);
		//element is the average of the elements of it's children
		newNode->element = avgPixel(newNode->nwChild->element, 
			newNode->neChild->element, 
			newNode->swChild->element, 
			newNode->seChild->element);
		return newNode;
	}
}

/**
* Private helper method which returns the "average pixel" of 4 pixels
* @param px1
* @param px2
* @param px3
* @param px4
*/
RGBAPixel Quadtree::avgPixel(RGBAPixel px1, RGBAPixel px2, 
	RGBAPixel px3, RGBAPixel px4) {

	uint8_t avgRed = (px1.red + px2.red + px3.red + px4.red)/4;
	uint8_t avgGreen = (px1.green + px2.green + px3.green + px4.green)/4;
	uint8_t avgBlue = (px1.blue + px2.blue + px3.blue + px4.blue)/4;
	uint8_t avgAlpha = (px1.alpha + px2.alpha + px3.alpha + px4.alpha)/4;
	return RGBAPixel(avgRed, avgGreen, avgBlue, avgAlpha);
}

/**
 * Helper function for operator=, cctor, etc.
 * Largely copied from lab_trees code.
 * @param subRoot The current node in the recursion
 */
Quadtree::QuadtreeNode* Quadtree::copy(const QuadtreeNode* subRoot){
    
    //if this subtree empty, trivial case
    if(subRoot == NULL){
        return NULL;
    }

    //copy the element of this subroot into newNode,
    //copy all subtrees 
    QuadtreeNode* newNode = new QuadtreeNode(subRoot->element);
    newNode->nwChild = copy(subRoot->nwChild);
    newNode->neChild = copy(subRoot->neChild);
    newNode->swChild = copy(subRoot->swChild);
    newNode->seChild = copy(subRoot->seChild);
    return newNode;
}

/**
* Private recursive getPixel helper function.
* @param local_x0 The x coordinate for the upper left pixel of the 
*   square the returned node represents
* @param local_y0 The y coordinate for the upper left pixel of the 
*   square the returned node represents
* @param local_res The resolution of the square the returned node represents
* @param x the x coordinate of the pixel being returned
* @param y the y coordinate of the pixel being returned
*/
RGBAPixel Quadtree::getPixel(Quadtree::QuadtreeNode* subRoot, int local_x0, int local_y0, 
	int local_res, int x, int y) const {
	
	//if any child is empty, all children are.
	//(second condition unnecessary, included for illustration)
	//return this subroot's element
	if(subRoot->nwChild == NULL || local_res == 1){
		return subRoot->element; 
	}
	
	//otherwise do a 2D binary search to find 
	//requested pixel...

	//if x0 < x < x0 + res/2, in west half
	if(x < local_x0 + local_res/2){
		//if y0 < y < y0 + res/2, in north half
		if(y < local_y0 + local_res/2){
			return getPixel(subRoot->nwChild, local_x0, 
				local_y0, local_res/2, x, y);
		//else in south half
		}else{
			return getPixel(subRoot->swChild, local_x0, 
				local_y0 + local_res/2, local_res/2, x, y);
		}
	//else in east half
	}else{
		//if y0 < y < y0 + res/2, in north half
		if(y < local_y0 + local_res/2){
			return getPixel(subRoot->neChild, local_x0 + local_res/2, 
				local_y0, local_res/2, x, y);
		//else in south half
		}else{
			return getPixel(subRoot->seChild, local_x0 + local_res/2, 
				local_y0 + local_res/2, local_res/2, x, y);
		}
	}
	
}









