// file:        interpreterprivate.h
// author:      Jack S-J, Geoff T
// date:        2017-10-11
// description: private methods for Interpreter
//              Declare and implement your private functions here.
//              Leave blank if you have no private functions to implement.
//              No includes or qualification necessary. Example below:

#ifndef _INTERPRETERPRIVATE_H_
#define _INTERPRETERPRIVATE_H_

#include <string>


//Returns true if str contains only digits, false otherwise.
bool is_digits(const std::string &str){
	if(str.find_first_not_of("0123456789-") != std::string::npos){
	//if any invalid characters contained, false
		return false;
	}else if(str.find("-") == std::string::npos){
	//if no "-" then string contains only digits; true
		return true;
	}else if(str.find("-", 1) != std::string::npos){
	//if a "-" is anywhere other than the first character, return false
		return false;
	}else{
	//all digits except first character which is "-", return true
		return true;
	}
}

//Returns true if str is a valid operator, false otherwise.
bool is_operator(const std::string &str){
	return (str == "#" || str == "RQ" || str == "PRINT" ||
		    str == "+" || str == "-" || str == "*" ||
		    str == "/" || str == "^"); 
}

//Returns true if str is a binary operator, false otherwise.
bool is_binary(const std::string &str){
	return (str == "+" || str == "-" || str == "*" ||
		    str == "/" || str == "^"); 
}

//Executes a binary operation
void execBinary(const std::string &optr){
	//space for left and right operands
	int left, right, result;
	//left is the "deepest"
	right = bin.pop();
	left = bin.pop();
	//evaluate accordingly and enqueue to tube
	if(optr == "+"){
		result = left + right;
		tube.enqueue(toString(result));
	}else if(optr == "-"){
		result = left - right;
		tube.enqueue(toString(result));
	}else if(optr == "*"){
		result = left * right;
		tube.enqueue(toString(result));
	}else if(optr == "/"){
		result = left / right;
		tube.enqueue(toString(result));
	}else{ //optr == ^
		result = recpow(left, right);
		tube.enqueue(toString(result));
	}
	
}

//Executes the RQ operation
std::string execRQ(){
	std::string output = "";
	std::string currString;
	//for each element in bin, append to output string,
	//push to sparebin and enqueue
	while(!bin.isEmpty()){
		currString = toString(bin.peek());
		output += currString + " ";
		sparebin.push(bin.pop());
		tube.enqueue(currString);
	}
	//put all elements in sparebin back in bin
	while(!sparebin.isEmpty()){
		bin.push(sparebin.pop());
	}
	//return output string with final " " removed
	return output + "\b";
}

//Executes print operation
std::string execPRINT(){
	//for each element in tube, append to output string
	std::string output = "";
	while(!tube.isEmpty()){
		output += tube.dequeue() + " ";
	}
	//return output string with final " " removed	
	return output + "\b";
}

//Used for debugging, prints all elements in tube.
//No longer in use.
void printTube(bool before){
	Queue<std::string> tube2 = Queue<std::string>(tube);
	std::string output = "";
	while(!tube2.isEmpty()){
		output += tube2.dequeue() + " ";
		//std::cout << output << std::endl;
		//std::cout << tube2.size() << std::endl;
		//std::cout << tube.size() << std::endl;
	}
	//return output string with final " " removed
	//std::cout <<  output + "\b" << std::endl;
}

#endif