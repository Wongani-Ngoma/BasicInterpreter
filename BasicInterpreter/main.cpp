#include <cstring>
#include <string>
#include <Windows.h>
#include <iostream>

int memorySize = 1000; // In words
int numOfRegisters = 10;

int wordLimit = 1000; // Number after the maximum value each word can support

int numOfCases = 0;

WORD* memoryPtr;
WORD* instrPtr;

WORD* memory;
WORD* registers;

void init() {
    memory = new WORD[memorySize];
    registers = new WORD[numOfRegisters];

    memoryPtr = memory;
    instrPtr = memory;

    std::memset(memory, 0, sizeof(WORD) * memorySize);
    std::memset(registers, 0, sizeof(WORD) * numOfRegisters);
}

void printMemory() {
    std::cout << "!!!! DEBUG !!!!!\n";
    std::cout << "\n========= Memory ==========\n";
    for (int i = 0; i < memorySize / 10; i++) {
        printf("%04d: ", i * 10);
        for (int e = i * 10; e < ((i * 10) + 10); e++) {
            printf("%03d ", *(memory + e));
        }
        printf("\n");
    }

    printf("================ End of memory dump ====================\n\n");
}

void printRegisters() {
    std::cout << "\n========= Registers ==========\n";
    for (int i = 0; i < numOfRegisters; i++) {
        printf("R%d : %03d\n", i, *(registers + i));
    }
    printf("================== End of register dump ==================\n\n");
}

void getMemory() {
    do {
        std::cin >> *memoryPtr;
        memoryPtr++;
    } while (*(memoryPtr - 1) != 100);
}

// The following methods add n2 to n1 or multiply n1 by n2, storing the result back in n1 in each case, the only difference between add/multiply and
// add_R/multiply_R is that those with the '_R' work on references only while the others work on a reference and a copied variable
void add_R(WORD& n1, WORD& n2) {
    n1 = ((n1 + n2) >= wordLimit) ? n1 + n2 - wordLimit : n1 + n2;
}

void multiply_R(WORD& n1, WORD& n2) {
    n1 = ((n1 * n2) >= wordLimit) ? (n1 * n2) - wordLimit : n1 * n2;
}

void add(WORD& n1, WORD n2) {
    n1 = ((n1 + n2) >= wordLimit) ? (n1 + n2) - wordLimit : n1 + n2;
}

void multiply(WORD& n1, WORD n2) {
    n1 = ((n1 * n2) >= wordLimit) ? (n1 * n2) - wordLimit : n1 * n2;
}

int executeInstructonCase() {

    int instruction;
    int leftOperand;
    int rightOperand;

    int numOfInstr = 0;
    while (true) {
        // I split an instruction into three parts using the arithmetic below, it's weird, but it works.
        instruction = (*instrPtr) / 100;
        leftOperand = (int)(*instrPtr / 10) - ((*instrPtr / 100) * 10);
        rightOperand = (*instrPtr - (int)(*instrPtr / 10) * 10);
        switch (instruction) {
        case 1: // Halt
            numOfInstr++;
            if (instrPtr <= (memory + 998)) instrPtr++; //If there might be some instructions left, set the pointer to point to them
            return numOfInstr;
        case 2: // 2dn: set register d to n, where n is between 0 and 9 inclusive
            registers[leftOperand] = rightOperand;
            break;
        case 3: // 3dn: add n to register d
            //registers[leftOperand] += rightOperand;
            add(registers[leftOperand], rightOperand);
            break;
        case 4: // 4dn: multiply register d by n
            //registers[leftOperand] *= rightOperand;
            multiply(registers[leftOperand], rightOperand);
            break;
        case 5: // 5ds: set register d to the value of register s
            registers[leftOperand] = rightOperand;
            break;
        case 6: // 6ds: add the value of register s to register d
            //registers[leftOperand] += registers[rightOperand];
            add_R(registers[leftOperand], registers[rightOperand]);
            break;
        case 7: // 7ds: multiply register d by the value of register s
            //registers[leftOperand] *= registers[rightOperand];
            multiply_R(registers[leftOperand], registers[rightOperand]);
            break;
        case 8: // 8da: set register d to the value in RAM whose address is in register a
            registers[leftOperand] = memory[registers[rightOperand]];
            break;
        case 9: // 9sa: set the value in RAM whose address is in register a to that of register s
            memory[registers[leftOperand]] = registers[rightOperand];
            break;
        case 0: // 0ds: goto the location in register d unless register s contains 0
            if (registers[rightOperand] != 0) {
                instrPtr = memory + (registers[leftOperand] - 1);
            }
            break;
        default:
            break;
        }
        numOfInstr++;
        instrPtr++;
    }
}

int main() {

    init();
    std::cin >> numOfCases;
    std::cout << "\n";
    for (int i = 0; i < numOfCases; i++) {
        getMemory();
    }
    printMemory();
    int n = 0;
    while (numOfCases > 0) {
        n = executeInstructonCase();
        printf("%d\n\n", n);
        numOfCases--;
    }
    
    return 0;
}