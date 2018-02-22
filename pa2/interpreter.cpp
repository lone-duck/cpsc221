    #include "interpreter.h"

    // default constructor
    Interpreter::Interpreter(){
    }

    // copy constructor
    Interpreter::Interpreter(const Interpreter& itpt){
    	tube = itpt.tube;
    	bin = itpt.bin;
    	sparebin = itpt.sparebin;
    }

    // assignment operator
    Interpreter& Interpreter::operator=(const Interpreter& itpt){
    	if(this == &itpt){return *this;}
    	tube = itpt.tube;
    	bin = itpt.bin;
    	sparebin = itpt.sparebin;
    	return *this;
    }

    // Loads a single instruction into the tube
    // Requires parsing the instruction into operators and operands
    // If tube already contains items, the instruction is loaded
    //   without clearing the tube contents
    // This should inject a "#" operator at the end
    void Interpreter::load(std::string instruction){
    	//NOTE: code heavily "inspired" by: https://stackoverflow.com/questions/289347/using-strtok-with-a-stdstring
    	size_t start, end = 0;
    	std::string delim = " ";
		while (end < instruction.size()) {
			start = end;
			while (start < instruction.size() && (delim.find(instruction[start]) != std::string::npos)) {
		  		start++;  // skip initial whitespace
			}
			end = start;
			while (end < instruction.size() && (delim.find(instruction[end]) == std::string::npos)) {
		  		end++; // skip to end of word
			}
			if (end-start != 0) {  // just ignore zero-length strings.
		  		tube.enqueue(std::string(instruction, start, end-start));
			}
		}
		tube.enqueue("#");
    }



    // Returns whether there are still items in the tube to be processed
    bool Interpreter::hasMoreInstructions(){
    	return !tube.isEmpty();
    }

    // Remove and execute next instruction
    // i.e. until a #, empty tube, print, or other error encountered
    // The output of any operator(s) will be returned
    // If an attempt to execute an operator causes an exception,
    //   throw the caught exception
    std::string Interpreter::next(){
    	std::string elem;
    	std::string output = "";
    	while(!tube.isEmpty()){
    		elem = tube.dequeue();
    		if(elem == "#"){
    			break;
    		}else if(is_operator(elem)){
    			output += execOp(elem);
    		}else if(is_digits(elem)){
    			bin.push(toInt(elem));
    		}else{
    			throw std::invalid_argument("Interpreter::next() : Element is neither an operator nor an operand.\n Value: " + elem);
    		}
    	}
    	return output;
    }

    // Execute remaining instructions
    // The outputs of each instruction will be
    // appended into a single string, separated by the
    // newline character '\n'. The last instruction
    // will NOT be followed by a newline.
    std::string Interpreter::run(){
    	std::string output = "";
    	//while instructions remain in tube, run next
    	while(!tube.isEmpty()){
    		//append output of each instruction
    		output += next();
    		//if tube is not empty, append "\n"
    		if(!tube.isEmpty()){output += "\n";}
    	}
    	//remove last newline
    	output += "\b";

    	if(output == ""){
    		return "\n";
    	}else{
    		return output;
    	}
    }

    // Clears the contents of all member containers (tube, bin, sparebin)
    void Interpreter::clear()  {
    	tube = Queue<std::string>();
    	bin = Stack<int>();
    	sparebin = Stack<int>();
    }

    // executes an operator, returns a string of execution result
    // most operators will return the empty string "", except for RQ, PRINT
    // If an operator causes a container exception, throw the caught exception
    std::string Interpreter::execOp(std::string optr){
    	std::string output = "";
    	if(is_binary(optr)){
    		execBinary(optr);
    	}else if(optr == "RQ"){
    		output += execRQ();
    	}else if(optr == "PRINT"){
    		output += execPRINT();
    	}

    	return output;
    }

    // Exponentiation function calculates x^y
    //   by repeated squaring (refer to HW2)
    // You may implement this either iteratively or recursively
    // PRE: y >= 0
    int Interpreter::recpow(int x, int y){
		if (y <= 0) { return 1; }
		if (y == 1) { return x; }
		int temp = recpow(x, y/2);
		int result = temp*temp;
		if (y % 2 == 0) {
		   return result;
		}
		return result*x;
    }