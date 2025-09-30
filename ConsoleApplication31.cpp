//Group: Zhigang Su and Aditya Singh
//CMPS 385 FALL 2025



#include <iostream>
using namespace std;


int summation(int start, int end) {


    if (start > end) {
        return 0; 
    }
    else {
        return (4 * start + 5) + summation(start + 1, end);
    }
}

int main() {
    int start, end;

    cout << "Enter the start index: ";
    cin >> start;

    cout << "Enter the end index: ";
    cin >> end;

    cout << "Now calculating (4n+5) from " << start << " to " << end << endl;

    int result = summation(start, end);

    cout << "Final answer is: " << result << endl;

    return 0;
}
