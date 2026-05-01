#include <iostream> 
#include <vector> 
using namespace std; 
 
class Person { 
protected: 
    int empId; 
    string name, department; 
 
public: 
    Person() : empId(0) {} 
 
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
 
    int getId() const { return empId; } 
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
    struct Salary { 
        double basic=0, hra=0, da=0, bonus=0; 
        double tax=0, pf=0, leaveDeduction=0; 
    } s; 
 
    double valid(double v) { return v < 0 ? 0 : v; } 
 
    void readSalary(const string& tag="") { 
        cout << "Enter " << tag << "Basic Salary  : "; cin >> s.basic; 
        cout << "Enter " << tag << "HRA           : "; cin >> s.hra; 
        cout << "Enter " << tag << "DA            : "; cin >> s.da; 
        cout << "Enter " << tag << "Bonus         : "; cin >> s.bonus; 
        cout << "Enter " << tag << "Tax Deduction : "; cin >> s.tax; 
        cout << "Enter " << tag << "PF Deduction  : "; cin >> s.pf; 
        cout << "Enter " << tag << "Leave Deduct  : "; cin >> s.leaveDeduction; 
 
        s.basic=valid(s.basic); s.hra=valid(s.hra); s.da=valid(s.da); 
        s.bonus=valid(s.bonus); s.tax=valid(s.tax); 
        s.pf=valid(s.pf); s.leaveDeduction=valid(s.leaveDeduction); 
    } 
 
public: 
    void input() { 
        inputBasicDetails(); 
        inputSalaryDetails(); 
    } 
 
    void inputSalaryDetails() { readSalary(); } 
    void updateSalaryDetails() { readSalary("New "); } 
 
    void update() { 
        cout << "\nUpdating Employee ID: " << empId << endl; 
        cout << "Enter New Name          : "; 
        getline(cin >> ws, name); 
        cout << "Enter New Department    : "; 
        getline(cin >> ws, department); 
        updateSalaryDetails(); 
    } 
 
    double calculateNetSalary() const { 
        return (s.basic+s.hra+s.da+s.bonus) - (s.tax+s.pf+s.leaveDeduction); 
    } 
 
    void display() const { 
        cout << "\n----------------------------------------\n"; 
        displayBasicDetails(); 
        cout << "Basic Salary  : " << s.basic << endl; 
        cout << "HRA           : " << s.hra << endl; 
        cout << "DA            : " << s.da << endl; 
        cout << "Bonus         : " << s.bonus << endl; 
        cout << "Tax Deduction : " << s.tax << endl; 
        cout << "PF Deduction  : " << s.pf << endl; 
        cout << "Leave Deduct  : " << s.leaveDeduction << endl; 
        cout << "\nNET SALARY    : " << calculateNetSalary() << endl; 
        cout << "----------------------------------------\n"; 
    } 
 
    void displayPayslip() const { 
        cout << "\n========== EMPLOYEE PAYSLIP ==========\n"; 
        display(); 
    } 
}; 
 
class PayrollSystem { 
    vector<Employee> emp; 
 
    int findEmployee(int id) const { 
        for (int i = 0; i < emp.size(); i++) 
            if (emp[i].getId() == id) return i; 
        return -1; 
    } 
 
public: 
    void addEmployee() { 
        Employee e; 
        e.input(); 
        emp.push_back(e); 
        cout << "Employee added!\n"; 
    } 
 
    void searchEmployee() const { 
        int id; cout << "Enter ID: "; cin >> id; 
        int i = findEmployee(id); 
        (i!=-1) ? emp[i].display() : cout << "Employee not found!\n"; 
    } 
 
    void generatePayslip() const { 
        int id; cout << "Enter ID for payslip: "; cin >> id; 
        int i = findEmployee(id); 
        if (i!=-1) { 
            const Payroll* p = &emp[i]; 
            p->displayPayslip(); 
        } else cout << "Employee not found!\n"; 
    } 
 
    void updateEmployee() { 
        int id; cout << "Enter ID to update: "; cin >> id; 
        int i = findEmployee(id); 
        (i!=-1) ? (emp[i].update(), cout<<"Employee updated!\n") 
                : cout<<"Employee not found!\n"; 
    } 
 
    void deleteEmployee() { 
        int id; cout << "Enter ID to delete: "; cin >> id; 
        int i = findEmployee(id); 
        if (i!=-1) { 
            emp.erase(emp.begin()+i); 
            cout << "Employee deleted!\n"; 
        } else cout << "Employee not found!\n"; 
    } 
 
    void menu() const { 
        cout << "\n===== EMPLOYEE PAYROLL SYSTEM =====\n"; 
        cout << "1. Add Employee\n2. Search Employee\n3. Generate Payslip\n"; 
        cout << "4. Update Employee\n5. Delete Employee\n6. Exit\n"; 
    } 
 
    void run() { 
        int ch; 
        do { 
            menu(); 
            cout << "Enter choice: "; 
            cin >> ch; 
            switch(ch){ 
                case 1: addEmployee(); break; 
                case 2: searchEmployee(); break; 
                case 3: generatePayslip(); break; 
                case 4: updateEmployee(); break; 
                case 5: deleteEmployee(); break; 
                case 6: cout<<"Exiting...\n"; break; 
                default: cout<<"Invalid choice!\n"; 
            } 
        } while(ch!=6); 
    } 
}; 
 
int main() { 
    PayrollSystem().run(); 
} 
