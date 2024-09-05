
# Budget Tracker

A Personal Expense Tracker is a console-based application that allows users to track their expenses. Each user can add, view, update, and delete their records. The application is designed to be user-specific, meaning that each user can only view and manage their own records after logging in.

## Features
1. User Authentication: Users must register and log in to access their records.
2. Add Record: Users can add a new expense record with a category, description, and amount.
3. View Records: Users can view their records.
4. Update Record: Users can update an existing record.
5. Delete Record: Users can delete a record.
6. Best Budget Finder: Users can find the category with the lowest spending.

### Getting Started
#### Prerequisites :
* A C compiler (e.g., GCC)\
* Basic understanding of C programming language\

### Installation
1. Clone the repository:
```bash
git clone https://github.com/yourusername/expense-tracker.git
```

2. Navigate to the project directory:
```bash
cd BUDGET TRACKER
```

3. Compile the program:
```bash
gcc index.c -o index
```

4. Run the program:
```bash
./index
```

### Usage
- Start the application.
- Register a new user or log in with existing credentials.
- Use the menu options to add, view, update, or delete records.
- Find the category with the lowest spending using the "Find Best Budget" option.

### File Structure
- expense_tracker.c: The main program file containing all the functions and logic.
- records.dat: Stores user-specific records (generated automatically).
- users.dat: Stores user credentials (generated automatically).

### Test Cases
#### Test Case 1: User Registration and Login
Scenario: A new user registers and then logs in.

Steps:
1. Start the program.
2. Enter a new username and password for registration.
3. Confirm the password.
4. Log in with the newly created username and password.
5. Expected Result:
6. The user should be successfully registered and able to log in.

Expected Result:

The record should be added successfully and saved to records.dat.
#### Test Case 2: Add a New Record
Scenario: A user logs in and adds a new expense record.

Steps:
1. Log in with valid credentials.
2. Select the option to add a record.
3. Enter the category (e.g., "Food").
4. Enter the description (e.g., "Groceries").
5. Enter the amount (e.g., "150.75").

####
Expected Result:

The record should be added successfully and saved to records.dat.

#### Test Case 3: View Records
Scenario: A user views their added records.

Steps:
1. Log in with valid credentials.
2. Select the option to view records.
####
Expected Result:

The records specific to the logged-in user should be displayed correctly.

#### Test Case 4: Update an Existing Record
Scenario: A user updates an existing expense record.

Steps:

1. Log in with valid credentials.
2. Select the option to update a record.
3. Enter the description of the record to update (e.g., "Groceries").
4. Enter the new category, description, and amount.
####
Expected Result:

The record should be updated with the new values and saved.

#### Test Case 5: Delete a Record
Scenario: A user deletes an existing expense record.

Steps:

1. Log in with valid credentials.
2. Select the option to delete a record.
3. Enter the description of the record to delete (e.g., "Groceries").
####
Expected Result:

The record should be deleted from the user's records.

#### Test Case 6: Find the Best Budget
Scenario: A user finds the category with the lowest spending.

Steps:

1. Log in with valid credentials.
2. Select the option to find the best budget.
####
Expected Result:

The category with the lowest total spending should be displayed.

#### Test Case 7: User-Specific Data Isolation
Scenario: Multiple users add records and verify that they can only see their own records.

Steps:

1. User A logs in and adds a record.
2. User B logs in and adds a record.
3. Both users view their records separately.
####
Expected Result: User A should only see their records, and User B should only see theirs.
