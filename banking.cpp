#include <iostream>
#include <iomanip> // For setting bank balance to 2 decimal places
#include <vector>
#include <chrono> // For current time (Leaving the program)
#include <ctime> // For current time (Vector records)
#include <string> // For converting doubles to string

// Context for the 2 different time variables: 
// Copied std::chrono for the ending system, and copied ctime from another source for the vector (as I coudln't figure out how to use chrono for the vector)
// Important: This program can only track actions done during the session, and thus is not stored in a database. Value changes are also not tracked in real time.

// Function declaration
double deposit(double balance, double deposit);
double withdraw(double balance, double withdraw);
double showBalance(double balance);

int main()
{
    double balance = 2000.50; // Bank account balance
    double withdrawAmount; // Amount withdrawn
    double depositAmount; // Amount deposited
    int method; // Method that the user picks
    std::vector<std::string> transactions; // Vector to store transaction records

    auto startTime = std::chrono::system_clock::now(); // Measures the session starting time (Specifically for the end, different code for the vector)
    time_t now = time(0); // current date and time on the current system (For the vector)
    std::string date_time = ctime(&now); // convert now to string form (For the vector)

    do
    {
        // Asking the user on their choice of transaction
        std::cout << "Welcome to CPP Bank! \n\n";
        std::cout << "What would you like to do today? \n";
        std::cout << "1. Check Balance  2. Withdraw Cash  3. Deposit Cash  4. Check Transaction History  5. Quit \n";
        std::cin >> method;

        // Switch checking the methods against the user's choice
        switch (method)
        {
        case 1:
            std::cout << "Your balance is currently $" << std::setprecision(2) << std::fixed << showBalance(balance) << ". \n"; // Outputting the user's balance
            transactions.push_back("User checked balance on " + date_time); // Marking the action in the history
            break;
        case 2:
            std::cout << "How much would you like to withdraw? \n"; // Asking the user about the amount to withdraw
            std::cin >> withdrawAmount;

            if (withdrawAmount > balance)  // Withdrawing more than available
            {
                std::cout << "You can't withdraw more than what you have! Deposit more money to withdraw that much. \n";
                break;
            } 
            else if (withdrawAmount <= 0)  // Withdrawing 0 or negative amounts
            {
                std::cout << "You can't withdraw 0 or negative amounts! Try depositing money if you need to put money in your account. \n";
                break;
            }
            else  // Typical withdrawal
            {
                std::cout << "You have successfully withdrawn $" << withdrawAmount << ". \n"; // Affirming the user that the amount is withdrawn
                std::cout << "Your balance is now $" << std::setprecision(2) << std::fixed << withdraw(balance, withdrawAmount) << ". \n"; // Amount left in the account
                balance = withdraw(balance, withdrawAmount); // Changing the account balance
                transactions.push_back("User withdrew $" + std::to_string(withdrawAmount) + " on " + date_time); // Marking the action in the history
                break;
            }
        case 3:
            std::cout << "How much would you like to deposit? \n"; // Asking the use about the amount to deposit
            std::cin >> depositAmount;

            if (depositAmount <= 0) // Depositing 0 or negative amounts
            {
                std::cout << "You can't deposit 0 or negative amounts! Try withdrawing money if you need money from your account. ";
                break;
            } 
            else // Typical deposit
            {
                std::cout << "You have successfully deposited $" << depositAmount << ". \n"; // Affirming the user that the amount is deposited
                std::cout << "Your balance is now $" << std::setprecision(2) << std::fixed << deposit(balance, depositAmount) << ". \n"; // Amount left in the account
                balance = deposit(balance, depositAmount); // Changing the account balance
                transactions.push_back("User deposited $" + std::to_string(depositAmount) + " on " + date_time); // Marking the action in the history
                break;
            }
        case 4:
            if (transactions.size() == 0) {
                std::cout << "Your transaction history is empty! \n"; // If the transaction amount vector is empty, it outputs this
                break;
            } else {
                std::cout << "Here is your transaction history. \n\n"; // Outputting the transaction history with a for loop
                for (int i = 0; i < transactions.size(); i++) {
                    std::cout << transactions[i];
                }
                break;
            }
        case 5:
            auto end = std::chrono::system_clock::now(); // Marks the end time with std::chrono

            std::chrono::duration<double> elapsed_seconds = end - startTime; // Elapsed session time with std::chrono
            std::time_t end_time = std::chrono::system_clock::to_time_t(end); // Ends the timer (I think)

            std::cout << "Thank you for banking with CPP Bank! We hope to see you soon! \n";
            std::cout << "Ending Time: " << std::ctime(&end_time); // Session termination time
            std::cout << "Elapsed Time: " << elapsed_seconds.count() << "s. \n"; // Elapsed time in seconds
            return 0;
            // No default statement as the code breaks (for some reason)
        }

    } while (true);
}

// User defined functions that return the amount based on the action done
double deposit(double balance, double deposit)
{
    return balance += deposit;
}

double withdraw(double balance, double withdraw)
{
    return balance -= withdraw;
}

double showBalance(double balance)
{
    return balance;
}
