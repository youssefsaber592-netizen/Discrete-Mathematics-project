#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

string toTF(bool val) {
    return val ? "T" : "F";
}

string to01(bool val) {
    return val ? "1" : "0";
}

string toTrueFalse(bool val) {
    return val ? "True" : "False";
}

bool printTable(bool use01) {

    auto B = [&](bool v) { return use01 ? to01(v) : toTF(v); };

    if (!use01) {
        cout << "==================== TRUTH TABLE (T / F) ====================\n";
    } else {
        cout << "==================== TRUTH TABLE (0 / 1) ====================\n";
    }

    cout << "| P | Q | R | S | Term1(P<->Q) | Term2(!P^R^S) | Term3(!R v !S) | LHS | RHS | Match? |\n";
    cout << "-------------------------------------------------------------------------------\n";

    bool allMatch = true;

    for (int p = 0; p <= 1; p++) {
        for (int q = 0; q <= 1; q++) {
            for (int r = 0; r <= 1; r++) {
                for (int s = 0; s <= 1; s++) {

                    bool bP = p, bQ = q, bR = r, bS = s;

                    bool t1 = (bP == bQ);
                    bool t2 = (!bP && bR && bS);
                    bool t3 = (!bR || !bS);

                    bool lhs = (t1 || t2) && (t1 || t3);
                    bool rhs = (bP == bQ);

                    bool match = (lhs == rhs);
                    if (!match) allMatch = false;

                    cout << "| " << B(bP)
                         << " | " << B(bQ)
                         << " | " << B(bR)
                         << " | " << B(bS)
                         << " |      " << B(t1)
                         << "       |       " << B(t2)
                         << "        |       " << B(t3)
                         << "        |  " << B(lhs)
                         << "  |  " << B(rhs)
                         << "  |  " << toTrueFalse(match)
                         << " |\n";
                }
            }
        }
    }

    return allMatch;
}

int main() {

    cout << "Question: Are the following logical expressions equivalent?\n";
    cout << "LHS = [(P<->Q) v (!P^R^S)] ^ [(!P<->!Q) v (!R v !S)]\n";
    cout << "RHS = [P <=> Q]\n\n";

    bool tfMatch = printTable(false);

    cout << "\n\n";

    bool numMatch = printTable(true);

    if (tfMatch && numMatch) {
        cout << "\nResult: The expressions are logically equivalent.\n";
    } else {
        cout << "\nResult: The expressions are NOT logically equivalent.\n";
    }

    system("pause");
    return 0;
}