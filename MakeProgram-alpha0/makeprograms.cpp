#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib> // Required for the system() function

// You will need to download the nlohmann/json header file and place it in the same directory.
// You can get it from: https://github.com/nlohmann/json
//#include "json.hpp"

using namespace std;
using json = nlohmann::json;

int main(int argc, char* argv[]){
    string language;
    
    // Check if a language flag was provided as a command-line argument.
    if(argc != 2){
        cout << "Usage: " << argv[0] << " <language_flag>" << endl;
        cout << "Example: " << argv[0] << " -c" << endl;
        cout << "Available flags are defined in boilerplate.json." << endl;
        return 1;
    }

    // The language flag is the second argument. We'll remove the leading '-' for the key lookup.
    language = argv[1];
    if (language.length() > 1 && language[0] == '-') {
        language = language.substr(1);
    } else {
        cout << "Invalid flag format. Please use a flag like -c or -html." << endl;
        return 1;
    }

    // Attempt to open and parse the JSON file.
    ifstream jsonFile("boilerplate.json");
    if (!jsonFile.is_open()) {
        cout << "Error: Could not open 'boilerplate.json'." << endl;
        cout << "Please ensure the file exists in the same directory." << endl;
        return 1;
    }

    json boilerplateData;
    try {
        jsonFile >> boilerplateData;
    } catch (json::parse_error& e) {
        cout << "Error parsing JSON file: " << e.what() << endl;
        return 1;
    }
    jsonFile.close();

    // Check if the requested language exists in the JSON data.
    if (boilerplateData.find(language) == boilerplateData.end()) {
        cout << "Error: No boilerplate found for language '" << language << "'." << endl;
        return 1;
    }

    // Get the boilerplate code from the JSON object.
    string boilerplateCode = boilerplateData[language];

    // Get the filename from the user.
    string fname;
    cout << "Enter your program name: ";
    cin >> fname;

    // Determine the file extension based on the language.
    string fileExtension;
    if (language == "c") {
        fileExtension = ".c";
    } else if (language == "html") {
        fileExtension = ".html";
    } else {
        fileExtension = "." + language; // Default to the flag as extension.
    }

    string fullFilename = fname + fileExtension;
    
    fstream newFile(fullFilename, ios::out);
    
    if(!newFile.is_open()){
        cout << "Error creating file <'" << fullFilename << "'>";
        return 1;
    }

    // Write the boilerplate code into the new file.
    newFile << boilerplateCode << endl;
    newFile.close();
    
    cout << "File '" << fullFilename << "' created successfully." << endl;
    
    // This line constructs and executes the command to open the file with nano.
    system(("nano " + fullFilename).c_str());

    return 0;
}

