# Assignment-Shell-Team-48
A command line app which helps you manage and maintain the file structure of your assignment files.

## Team Members
1. Vidit Jain (2020101134)
2. Sreejan Patel(2020101084)
3. Yeduru Rupasree(2020101097)
4. Ayan Agrawal(2020101034)
5. Anirudh Kaushik (2020111015)

## Instructions on How to Compile and run the Assignment Shell:
1. Download the zip folder and unzip the submission
2. Change into the Assignment-Shell-Team-48 directory
3. run `make` in terminal (The main directory specifically)
4. run `./AssignmentShell` in terminal to use the application.

## Instructions(2):
1. Run `git clone https://github.com/Vidit-Jain/Assignment-Shell-Team-48.git` in the terminal in an appropriate directory
2. Change into Assignment-Shell-Team-48 directory
3. run `make` in terminal (The main directory specifically)
4. run `./AssignmentShell` in terminal to use the application.

## Syntax of commands Implemented in Assignment Shell

1. `switch <subject_name>`

   example: `switch DSA`

   Switches to the specified subject if it exists

2. `create <assignment_name>`

   example: `create Assignment1`

   Creates an assignment if it exists on the server

3. `update <assignment_name>`

   example: `update Assignment1`

   Updates an assignment by removing the old files and adding the new ones

4. `setup <assignment_name>`

   example: `setup Assignment1`
   
   Sets up the assignment according to the given folder structure provided in the dist folder

5. `test <assignment_name>`

   example: `test Assignment1`

   Tests the given assignment by running `submitter.py`

6. `submit <assignment_name>`

   example: `submit Assignment1`
   
   Zips your submission and uploads it to the server

7. `compare <assignment_name> <assignment_name.zip>`

   example: `compare Assignment1 Assignment1.zip`

   Compares your assignment with the zipped submission to ensure the integrity is maintained

8. `use <assignment_name>`

   example `use Assignment1`

   Defaults the second argument of each function that take assignment name as a parameter to the string used with the used command for user convinience

## Running Testcases
We've provided two lists of test cases, that helps in displaying the error handling that has
been implemented by us. Due to the project being an interactive one, we felt that testcases
wouldn't be able to show the actual functioning of the project. It is possible to come up with the test cases intuitively. 
