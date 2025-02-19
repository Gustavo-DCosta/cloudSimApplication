#include <iostream>
using namespace std;

void inches() {
    double inches, cm;
    cout << "How many inch(es) would you like to convert?: " << endl;
    cin >> inches;
    cm = 2.54 * inches;
    cout << "The result of " << inches << " inch(es) to cm is " << cm << " cm" << endl;
}

void foot() {
    double foot, cm;
    cout << "How many foot/feet would you like to convert?: " << endl;
    cin >> foot;
    cm = 30.48 * foot;
    cout << "The result of " << foot << " foot/feet to cm is " << cm << " cm" << endl;
}

void yard() {
    double yard, cm;
    cout << "How many yard(s) would you like to convert?: " << endl;
    cin >> yard;
    cm = 91.44 * yard;
    cout << "The result of " << yard << " yard(s) to cm is " << cm << " cm" << endl;
}

void mile() {
    double mile, km;
    cout << "How many mile(s) would you like to convert?: " << endl;
    cin >> mile;
    km = 1.60934 * mile;
    cout << "The result of " << mile << " mile(s) to km(s) is " << km << " km" << endl;
}

void ounce() {
    double ounce, gram;
    cout << "How many ounce(s) would you like to convert?: " << endl;
    cin >> ounce;
    gram = 28.3495 * ounce;
    cout << "The result of " << ounce << " ounce(s) to gram(s) is " << gram << " g" << endl;
}

void pound() {
    double pound, kg;
    cout << "How many pound(s) would you like to convert?: " << endl;
    cin >> pound;
    kg = 0.453592 * pound;
    cout << "The result of " << pound << " pound(s) to kg(s) is " << kg << " kg" << endl;
}

void pint() {
    double pint, mL;
    cout << "How many pint(s) would you like to convert?: " << endl;
    cin >> pint;
    mL = 473.176 * pint;
    cout << "The result of " << pint << " pint(s) to mL is " << mL << " mL" << endl;
}

void gallon() {
    double gallon, L;
    cout << "How many gallon(s) would you like to convert?: " << endl;
    cin >> gallon;
    L = 3.78541 * gallon;
    cout << "The result of " << gallon << " gallon(s) to L is " << L << " L" << endl;
}

int main() {
    string response;
    cout << "Choose a conversion from the following list:" << endl;

    string list_functions[] = {"inches_cm", "foot_cm", "yard_cm", "mile_km", "ounce_gm", "pound_kg", "pint_mL", "gallon_L : "};
    int list_size = sizeof(list_functions) / sizeof(list_functions[0]);

    // Loop to print each element
    for (int i = 0; i < list_size; i++) {
        cout << list_functions[i] << " ";
    }
    cout << endl;

    cin >> response;

    if (response == "inches_cm") {
        inches();
    } else if (response == "foot_cm") {
        foot();
    } else if (response == "yard_cm") {
        yard();
    } else if (response == "mile_km") {
        mile();
    } else if (response == "ounce_gm") {
        ounce();
    } else if (response == "pound_kg") {
        pound();
    } else if (response == "pint_mL") {
        pint();
    } else if (response == "gallon_L") {
        gallon();
    } else {
        cout << "Invalid selection. Please try again." << endl;
    }
}
