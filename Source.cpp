#include<iostream>
using namespace std;

struct Node
{
	int coefficient;
	int exponent;
	Node* next;
};

class List {
private:
	Node* head = nullptr;
	Node* tail = nullptr;
public:
    bool isEmpty(); 
	void insert(int coeffValue, int expValue);
	void display();
	int evaluate(int x);
	int power(int base, int exp);
	List operator+(const List& polynomial);
	List operator-(const List& polynomial);
	List operator*(const List& polynomial);
};

bool List::isEmpty() {
    return head == nullptr;
}
void List::insert(int coeffValue, int expValue) {
    Node* newNode = new Node;
    newNode->coefficient = coeffValue;
    newNode->exponent = expValue;
    if (!head || head->exponent < expValue) {
        newNode->next = head;
        head = newNode;
    }
    else {
        Node* current = head;
        Node* prev = nullptr;
        while (current && current->exponent > expValue) {
            prev = current;
            current = current->next;
        }
        if (current && current->exponent == expValue) {
            current->coefficient += coeffValue;
            delete newNode;
            if (current->coefficient == 0) {
                if (prev) {
                    prev->next = current->next;
                }
                else {
                    head = current->next;
                }
                delete current;
            }
        }
        else {
            newNode->next = current;
            if (prev) {
                prev->next = newNode;
            }
            else {
                head = newNode;
            }
        }
    }
}

void List::display() {
    if (!head) {
        cout << "0" << endl;
        return;
    }
    Node* current = head;
    while (current) {
        if (current->coefficient > 0 && current != head) {
            cout << " + ";
        }
        if (current->exponent == 0) {
            cout << current->coefficient;
        }
        else {
            cout << current->coefficient << "x^" << current->exponent;
        }
        current = current->next;
    }
    cout << endl;
}

int List::power(int base, int exp)  {
    if (exp == 0) return 1;
    return base * power(base, exp - 1);
}

int List::evaluate(int x)  {
    int result = 0;
    for (Node* current = head; current != nullptr; current = current->next) {
        result += current->coefficient * power(x, current->exponent);
    }
    return result;
}

List List::operator+(const List& polynomial)  {
    List result;
    Node* p1 = head;
    Node* p2 = polynomial.head;

    while (p1 || p2) {
        if (p1 && (!p2 || p1->exponent > p2->exponent)) {
            result.insert(p1->coefficient, p1->exponent);
            p1 = p1->next;
        }
        else if (p2 && (!p1 || p2->exponent > p1->exponent)) {
            result.insert(p2->coefficient, p2->exponent);
            p2 = p2->next;
        }
        else {
            result.insert(p1->coefficient + p2->coefficient, p1->exponent);
            p1 = p1->next;
            p2 = p2->next;
        }
    }
    return result;
}

List List::operator-(const List& polynomial)  {
    List result;
    Node* p1 = head;
    Node* p2 = polynomial.head;

    while (p1 || p2) {
        if (p1 && (!p2 || p1->exponent > p2->exponent)) {
            result.insert(p1->coefficient, p1->exponent);
            p1 = p1->next;
        }
        else if (p2 && (!p1 || p2->exponent > p1->exponent)) {
            result.insert(-p2->coefficient, p2->exponent);
            p2 = p2->next;
        }
        else {
            result.insert(p1->coefficient - p2->coefficient, p1->exponent);
            p1 = p1->next;
            p2 = p2->next;
        }
    }
    return result;
}

List List::operator*(const List& polynomial) {
    List result;
    for (Node* p1 = head; p1 != nullptr; p1 = p1->next) {
        List temp;
        for (Node* p2 = polynomial.head; p2 != nullptr; p2 = p2->next) {
            temp.insert(p1->coefficient * p2->coefficient, p1->exponent + p2->exponent);
        }
        result = result + temp;
    }
    return result;
}

int getValidInt() {
    int value;
    while (!(cin >> value)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter an integer: ";
    }
    return value;
}

int main() {
    List polynomial1, polynomial2;
    int choice;
    int coeff, exp, x;
    while (true) {
        cout << "\nMenu:\n1. Insert term in Polynomial 1\n2. Insert term in Polynomial 2\n3. Display Polynomial 1\n";
        cout << "4. Display Polynomial 2\n5. Add Polynomials\n6. Subtract Polynomial 1 - Polynomial 2\n";
        cout << "7. Multiply Polynomials\n8. Evaluate Polynomial 1\n9. Evaluate Polynomial 2\n10. Exit\n";
        cout << "Enter choice: ";
        choice = getValidInt();

        if (choice == 10) break;

        int coeff, exp, x;
        switch (choice) {
        case 1:
            cout << "Enter coefficient for Polynomial 1: ";
            coeff = getValidInt();
            cout << "Enter exponent for Polynomial 1: ";
            exp = getValidInt();
            polynomial1.insert(coeff, exp);
            break;
        case 2:
            cout << "Enter coefficient for Polynomial 2: ";
            coeff = getValidInt();
            cout << "Enter exponent for Polynomial 2: ";
            exp = getValidInt();
            polynomial2.insert(coeff, exp);
            break;
        case 3:
            cout << "Polynomial 1: ";
            polynomial1.display();
            break;
        case 4:
            cout << "Polynomial 2: ";
            polynomial2.display();
            break;
        case 5:
            if (polynomial1.isEmpty() || polynomial2.isEmpty()) {
                cout << "Both polynomials must have terms to perform addition. Please enter terms in both polynomials first.\n";
            }
            else {
                List sum = polynomial1 + polynomial2;
                cout << "Sum of Polynomials: ";
                sum.display();
            }
            break;
        case 6:
            if (polynomial1.isEmpty() || polynomial2.isEmpty()) {
                cout << "Both polynomials must have terms to perform subtraction. Please enter terms in both polynomials first.\n";
            }
            else {
                List difference = polynomial1 - polynomial2;
                cout << "Difference (Polynomial 1 - Polynomial 2): ";
                difference.display();
            }
            break;
        case 7:
            if (polynomial1.isEmpty() || polynomial2.isEmpty()) {
                cout << "Both polynomials must have terms to perform multiplication. Please enter terms in both polynomials first.\n";
            }
            else {
                List product = polynomial1 * polynomial2;
                cout << "Product of Polynomials: ";
                product.display();
            }
            break;
        case 8:
            cout << "Enter the value of x to evaluate Polynomial 1: ";
            x = getValidInt();
            cout << "Polynomial 1 evaluated at x = " << x << ": " << polynomial1.evaluate(x) << endl;
            break;
        case 9:
            if (polynomial2.isEmpty()) {
                cout << "Polynomial 2 has no terms. Please enter terms in Polynomial 2 first.\n";
            }
            else {
                cout << "Enter the value of x to evaluate Polynomial 2: ";
                x = getValidInt();
                cout << "Polynomial 2 evaluated at x = " << x << ": " << polynomial2.evaluate(x) << endl;
            }
            break;
        default:
            cout << "Invalid choice, please enter a number from 1 to 10.\n";
        }
    }
    return 0;
}
