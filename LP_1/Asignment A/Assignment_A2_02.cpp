#include <bits/stdc++.h>

using namespace std;

// Structure to represent a macro
struct Macro {
    vector<string> parameters;
    vector<string> definition;
};

// Class for the Macro Processor
class MacroProcessor {
public:
    void initialize(const unordered_map<string, Macro>& mnt,
                    const unordered_map<string, Macro>& mdt,
                    const vector<string>& intermediate) {
        // macroNameTable = mnt;
        macroDefinitionTable = mdt;
        intermediateCode = intermediate;
    }

    void secondPass() {
        cout << "\nExpanded Code:\n";
        for (const auto& line : intermediateCode) {
            if (line.find("MEND") != string::npos) continue;

            stringstream ss(line);
            string token;
            ss >> token;

            // Check if token is a macro call
            if (macroNameTable.find(token) != macroNameTable.end()) {
                expandMacro(token, ss);
            } else {
                cout << line << endl; // Print regular line
            }
        }
    }

private:
    unordered_map<string, Macro> macroDefinitionTable; // MDT
    unordered_map<string, int> macroNameTable;         // MNT
    vector<string> intermediateCode;

    void expandMacro(const string& macroName, stringstream& ss) {
        Macro macro = macroDefinitionTable[macroName];
        cout << "Expanding macro: " << macroName << endl;

        vector<string> args;
        string arg;
        while (ss >> arg) {
            args.push_back(arg);
        }

        // Replace parameters with arguments in the macro definition
        for (const auto& line : macro.definition) {
            string expandedLine = line;
            for (size_t i = 0; i < macro.parameters.size(); ++i) {
                expandedLine = replaceParameter(expandedLine, macro.parameters[i], args[i]);
            }
            cout << expandedLine << endl;
        }
    }

    string replaceParameter(const string& line, const string& param, const string& value) {
        string result = line;
        size_t pos = 0;
        while ((pos = result.find(param, pos)) != string::npos) {
            result.replace(pos, param.length(), value);
            pos += value.length();
        }
        return result;
    }
};

// Sample MNT, MDT, and Intermediate Code from Pass-I
unordered_map<string, Macro> macroDefinitionTable = {
    {"ADDITION", {{"A", "B"}, {"LOAD A", "ADD B"}}}
};

unordered_map<string, int> macroNameTable = {
    {"ADDITION", 0}
};

vector<string> intermediateCode = {
    "START: LOAD A",
    "ADD B",
    "ADDITION A, B",
    "STORE RESULT",
    "END"
};

int main() {
    MacroProcessor processor;
    // processor.initialize(macroNameTable, macroDefinitionTable, intermediateCode);
    processor.secondPass();

    return 0;
}
