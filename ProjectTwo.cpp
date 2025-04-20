#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>  // For stringstream to split strings

using namespace std;

class Course {
public:
    string courseId;
    string courseTitle;
    vector<string> preRequisite;

    Course() = default;  // Default constructor
};

// Load data into vector from file
void loadVector(const string& textFile, vector<Course>& courses) {
    ifstream file(textFile);

    // When file is found
    if (file.is_open()) {
        Course tempCourse;
        string line;
        
        while (getline(file, line)) {  // Read the whole line
            stringstream ss(line);  // Use stringstream to parse the line
            
            // Extract courseId and courseTitle
            getline(ss, tempCourse.courseId, ',');  // Read courseId (separated by comma)
            getline(ss, tempCourse.courseTitle, ',');  // Read courseTitle (separated by comma)

            tempCourse.preRequisite.clear(); // Clear the prerequisites before adding new ones
            string preRequisite;
            
            // Read prerequisites (until "-1" is encountered)
            while (ss >> preRequisite && preRequisite != "-1") {
                tempCourse.preRequisite.push_back(preRequisite);
            }

            // Debugging: Check if the course was read correctly
            cout << "Loaded course: " << tempCourse.courseId << ", " << tempCourse.courseTitle << endl;

            // Add the course to the courses vector
            courses.push_back(tempCourse);
        }

        file.close();
        cout << "Courses have been imported." << endl;
    } else {
        cout << "File not found." << endl;
    }
}

// Print course list, filtering by courseId
void printCourseList(const vector<Course>& courses) {
    if (courses.empty()) {
        cout << "No courses available." << endl;
        return;
    }

    for (const Course& course : courses) {
        cout << "Course ID: " << course.courseId << ", Title: " << course.courseTitle << endl;

        // Print prerequisites if available
        if (!course.preRequisite.empty()) {
            cout << "Prerequisites: ";
            for (const string& preReq : course.preRequisite) {
                cout << preReq << " ";
            }
            cout << endl;
        } else {
            cout << "Prerequisites: None listed" << endl;
        }
    }
}

// Print detailed course information by courseId
void printCourseInformation(const vector<Course>& courses, const string& courseId) {
    bool found = false;
    for (const Course& course : courses) {
        // Ensure exact comparison between courseId and the input courseId
        if (course.courseId == courseId) {
            found = true;
            cout << course.courseId << ": " << course.courseTitle << endl;

            // Print prerequisites if available
            if (!course.preRequisite.empty()) {
                for (const string& preReq : course.preRequisite) {
                    cout << "Prerequisite: " << preReq << endl;
                }
            } else {
                cout << "None listed." << endl;
            }
            break;
        }
    }
    if (!found) {
        cout << "Course not found." << endl;
    }
}


int main() {
    vector<Course> courses;
    string textFile;
    string courseId;
    int choice;

    // User menu options
    do {
        cout << "1. Load Data Structure." << endl;
        cout << "2. Print Course List." << endl;
        cout << "3. Print Course." << endl;
        cout << "9. Exit" << endl;
        cout << "What would you like to do? ";
        cin >> choice;
        cin.ignore(); // Ignore any extra newline characters that may remain in the input buffer.

        switch (choice) {
        case 1: {
            // Prompt for text file name and load the courses
            cout << "Enter the file name to load data: ";
            getline(cin, textFile);  // Read the entire file name (including spaces if any)
            loadVector(textFile, courses);
            break;
        }
        case 2:
            // Print the course list
            printCourseList(courses);
            break;
        case 3: {
            // Print information about a specific course
            cout << "Enter course ID to search: ";
            getline(cin, courseId);  // Read the whole course ID
            printCourseInformation(courses, courseId);
            break;
        }
        case 9:
            cout << "Thank you for using the course planner!" << endl;
            break;
        default:
            cout << "Invalid option selected." << endl;
            break;
        }
    } while (choice != 9);

    return 0;
}
