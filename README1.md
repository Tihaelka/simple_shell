Creating a simple shell project in C programming involves several steps.
A shell is a command-line interface that allows users to interact with
an operating system.
In order to meet the main requirments of the project
Here's the outline of the steps i have followed to
create a simple shell in C:

2. **Designing Shell**:
   - Decide on the features and functionalities i want to include in
   shell according to the tasks requirments.
3. **Write the Main Loop**:
   - Create a main loop that continuously reads user input and processes
   commands until the user decides to exit the shell.

4. **Read User Input**:
   - Use functions like getline as demanded to read user input from the
   command line.

5. **Parse User Input**:
   - Parse the user input to separate the command and its arguments
   using "strtock"
6. **Execute Commands**:
   - Create a function or system call to execute the parsed command
   and its arguments.
7. **Handle Built-in Commands**:
   - Implement built-in commands like `cd`, `exit`

8. **Handle Pipes** (optional):
   - Implement support for pipes (`|`) to allow chaining multiple
   commands together.

9. **Error Handling**:
    - Implement error handling for various scenarios
10. **Signal Handling** (optional):
    - Implement signal handling to handle signals like Ctrl+C (SIGINT).

11. **Prompt and Display**:
    - Create a shell prompt to indicate that the shell is ready for input
    and display the results of executed commands.

12. **Clean Up Resources**:
    - Properly release any allocated resources and close files or processes
    when the shell exits.

13. **Testing**:
    - Test your shell with various commands and scenarios to ensure it
    works as expected.
