#include <bits/stdc++.h>
using namespace std;

class Expense
{
public:
    string category;
    float amount;
};

class FinancialAdvice
{
public:
    void provideAdvice(float income, float spent)
    {
        // Savings and Budgeting
        if ((income - spent) > (0.3 * income))
        {
            cout << "Excellent! You are saving a good portion of your income. Keep up the good work!" << endl;
        }
        else if ((income - spent) > (0.2 * income))
        {
            cout << "Good job! You are saving a reasonable amount of your income. Consider increasing your savings if possible." << endl;
        }
        else
        {
            cout << "Your current savings rate is low. Try to reduce your expenses and increase your savings to achieve financial stability." << endl;
        }

        // Debt Management
        if (spent > (0.5 * income))
        {
            cout << "Your expenses are high compared to your income. Consider reducing your debt or finding ways to increase your income." << endl;
        }
        else
        {
            cout << "Your expenses seem manageable compared to your income. Keep up the good work in managing your debt." << endl;
        }

        // Overall Advice
        if ((income - spent) > (0.3 * income) && spent < (0.5 * income))
        {
            cout << "Congratulations! You are in a strong financial position. Keep up the good work and continue to save and manage your expenses effectively." << endl;
        }
        else
        {
            cout << "Review your spending habits and consider ways to increase your savings and reduce your debt. Financial stability is important for your long-term well-being." << endl;
        }
        cout<<endl;
    }
};

int main()
{
    vector<Expense> expenses;
    FinancialAdvice advice;
    float income = 0.0;
    float spent = 0.0;
    int ch;

    cout << "Enter your total earnings: ";
    cin >> income;

    while (true)
    {
        cout << "Finance Management System" << endl;
        cout << "1. Add Expense" << endl;
        cout << "2. Display Expenses" << endl;
        cout << "3. Delete Expense" << endl;
        cout << "4. Get Financial Advice" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> ch;

        switch (ch)
        {
        case 1:
        {
            Expense e;
            cout << "Enter expense category: ";
            cin >> e.category;
            cout << "Enter expense amount: ";
            cin >> e.amount;
            expenses.push_back(e);
            spent += e.amount;
            cout << "Expenses added successfully!" << endl
                 << endl;
            break;
        }
        case 2:
        {
            cout << "Finance Management Details: "<<endl;
            for (Expense e : expenses)
            {
                cout << "Category: " << e.category << ", Amount: $" << e.amount << endl;
            }
            cout << "Total Expenses: $" << spent << endl;
            cout << "Current Balance: $" << (income - spent) << endl << endl;
            break;
        }
        case 3:
        {
            int i;
            cout << "Enter the index of the expense to delete: ";
            cin >> i;
            if (i >= 0 && i < expenses.size())
            {
                spent -= expenses[i].amount;
                expenses.erase(expenses.begin() + i);
                cout << "Expense deleted successfully!" << endl << endl;
            }
            else
            {
                cout << "Invalid index!" << endl << endl;
            }
            break;
        }
        case 4:
        {
            advice.provideAdvice(income, spent);
            break;
        }
        case 5:
        {
            cout << "Final Balance: $" << (income - spent) << endl;
            cout << "Exiting..." << endl;
            return 0;
        }
        default:
        {
            cout << "Enter a valid choice!" << endl << endl;
            break;
        }
        }
    }
    return 0;
}