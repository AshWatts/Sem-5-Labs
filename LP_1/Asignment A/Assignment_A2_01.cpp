#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

// Structure to represent a macro
struct Macro {
    string name;
    vector<string> parameters;
    vector<string> definition;
};

// Class for the Macro Processor
class MacroProcessor {
public:
    void firstPass(const string& assemblyCode) {
        istringstream iss(assemblyCode);
        string line;
        int lineNum = 0;

        while (getline(iss, line)) {
            line = trim(line);
            if (line.empty() || line[0] == '#') continue;

            // Check for macro definition
            if (line.substr(0, 5) == "MACRO") {
                processMacroDefinition(iss, lineNum);
                continue;
            }

            // Add to intermediate code
            intermediateCode.push_back(line);
            lineNum++;
        }
    }

    void printMNT() const {
        cout << "Macro Name Table (MNT):\n";
        for (const auto& entry : macroNameTable) {
            cout << entry.first << ": " << entry.second << endl;
        }
    }

    void printMDT() const {
        cout << "\nMacro Definition Table (MDT):\n";
        for (const auto& entry : macroDefinitionTable) {
            cout << entry.first << " -> ";
            for (const auto& line : entry.second.definition) {
                cout << line << " ";
            }
            cout << endl;
        }
    }

    void printIntermediateCode() const {
        cout << "\nIntermediate Code:\n";
        for (const auto& line : intermediateCode) {
            cout << line << endl;
        }
    }

private:
    unordered_map<string, Macro> macroDefinitionTable; // MDT
    unordered_map<string, int> macroNameTable;         // MNT
    vector<string> intermediateCode;

    void processMacroDefinition(istringstream& iss, int& lineNum) {
        string line, macroName;
        getline(iss, line);
        line = trim(line);
        macroName = line.substr(0, line.find(' '));

        Macro macro;
        macro.name = macroName;

        // Read macro parameters
        if (line.find('(') != string::npos) {
            size_t start = line.find('(') + 1;
            size_t end = line.find(')');
            string params = line.substr(start, end - start);
            stringstream paramStream(params);
            string param;
            while (getline(paramStream, param, ',')) {
                macro.parameters.push_back(trim(param));
            }
        }

        // Read macro definition until 'MEND'
        while (getline(iss, line)) {
            line = trim(line);
            if (line == "MEND") break;
            macro.definition.push_back(line);
        }

        // Store the macro in MNT and MDT
        macroNameTable[macroName] = macroDefinitionTable.size();
        macroDefinitionTable[macroName] = macro;
    }

    string trim(const string& str) const {
        size_t first = str.find_first_not_of(' ');
        size_t last = str.find_last_not_of(' ');
        return first != string::npos ? str.substr(first, last - first + 1) : "";
    }
};

// Sample assembly code with macros
const string assemblyCode = R"(
START: LOAD A
       ADD B
       MACRO ADDITION(A, B)
       LOAD A
       ADD B
       MEND
       ADDITION(A, B)
       STORE RESULT
       END
)";

int main() {
    cout<<endl<<endl;
    MacroProcessor processor;
    processor.firstPass(assemblyCode);
    processor.printMNT();
    processor.printMDT();
    processor.printIntermediateCode();
    cout<<endl<<endl;
    return 0;
}
