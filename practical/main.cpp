#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>

// ======================================================
// 1) Basic pointer on int
// ======================================================

void demonstrateBasicIntPointer() {
    std::cout << "=== demonstrateBasicIntPointer ===\n";

    int userNumber{10};
    int *pointerToUserNumber{&userNumber};

    std::cout << "Initial value: " << userNumber << '\n';
    std::cout << "Value via pointer: " << *pointerToUserNumber << '\n';

    *pointerToUserNumber = 25; // dereferencing and assigning
    std::cout << "New value after dereferencing: " << userNumber << "\n\n";
}

// ======================================================
// 2) Various pointer types
// ======================================================

void functionToBeCalledThroughPointer() {
    std::cout << "Function called through function pointer.\n";
}

void demonstrateVariousPointerTypes() {
    std::cout << "=== demonstrateVariousPointerTypes ===\n";

    // Pointer to int
    int integerValue{42};
    int *pointerToIntegerValue{&integerValue};
    std::cout << "Pointer to int: " << *pointerToIntegerValue << '\n';

    // Pointer to char
    char characterValue{'A'};
    char *pointerToCharacterValue{&characterValue};
    std::cout << "Pointer to char: " << *pointerToCharacterValue << '\n';

    // Pointer to array
    int integerArray[3]{1, 2, 3};
    int *pointerToIntegerArray{integerArray};
    std::cout << "Pointer to array: ";
    for (int index = 0; index < 3; ++index) {
        std::cout << *(pointerToIntegerArray + index) << ' ';
    }
    std::cout << '\n';

    // Array of pointers
    const char *arrayOfWords[3]{"Hello", "World", "Pointers"};
    std::cout << "Array of pointers:\n";
    for (int index = 0; index < 3; ++index) {
        std::cout << "  " << arrayOfWords[index] << '\n';
    }

    // Pointer to pointer
    int *pointerToFirstElement{&integerArray[0]};
    int **pointerToPointer{&pointerToFirstElement};
    std::cout << "Pointer to pointer: " << **pointerToPointer << '\n';

    // Pointer to function
    void (*pointerToFunction)() = functionToBeCalledThroughPointer;
    pointerToFunction();

    std::cout << '\n';
}

// ======================================================
// 3) Const pointer cases
// ======================================================

void demonstrateConstPointerCases() {
    std::cout << "=== demonstrateConstPointerCases ===\n";

    int firstNumber{10};
    int secondNumber{20};

    // const int *p : data const, pointer not const
    const int *pointerToConstantData{&firstNumber};
    std::cout << "pointerToConstantData: " << *pointerToConstantData << '\n';
    pointerToConstantData = &secondNumber;

    // int *const p : pointer const, data not const
    int *const constantPointerToData{&firstNumber};
    *constantPointerToData = 40;

    // const int *const p : both const
    const int *const constantPointerToConstantData{&firstNumber};
    std::cout << "constantPointerToConstantData: " << *constantPointerToConstantData << "\n\n";
}

// ======================================================
// 4) Structure Student + malloc/free
// ======================================================

struct Student {
    int registrationNumber;
    char name[50];
    int age;
};

void demonstrateStudentAllocationWithMallocFree() {
    std::cout << "=== demonstrateStudentAllocationWithMallocFree ===\n";

    Student *pointerToStudent = static_cast<Student*>(std::malloc(sizeof(Student)));
    if (pointerToStudent == nullptr) {
        std::cout << "Allocation failed.\n\n";
        return;
    }

    pointerToStudent->registrationNumber = 12345;
    std::strcpy(pointerToStudent->name, "Alice");
    pointerToStudent->age = 20;

    std::cout << "Student (malloc/free): "
              << pointerToStudent->registrationNumber << ", "
              << pointerToStudent->name << ", "
              << pointerToStudent->age << '\n';

    std::free(pointerToStudent);
    std::cout << '\n';
}

// ======================================================
// 5) Structure Student + new/delete
// ======================================================

void demonstrateStudentAllocationWithNewDelete() {
    std::cout << "=== demonstrateStudentAllocationWithNewDelete ===\n";

    Student *pointerToStudent = new Student;

    pointerToStudent->registrationNumber = 54321;
    std::strcpy(pointerToStudent->name, "Bob");
    pointerToStudent->age = 22;

    std::cout << "Student (new/delete): "
              << pointerToStudent->registrationNumber << ", "
              << pointerToStudent->name << ", "
              << pointerToStudent->age << '\n';

    delete pointerToStudent;
    std::cout << '\n';
}

// ======================================================
// 6) Pointer arithmetic
// ======================================================

void demonstratePointerArithmetic() {
    std::cout << "=== demonstratePointerArithmetic ===\n";

    int integerArray[5]{10, 20, 30, 40, 50};
    int *pointerToStart{integerArray};
    int *pointerToEnd{&integerArray[4]};

    std::cout << "pointerToStart: " << *pointerToStart << '\n';
    std::cout << "pointerToStart + 2: " << *(pointerToStart + 2) << '\n';

    std::cout << "pointerToEnd: " << *pointerToEnd << '\n';
    std::cout << "pointerToEnd - 2: " << *(pointerToEnd - 2) << '\n';

    int distance = pointerToEnd - pointerToStart;
    std::cout << "Distance: " << distance << " elements\n\n";
}

// ======================================================
// 7) Pointer dangers (UB examples, commented)
// ======================================================

void demonstratePointerDangers() {
    std::cout << "=== demonstratePointerDangers ===\n";
    std::cout << "Examples shown as commented code to avoid UB.\n\n";

    std::cout << "1) Uninitialized pointer dereference\n";
    std::cout << "   int *p; // *p = 10; // UB\n\n";

    std::cout << "2) Null pointer dereference\n";
    std::cout << "   int *p = nullptr; // *p = 10; // UB\n\n";

    std::cout << "3) Use-after-free\n";
    std::cout << "   int *p = malloc(...); free(p); // *p = 10; // UB\n\n";

    std::cout << "4) Double free\n";
    std::cout << "   free(p); free(p); // UB\n\n";

    std::cout << "5) Buffer overflow\n";
    std::cout << "   int arr[3]; arr[3] = 10; // UB\n\n";

    std::cout << "6) Invalid pointer arithmetic\n";
    std::cout << "   *(p + 10); // UB\n\n";

    std::cout << "7) Strict aliasing violation\n";
    std::cout << "   double d; int *p = (int*)&d; // UB\n\n";
}

// ======================================================
// main
// ======================================================

int main() {
    demonstrateBasicIntPointer();
    demonstrateVariousPointerTypes();
    demonstrateConstPointerCases();
    demonstrateStudentAllocationWithMallocFree();
    demonstrateStudentAllocationWithNewDelete();
    demonstratePointerArithmetic();
    demonstratePointerDangers();

    return 0;
}
