# CS50x Final Project: cGPA Calculator and Planner

---
## Program Overview

This project is a command-line application written in C that calculates a student's cumulative Grade Point Average (cGPA) based on the total number of academic units attained, and the letter grade they receive for the corresponding courses. Additional features such as recalculating cGPA based on invoking the S/U option, required cGPA predictor for remaining courses to attain target cGPA, and recalculating cGPA based on the addition of retaken 'F' courses, are included to provide a more comprehensive scenario analysis.

While the project is kept as a single file to focus on algorithmic accuracy and clarity, the code is modularised via functions to fulfill single responsibility and modularity.

---
## Design Considerations

Each course is represented by a `struct` which stores:
1. Academic units (AU)
2. Grade
3. Grade point equivalent
4. A boolean flag indicating its inclusion in cGPA calculation
This allows the program to recalculate cGPA dynamically without requiring repeated user inputs for courses and AUs, particularly for options like invoking S/U or adding retaken courses, thereby aiding in convenience and data retrieval accessibility.

---
## Functionality

The functionalities of the program are presented to the user via an initial menu. Users can repeatedly select and execute as many functions as they desire, until they enter the choice to exit the program. This is done via a do-while loop to ensure repetition, and the switch function to toggle among user's choices.

### 1. Input courses and AUs

Upon selection, users enter the number of courses that they have taken, and their corresponding AUs. These information are then stored accordingly and can be accessed by the course index, attained as per the order of user input. Users would only need to enter the certain changes, if any, when other functions are selected. They would not have to re-enter all courses repeatedly, for the duration of the program.


### 2. Calculate cGPA

The cGPA is computed using the standard formula:
    `CGPA = Σ(Grade Point for each course × AU for each course) / Σ(AU)`

where only letter-grade courses are included in both the numerator and denominator. The courses that are graded as S (Satisfactory), U (Unsatisfactory), P (Pass), IP (In Progress), or EX (Exempted) do not contribute to the final standing cGPA, as per typical academic policies.


### 3. SU and recalculate cGPA

Users can invoke an S/U option on a previously letter-graded course. Grade S indicates a Satisfactory grade, while grade U indicates an Unsatisfactory one. The course/s would then subsequently be excluded from the computation of cGPA. As such, the grade points and AUs of these courses are removed from the numerator and denominator of cGPA calculations respectively, and they are marked as excluded (boolean=False for `included`).


### 4. Average cGPA required for remaining courses to attain target cGPA

Users can enter their target cGPA and the total number of AUs required for the completion of their degree programme. The program will then return the average cGPA required for their remaining courses, if any, in order to attain the desired target cGPA.

This is computed via:
    `(Target cGPA * Total AUs required - Current cGPA * Total AUs completed) / Remaining AUs`

where Remaining AUs = Total AUs required - Total AUs completed.

As such, the planner aspect of the program is fulfilled, and users are provided with tangible cGPA objectives for the remainder of their studies.


### 5. Add retaken 'F' courses and recalculate cGPA

The user can indicate their retaken 'F' course/s, in which both attempts, that is the 'F' grade attained from the first attempt, and the new grade attained from the subsequent attempt, will be reflected in the cGPA calculation. As such, the retaken course is treated as an additional course entry rather than replacing the old entry, and both the numerator and denominator of cGPA calculations increase.


### 6. Exit

Users can then exit the program. There is no data persistence, and users have to re-enter the required information if/when they run the program again.

---
## Future Improvements
- Additional Year Grade Point Average (yGPA) calculations to measure yearly performance
- Visualisation or further analytics of cGPA trends
- Complete automation via information extraction from uploaded transcript
- Data persistence after the program is exited
- A more accessible web application for better user experience
