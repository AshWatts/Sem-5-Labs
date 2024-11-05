#include <bits/stdc++.h>
using namespace std;

class Student {
public:
    string name;
    int rollNo;
    float marks;
};

int main() {
    vector<Student> students;
    int choice;
    
    while (true) {
        cout << "Student Management System" << endl;
        cout << "1. Add Student" << endl;
        cout << "2. Display Students" << endl;
        cout << "3. Delete Student" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1: {
                Student s;
                cout << "Enter name: ";
                cin >> s.name;
                cout << "Enter roll number: ";
                cin >> s.rollNo;
                cout << "Enter marks: ";
                cin >> s.marks;
                students.push_back(s);
                cout << "Student added successfully!" << endl << endl;
                break;
            }
            case 2: {
                cout << "Student Details:" << endl;
                for (Student s : students) {
                    cout << "Name: " << s.name << ", Roll No: " << s.rollNo << ", Marks: " << s.marks << endl;
                }
                cout<<endl;
                break;
            }
            case 3: {
                int rollNo;
                cout << "Enter roll number of the student to delete: ";
                cin >> rollNo;
                bool found = false;
                for (int i = 0; i < students.size(); i++) {
                    if (students[i].rollNo == rollNo) {
                        students.erase(students.begin() + i);
                        cout << "Student deleted successfully!" << endl << endl;
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    cout << "Student not found!" << endl << endl;
                }
                break;
            }
            case 4: {
                cout << "Exiting..." << endl << endl;
                return 0;
            }
            default: {
                cout << "Invalid choice!" << endl << endl;
                break;
            }
        }
    }
    
    return 0;
}