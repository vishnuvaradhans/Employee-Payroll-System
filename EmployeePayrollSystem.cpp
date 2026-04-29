#include <iostream>
#include <string>

using namespace std;

class Person {
protected:
    int empId;
    string name;
    string department;

public:
    Person() : empId(0), name(""), department("") {}

    virtual void inputBasicDetails() {
        cout << "\nEnter Employee ID   : ";
        cin >> empId;

        cout << "Enter Name          : ";
        getline(cin >> ws, name);

        cout << "Enter Department    : ";
        getline(cin >> ws, department);
    }

    virtual void displayBasicDetails() const {
        cout << "Employee ID   : " << empId << endl;
        cout << "Name          : " << name << endl;
        cout << "Department    : " << department << endl;
    }

    int getId() const {
        return empId;
    }

    virtual ~Person() {}
};

class Payroll {
public:
    virtual void inputSalaryDetails() = 0;
    virtual void updateSalaryDetails() = 0;
    virtual double calculateNetSalary() const = 0;
    virtual void displayPayslip() const = 0;
    virtual ~Payroll() {}
};

class Employee : public Person, public Payroll {
private:
    double basicSalary;
    double hra;
    double da;
    double bonus;
    double tax;
    double pf;
    double leaveDeduction;

    double validAmount(double value) const {
        if (value < 0) {
            return 0;
        }
        return value;
    }

public:
    Employee() : basicSalary(0), hra(0), da(0), bonus(0), tax(0), pf(0), leaveDeduction(0) {}

    void input() {
        inputBasicDetails();
        inputSalaryDetails();
    }

    void inputSalaryDetails() {
        cout << "Enter Basic Salary  : ";
        cin >> basicSalary;
        basicSalary = validAmount(basicSalary);

        cout << "Enter HRA           : ";
        cin >> hra;
        hra = validAmount(hra);

        cout << "Enter DA            : ";
        cin >> da;
        da = validAmount(da);

        cout << "Enter Bonus         : ";
        cin >> bonus;
        bonus = validAmount(bonus);

        cout << "Enter Tax Deduction : ";
        cin >> tax;
        tax = validAmount(tax);

        cout << "Enter PF Deduction  : ";
        cin >> pf;
        pf = validAmount(pf);

        cout << "Enter Leave Deduct  : ";
        cin >> leaveDeduction;
        leaveDeduction = validAmount(leaveDeduction);
    }

    void update() {
        cout << "\nUpdating Employee ID: " << empId << endl;

        cout << "Enter New Name          : ";
        getline(cin >> ws, name);

        cout << "Enter New Department    : ";
        getline(cin >> ws, department);

        updateSalaryDetails();
    }

    void updateSalaryDetails() {
        cout << "Enter New Basic Salary  : ";
        cin >> basicSalary;
        basicSalary = validAmount(basicSalary);

        cout << "Enter New HRA           : ";
        cin >> hra;
        hra = validAmount(hra);

        cout << "Enter New DA            : ";
        cin >> da;
        da = validAmount(da);

        cout << "Enter New Bonus         : ";
        cin >> bonus;
        bonus = validAmount(bonus);

        cout << "Enter New Tax Deduction : ";
        cin >> tax;
        tax = validAmount(tax);

        cout << "Enter New PF Deduction  : ";
        cin >> pf;
        pf = validAmount(pf);

        cout << "Enter New Leave Deduct  : ";
        cin >> leaveDeduction;
        leaveDeduction = validAmount(leaveDeduction);
    }

    double calculateNetSalary() const {
        double earnings = basicSalary + hra + da + bonus;
        double deductions = tax + pf + leaveDeduction;
        return earnings - deductions;
    }

    void display() const {
        cout << "\n----------------------------------------\n";
        displayBasicDetails();
        cout << "Basic Salary  : " << basicSalary << endl;
        cout << "HRA           : " << hra << endl;
        cout << "DA            : " << da << endl;
        cout << "Bonus         : " << bonus << endl;
        cout << "Tax Deduction : " << tax << endl;
        cout << "PF Deduction  : " << pf << endl;
        cout << "Leave Deduct  : " << leaveDeduction << endl;
        cout << "\nNET SALARY    : " << calculateNetSalary() << endl;
        cout << "----------------------------------------\n";
    }

    void displayPayslip() const {
        cout << "\n========== EMPLOYEE PAYSLIP ==========\n";
        display();
    }
};

class PayrollSystem {
private:
    Employee employees[100];
    int countEmp;

    int findEmployee(int id) const {
        for (int i = 0; i < countEmp; i++) {
            if (employees[i].getId() == id) {
                return i;
            }
        }
        return -1;
    }

public:
    PayrollSystem() : countEmp(0) {}

    void addEmployee() {
        if (countEmp >= 100) {
            cout << "Storage full!\n";
            return;
        }

        employees[countEmp].input();
        countEmp++;
        cout << "Employee added!\n";
    }

    void searchEmployee() const {
        int id;
        cout << "Enter ID: ";
        cin >> id;

        int index = findEmployee(id);
        if (index != -1) {
            employees[index].display();
        } else {
            cout << "Employee not found!\n";
        }
    }

    void generatePayslip() const {
        int id;
        cout << "Enter ID for payslip: ";
        cin >> id;

        int index = findEmployee(id);
        if (index != -1) {
            const Payroll* payrollRef = &employees[index];
            payrollRef->displayPayslip();
        } else {
            cout << "Employee not found!\n";
        }
    }

    void updateEmployee() {
        int id;
        cout << "Enter ID to update: ";
        cin >> id;

        int index = findEmployee(id);
        if (index != -1) {
            employees[index].update();
            cout << "Employee updated!\n";
        } else {
            cout << "Employee not found!\n";
        }
    }

    void deleteEmployee() {
        int id;
        cout << "Enter ID to delete: ";
        cin >> id;

        int index = findEmployee(id);
        if (index != -1) {
            for (int i = index; i < countEmp - 1; i++) {
                employees[i] = employees[i + 1];
            }
            countEmp--;
            cout << "Employee deleted!\n";
        } else {
            cout << "Employee not found!\n";
        }
    }

    void menu() const {
        cout << "\n===== EMPLOYEE PAYROLL SYSTEM =====\n";
        cout << "1. Add Employee\n";
        cout << "2. Search Employee\n";
        cout << "3. Generate Payslip\n";
        cout << "4. Update Employee\n";
        cout << "5. Delete Employee\n";
        cout << "6. Exit\n";
    }

    void run() {
        int choice;

        do {
            menu();
            cout << "Enter choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    addEmployee();
                    break;
                case 2:
                    searchEmployee();
                    break;
                case 3:
                    generatePayslip();
                    break;
                case 4:
                    updateEmployee();
                    break;
                case 5:
                    deleteEmployee();
                    break;
                case 6:
                    cout << "Exiting...\n";
                    break;
                default:
                    cout << "Invalid choice!\n";
            }
        } while (choice != 6);
    }
};

int main() {
    PayrollSystem payrollSystem;
    payrollSystem.run();
    return 0;
}
