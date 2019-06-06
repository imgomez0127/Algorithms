/*
 * student.cpp
 * "I pledge my honor that I have abided by the Stevens honor system" -igomez1
 *  Created on: September, 07 2018
 *      Author: igomez1
 * 		Ian Gomez
 */
#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

class Student{
 /**
 	A student class which contains the first and last name of a student, as well as the gpa and student id
 	It also contains fucntions which return these values and a function to print out the provided information
 */
private:
	/**
		string first_ the first name of the student
		string last_ the last name of the student
		float gpa_ the gpa of the student
		int id_ the id number of the student
	*/
	string first_,last_;
	float gpa_;
	int id_;
public:
	Student(string first, string last, float gpa, int id): first_{first},last_{last},gpa_{gpa},id_{id}{  }
	string full_name() const{
		/**
			A function which returns the full name of the student
		*/
		return first_ + " " + last_;
	} 
	int id() const{
		/**
			A function which returns the student id of the student
		*/
		return id_;
	}
	float gpa() const{
		/**
			A function which returns the GPA of the student 
		*/
		return gpa_;
	}
	void print_info() const{
		/**
			A function which returns all the provided information of the student
		*/
		cout << full_name() << ", GPA: "  << fixed << setprecision(2) << gpa_ << ", ID: " << id_ << endl; 
	}
};
vector<Student> failing_students(const vector<Student> &students){
	/**
		This function takes in a vector of students and returns a vector of students
		which contains all the students that have lower than 1 gpa
	*/
	vector<Student> failing_students;
	for(auto it=students.cbegin(); it != students.cend(); ++it){
		if(it->gpa() <1.0){
			failing_students.push_back(*it);
		}
	
	}
	return failing_students;
}
void print_students(const vector<Student> &students){
	/**
		This function takes in a vector of students and prints out all the information of each student
		on a new line
	*/
	for(auto it = students.cbegin(); it != students.cend(); it++){
		it->print_info();
	}
}
int main(){
	string first_name,last_name;
	float gpa;
	int id;
	char repeat;
	vector<Student> students;
	 do {
        cout << "Enter student's first name: ";
        cin >> first_name;
        cout << "Enter student's last name: ";
        cin >> last_name;
        gpa = -1;
        while (gpa < 0 || gpa > 4) {
            cout << "Enter student's GPA (0.0-4.0): ";
            cin >> gpa;
        }
        cout << "Enter student's ID: ";
        cin >> id;
        students.push_back(Student(first_name, last_name, gpa, id));
        cout << "Add another student to database (Y/N)? ";
        cin >> repeat;
    } while (repeat == 'Y' || repeat == 'y');
    cout << endl << "All students:" << endl;
    print_students(students);
    vector<Student> failing_stus = failing_students(students);
    cout << endl << "Failing students:";
    if(failing_stus.size() == 0){
    	cout << " None";
    }
    else{
    	cout << endl;
    	print_students(failing_stus);
    }
	return 0;
}