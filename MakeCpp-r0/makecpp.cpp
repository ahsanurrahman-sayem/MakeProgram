#include<iostream>
#include<string>
#include<fstream>
#include<cstdlib> // Required for the system() function

using namespace std;

int main(int argc, char* argv[]){
	string fname;

	// Check if the user has provided a command-line argument for the filename.
	if(argc == 2){
		// The filename is the second argument in the 'argv' array.
		fname = argv[1];
	} else {
		// If no argument is provided, prompt the user for the filename.
		cout << "Enter your program name: ";
		cin >> fname;
	}
	
	string fullFilename = fname + ".cpp";
	// Open the file stream for output (creation).
	fstream newFile(fullFilename, ios::out);
	
	if(!newFile.is_open()){
		cout << "Error creating file <'" << fullFilename << "'>";
		return 1;
	}

	// Write the basic C++ template code into the new file.
	newFile << "#include<iostream>\n\nusing namespace std;\n\nint main(){\n\n\treturn 0;\n}" << endl;
	newFile.close();
	
	cout << "File '" << fullFilename << "' created successfully." << endl;
	
	// This line constructs and executes the command to open the file with nano.
	system(("nano " + fullFilename).c_str());

	return 0;
}

