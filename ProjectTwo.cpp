//Jodie Snodgrass
//20 June 2025
//CS 300 project two
//****Project works to load csv file. With file information code can sort a course list and print individual courses. 
//Menu is displayed to have user pick 1, 2, 3, or 9 depending on what they wish to do with csv file information.*** 



#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

//course structure
struct Course {
    string courseId;
    string courseName;
    vector<string> prerequisite;
};

//function to parse CSV line into a Course object
Course parseCourse(string line) {
    Course course;
    stringstream ss(line);
    string item;
    int count = 0;

    //split the line by commas
    while (getline(ss, item, ',')) {
        if (count == 0) {
            course.courseId = item;
        }
        else if (count == 1) {
            course.courseName = item;
        }
        //else push back prerequisites
        else {
            course.prerequisite.push_back(item);
        }
        count++;
    }

    return course;
}

//load courses from file
void loadCourses(string filename, vector<Course>& courses) {
    ifstream file(filename);
    string line;
    //if file cannot be found
    if (!file.is_open()) {
        //print error
        cout << "Error: Cannot open file." << endl;
        return;
    }
    //if found load courses
    while (getline(file, line)) {
        if (!line.empty()) {
            Course course = parseCourse(line);
            courses.push_back(course);
        }
    }
    //close file
    file.close();
    cout << "Courses successfully loaded!" << endl;
}

//print sorted course list
void printCourseList(const vector<Course>& courses) {
    vector<Course> sortedCourses = courses;
    //sorts by courseId
    sort(sortedCourses.begin(), sortedCourses.end(),
        [](const Course& a, const Course& b) {
            return a.courseId < b.courseId;
        });
    //how to display sorted course information
    for (const Course& course : sortedCourses) {
        cout << course.courseId << ", " << course.courseName << endl;
    }
}

//print course details for a specific course
void printCourseDetails(const vector<Course>& courses, string courseId) {
    bool found = false;
    for (const Course& course : courses) {
        if (course.courseId == courseId) {
            cout << course.courseId << ", " << course.courseName << endl;
            //check if there are prerequisites
            if (!course.prerequisite.empty()) {
                //print prerequisites
                cout << "Prerequisites: ";
                for (size_t i = 0; i < course.prerequisite.size(); ++i) {
                    cout << course.prerequisite[i];
                    if (i < course.prerequisite.size() - 1) cout << ", ";
                }
                cout << endl;
            }
            else {
                //print if no prerequisites 
                cout << "No prerequisites required." << endl;
            }
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Course not found." << endl;
    }
}

//main menu
void displayMenu() {
    //printed menu options
    cout << "------ Course Planner Menu ------" << endl;
    cout << "1. Load Courses" << endl;
    cout << "2. Print Course List" << endl;
    cout << "3. Print Course Information" << endl;
    cout << "9. Exit" << endl;
    cout << "Enter your choice: " << endl;
}
//main method
int main() {
    vector<Course> courses;
    string filename;
    int choice;

    do {
        //open menu
        displayMenu();
        cin >> choice;
        //to handle newline after ID input
        cin.ignore();  

        switch (choice) {
        case 1:
            //asks for csv file name 
            cout << "Enter CSV file name: ";
            //user inputs file name 
            getline(cin, filename);
            //file information loads
            loadCourses(filename, courses);
            break;
        case 2:
            //incase no file has been loaded there would be no data to print
            if (courses.empty()) {
                cout << "No courses loaded. Please load data first." << endl;
            }
            //else prints course list in alphanumeric order
            else {
                printCourseList(courses);
            }
            break;
        case 3:
            //incase no file has been loaded there would be no data to print
            if (courses.empty()) {
                cout << "No courses loaded. Please load data first." << endl;
            }
            else {
                string courseId;
                //asks for course Id
                cout << "Enter course ID (e.g., CS101): ";
                //finds input data
                getline(cin, courseId);
                //prints found data
                printCourseDetails(courses, courseId);
            }
            break;
        case 9:
            cout << "Goodbye!" << endl;
            break;
        default:
            //incase none of the menu options were chosen 
            cout << "Invalid choice. Please try again." << endl;
        }

    } while (choice != 9);

    return 0;
}
