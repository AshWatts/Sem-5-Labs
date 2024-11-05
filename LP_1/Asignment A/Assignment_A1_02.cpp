#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

// Structure for an instruction in intermediate code
struct Instruction {
    string label;
    string opcode;
    string operand;
};

// Class to manage the symbol table
class SymbolTable {
public:
    void addSymbol(const string& label, int address) {
        symbols[label] = address;
    }

    int getAddress(const string& label) {
        return symbols.count(label) ? symbols[label] : -1;
    }

    void print() const {
        cout << "Symbol Table:\n";
        for (const auto& entry : symbols) {
            cout << entry.first << ": " << entry.second << endl;
        }
    }

private:
    unordered_map<string, int> symbols;
};

// Class to manage the literal table
class LiteralTable {
public:
    void addLiteral(const string& literal, int address) {
        literals[literal] = address;
    }

    int getAddress(const string& literal) {
        return literals.count(literal) ? literals[literal] : -1;
    }

    void print() const {
        cout << "\nLiteral Table:\n";
        for (const auto& entry : literals) {
            cout << entry.first << ": " << entry.second << endl;
        }
    }

private:
    unordered_map<string, int> literals;
};

// Class to manage opcodes
class OpcodeTable {
public:
    OpcodeTable() {
        opcodes = {
            {"LOAD", "01"},
            {"STORE", "02"},
            {"ADD", "03"},
            {"SUB", "04"},
            {"JMP", "05"},
            {"JZ", "06"},
            {"JNZ", "07"}
        };
    }

    string getOpcode(const string& mnemonic) {
        return opcodes.count(mnemonic) ? opcodes[mnemonic] : "";
    }

private:
    unordered_map<string, string> opcodes;
};

// Class for the assembler
class TwoPassAssembler {
public:
    // Inputs for Pass-II
    void initialize(const vector<Instruction>& intermediate, const SymbolTable& symTab, const LiteralTable& litTab) {
        instructions = intermediate;
        symbolTable = symTab;
        literalTable = litTab;
        currentAddress = 0;
    }

    void secondPass() {
        cout << "\nMachine Code:\n";
        for (const auto& instr : instructions) {
            string opcode = instr.opcode;
            string operand = instr.operand;

            // Resolve operand addresses
            if (symbolTable.getAddress(operand) != -1) {
                operand = to_string(symbolTable.getAddress(operand));
            } else if (literalTable.getAddress(operand) != -1) {
                operand = to_string(literalTable.getAddress(operand));
            }

            cout << currentAddress << ": " << opcode << " " << operand << endl;
            currentAddress++;
        }
    }

private:
    vector<Instruction> instructions;
    SymbolTable symbolTable;
    LiteralTable literalTable;
    int currentAddress;
};

// Sample data from Pass-I
const vector<Instruction> intermediateCode = {
    {"", "01", "A"},
    {"", "03", "B"},
    {"", "02", "RESULT"},
    {"", "05", "START"}
};

const string assemblyCode = R"(
START: LOAD A
       ADD B
       STORE RESULT
       JMP START
A:     WORD 5
B:     WORD 10
RESULT: RESW 1
END: EQU START
)";

int main() {
    // cout<<endl<<endl;
    SymbolTable symbolTable;
    symbolTable.addSymbol("START", 0);
    symbolTable.addSymbol("A", 4);
    symbolTable.addSymbol("B", 5);
    symbolTable.addSymbol("RESULT", 6);
    symbolTable.addSymbol("END", 0);

    LiteralTable literalTable;
    literalTable.addLiteral("5", 4);
    literalTable.addLiteral("10", 5);

    // Initialize and execute Pass-II
    TwoPassAssembler assembler;
    assembler.initialize(intermediateCode, symbolTable, literalTable);
    assembler.secondPass();
    cout<<endl<<endl;
    return 0;
}