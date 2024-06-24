#include <iostream>
#include <string>
#include <iomanip>
#include <queue>
#include <list>
#include <algorithm>
using namespace std;

struct Student
{
    string name;
    int id;
    int grade;
    char category; // New field for category
    double price;  // New field for price
};

class PriorityQueue
{
private:
    struct CompareStudents
    {
        bool operator()(const Student &a, const Student &b)
        {
            return a.grade < b.grade;
        }
    };

    priority_queue<Student, vector<Student>, CompareStudents> pq;
    const int maxSize = 5; // Maximum size for the priority queue

public:
    void enqueue(const Student &newStudent)
    {
        if (pq.size() < maxSize)
        {
            pq.push(newStudent);
            cout << "Student " << newStudent.name << " added to the priority queue successfully." << endl;
        }
        else
        {
            cout << "Priority queue is full. Cannot add more students." << endl;
        }
    }

    bool isEmpty()
    {
        return pq.empty();
    }

    Student front()
    {
        return pq.top();
    }

    void dequeue()
    {
        pq.pop();
    }

    void display()
    {
        priority_queue<Student, vector<Student>, CompareStudents> temp = pq;
        cout << "---------------------------------" << endl;
        cout << "| Priority Queue        |" << endl;
        cout << "---------------------------------" << endl;
        cout << "| Name          | ID    | Grade |" << endl;
        cout << "---------------------------------" << endl;
        while (!temp.empty())
        {
            Student student = temp.top();
            cout << "| " << setw(13) << left << student.name << "| " << setw(6) << left << student.id << " | " << setw(5) << left << student.grade << " | " << endl;
            temp.pop();
        }
        cout << "---------------------------------" << endl;
    }
};

list<Student> registeredStudents; // Using linked list instead of vector
int studentIDCounter = 0;         // Counter for assigning student IDs
vector<string> registeredNames;   // Vector to keep track of registered names

void Display_Registration()
{
    cout << "-----------------------------------------------------" << endl;
    cout << "|       Registered Students      |" << endl;
    cout << "-----------------------------------------------------" << endl;
    cout << "| Name          | ID    | Grade  | Category | Price |" << endl;
    cout << "-----------------------------------------------------" << endl;
    for (const auto &student : registeredStudents)
    {
        cout << "| " << setw(13) << left << student.name << "| " << setw(6) << left << student.id << " | " << setw(5) << left << student.grade << " | " << setw(8) << left << student.category << " | " << setw(6) << left << student.price << " |" << endl;
    }
    cout << "-----------------------------------------------------" << endl;
}

void Print_System_Definition()
{
    cout << "         *******************" << endl;
    cout << "*    Welcome to the Registration System!   *" << endl;
    cout << "         *******************" << endl;
}

void assignCategory(Student &student)
{
    if (student.grade >= 290)
    {
        student.category = 'A';
        student.price = 22750.0;
    }
    else if (student.grade >= 190)
    {
        student.category = 'B';
        student.price = 25755.0;
    }
    else
    {
        student.category = 'C';
        student.price = 30750.0;
    }
}

void updateStudentGrade(list<Student> &students, const string &name, int newGrade)
{
    auto it = find_if(students.begin(), students.end(), [&name](const Student &student)
                      { return student.name == name; });

    if (it != students.end())
    {
        it->grade = newGrade;
        assignCategory(*it); // Reassign category and price based on the new grade
        cout << "Grade of student " << name << " has been successfully updated." << endl;
    }
    else
    {
        cout << "Student " << name << " not found." << endl;
    }
}

void deleteStudent(list<Student> &students, const string &name)
{
    auto it = find_if(students.begin(), students.end(), [&name](const Student &student)
                      { return student.name == name; });

    if (it != students.end())
    {
        int deletedId = it->id;
        students.erase(it);

        // Reset IDs
        int newId = 1;
        for (auto &student : students)
        {
            student.id = newId++;
        }
        studentIDCounter--;

        cout << "Student " << name << " has been successfully deleted." << endl;
    }
    else
    {
        cout << "Student " << name << " not found." << endl;
    }
}

void searchStudent(list<Student> &students, const string &name)
{
    auto it = find_if(students.begin(), students.end(), [&name](const Student &student)
                      { return student.name == name; });

    if (it != students.end())
    {
        cout << "Student " << name << " found with ID " << it->id << ", grade " << it->grade << ", category " << it->category << ", and price $" << it->price << endl;
    }
    else
    {
        cout << "Student " << name << " not found." << endl;
    }
}

void Process_Registration(PriorityQueue &priorityQueue)
{
    if (!priorityQueue.isEmpty())
    {
        Student newStudent = priorityQueue.front();
        if (find(registeredNames.begin(), registeredNames.end(), newStudent.name) == registeredNames.end())
        {
            registeredNames.push_back(newStudent.name);
            newStudent.id = ++studentIDCounter; // Assigning a unique ID to the student
            assignCategory(newStudent);         // Assign category and price to the student
            registeredStudents.push_back(newStudent);
            cout << "Student " << newStudent.name << " with ID " << newStudent.id << ", category " << newStudent.category << ", and price $" << newStudent.price << " registered successfully." << endl;
        }
        else
        {
            cout << "Student " << newStudent.name << " has already been registered." << endl;
        }
        priorityQueue.dequeue();
    }
    else
    {
        cout << "Priority queue is empty." << endl;
    }
}

void RunMain()
{
    int choice;
    Print_System_Definition();
    PriorityQueue priorityQueue; // Creating priority queue with fixed size
    do
    {
        cout << "Choose an option:" << endl;
        cout << "1. Add Student" << endl;
        cout << "2. Process Registration" << endl;
        cout << "3. Display Registered Students" << endl;
        cout << "4. Display Priority Queue" << endl;
        cout << "5. Delete" << endl;
        cout << "6. Update" << endl;
        cout << "7. Search" << endl;
        cout << "8. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        system("cls");

        switch (choice)
        {
        case 1:
        {
            Student newStudent;
            cout << "Enter student name: ";
            cin.ignore();
            getline(cin, newStudent.name);
            cout << "Enter student grade: ";
            cin >> newStudent.grade;
            if (newStudent.grade >= 200)
            {
                priorityQueue.enqueue(newStudent);
            }
            else
            {
                cout << "Student " << newStudent.name << " cannot be registered with grade less than 200." << endl;
            }
            break;
        }
        case 2:
        {
            cout << "Processing registration..." << endl;
            Process_Registration(priorityQueue); // Process registration from priority queue
            break;
        }

        case 3:
        {
            Display_Registration();
            break;
        }

        case 4:
        {
            priorityQueue.display();
            break;
        }

        case 5:
        {
            string nameToDelete;
            cout << "Enter student name to delete: ";
            cin.ignore();
            getline(cin, nameToDelete);
            deleteStudent(registeredStudents, nameToDelete);
            break;
        }

        case 6:
        {
            string nameToUpdate;
            int newGrade;
            cout << "Enter student name to update grade: ";
            cin.ignore();
            getline(cin, nameToUpdate);
            cout << "Enter new grade: ";
            cin >> newGrade;
            updateStudentGrade(registeredStudents, nameToUpdate, newGrade);
            break;
        }

        case 7:
        {
            string nameToSearch;
            cout << "Enter student name to search: ";
            cin.ignore();
            getline(cin, nameToSearch);
            searchStudent(registeredStudents, nameToSearch);
            break;
        }

        case 8:
        {
            cout << "Exiting program..." << endl;
            break;
        }

        default:
        {
            cout << "Invalid choice. Please try again." << endl;
        }
        }
    } while (choice != 8);
}

int main()
{
    RunMain();
    return 0;
}
