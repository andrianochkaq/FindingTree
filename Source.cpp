#include <iostream>
#include "BST.h"
#include "RBTree.h"
#include "Tree234.h"

using namespace std;

void print234(Tree234& tree, const char* name) {
    cout << "\n" << name << ":\n";
    tree.print();

    cout << "Height: " << tree.height() << endl;
    cout << "Nodes: " << tree.size()
        << ", keys: " << tree.keysCount() << endl;
}
// =====================================================
// BST output
// =====================================================
void printBST(BST& tree, const char* name) {
    cout << "\n" << name << ":\n";
    tree.print();

    cout << "Height: "
        << tree.height() << endl;
}

// =====================================================
// RB Tree output
// =====================================================
void printRB(RBTree& tree, const char* name) {
    cout << "\n" << name << ":\n";
    tree.print();

    cout << "Height: "
        << tree.height() << endl;
}

// =====================================================
// Check whether two trees contain the same set of keys(TASK B)
// =====================================================
// Check all keys of the first tree in the second tree.
// The number of nodes must also be the same.
bool equalBST(BST& first, BST& second, int data[], int count, int& visited) {
    visited = 0;

    if (first.size() != second.size())
    {
        return false;
    }

    for (int i = 0; i < count; i++)
    {
        int currentVisited = 0;

        bool found =
            second.search(data[i], currentVisited);

        visited += currentVisited;

        if (!found)
        {
            return false;
        }
    }

    return true;
}

bool equalRB(RBTree& first, RBTree& second, int data[], int count, int& visited) {
    visited = 0;

    if (first.size() != second.size())
    {
        return false;
    }

    for (int i = 0; i < count; i++)
    {
        int currentVisited = 0;

        bool found =
            second.search(data[i], currentVisited);

        visited += currentVisited;

        if (!found)
        {
            return false;
        }
    }

    return true;
}

// =====================================================
// MAIN
// =====================================================
int main() {

    // =================================================
    // Initial data
    // =================================================

    int data1[] =
    {
        50, 30, 70, 20, 40,
        60, 80, 10, 25, 35,
        45, 55, 65, 75, 90
    };

    int data2[] =
    {
        40, 20, 60, 10, 30,
        50, 71, 5, 15, 25,
        35, 45, 55, 65, 75
    };

    int count1 =
        sizeof(data1) / sizeof(data1[0]);

    int count2 =
        sizeof(data2) / sizeof(data2[0]);


    // =================================================
    // Create trees
    // =================================================

    BST bstT1;
    BST bstT2;

    RBTree rbT1;
    RBTree rbT2;


    // =================================================
    // Fill trees
    // =================================================

    int visited = 0;

    for (int i = 0; i < count1; i++)
    {
        bstT1.insert(data1[i], visited);
        rbT1.insert(data1[i], visited);
    }

    for (int i = 0; i < count2; i++)
    {
        bstT2.insert(data2[i], visited);
        rbT2.insert(data2[i], visited);
    }


    // =================================================
    // Copies of the initial trees
    //
    // They will be used in Task C.
    // =================================================

    BST bstT1Copy;
    BST bstT2Copy;

    RBTree rbT1Copy;
    RBTree rbT2Copy;

    bstT1.copyTo(bstT1Copy);
    bstT2.copyTo(bstT2Copy);

    rbT1.copyTo(rbT1Copy);
    rbT2.copyTo(rbT2Copy);


    // =================================================
    // INITIAL STATE
    // =================================================

    cout << "========================================\n";
    cout << "INITIAL TREES\n";
    cout << "========================================\n";

    printBST(bstT1, "BST T1");
    printBST(bstT2, "BST T2");

    printRB(rbT1, "RB T1");
    printRB(rbT2, "RB T2");


    // =================================================
    // Counters
    // =================================================

    int visitedA_BST = 0;
    int visitedA_RB = 0;

    int visitedB_BST = 0;
    int visitedB_RB = 0;

    int visitedC_BST = 0;
    int visitedC_RB = 0;


    // =================================================
    // TASK A
    //
    // Print the keys of tree T
    // in descending order.
    // =================================================

    cout << "\n\n========================================\n";
    cout << "TASK A\n";
    cout << "Print keys in descending order\n";
    cout << "========================================\n";

    cout << "\nBST T1:\n";

    bstT1.printDescending(visitedA_BST);

    cout << "Visited nodes: "
        << visitedA_BST << endl;


    cout << "\nRB T1:\n";

    rbT1.printDescending(visitedA_RB);

    cout << "Visited nodes: "
        << visitedA_RB << endl;


    cout << "\nTrees after Task A:" << endl;

    printBST(bstT1, "BST T1");

    printRB(rbT1, "RB T1");


    // =================================================
    // TASK B
    //
    // Insert all keys of T2 into T1.
    //
    // The number of visited nodes is counted
    // directly during each insertion.
    // =================================================

    cout << "\n\n========================================\n";
    cout << "TASK B\n";
    cout << "Insert all keys of T2 into T1\n";
    cout << "========================================\n";


    visitedB_BST = 0;

    for (int i = 0; i < count2; i++)
    {
        int currentVisited = 0;

        bstT1.insert(
            data2[i],
            currentVisited
        );

        visitedB_BST += currentVisited;
    }


    visitedB_RB = 0;

    for (int i = 0; i < count2; i++)
    {
        int currentVisited = 0;

        rbT1.insert(
            data2[i],
            currentVisited
        );

        visitedB_RB += currentVisited;
    }


    cout << "\nBST T1 after inserting T2:\n";

    bstT1.print();

    cout << "BST T1 height: "
        << bstT1.height() << endl;

    cout << "Visited nodes during insertion: "
        << visitedB_BST << endl;


    cout << "\nRB T1 after inserting T2:\n";

    rbT1.print();

    cout << "RB T1 height: "
        << rbT1.height() << endl;

    cout << "Visited nodes during insertion: "
        << visitedB_RB << endl;


    // =================================================
    // TASK C
    //
    // Work NOT with T1 after Task B,
    // but with copies of the initial trees.
    // =================================================

    cout << "\n\n========================================\n";
    cout << "TASK C\n";
    cout << "Check whether the sets of keys are equal\n";
    cout << "========================================\n";


    bool bstEqual = equalBST(
        bstT1Copy,
        bstT2Copy,
        data1,
        count1,
        visitedC_BST
    );


    bool rbEqual = equalRB(
        rbT1Copy,
        rbT2Copy,
        data1,
        count1,
        visitedC_RB
    );


    cout << "\nBST:" << endl;

    if (bstEqual)
    {
        cout << "T1 and T2 contain the same set of keys."
            << endl;
    }
    else
    {
        cout << "T1 and T2 contain different sets of keys."
            << endl;
    }

    cout << "Visited nodes: "
        << visitedC_BST << endl;


    cout << "\nRB:" << endl;

    if (rbEqual)
    {
        cout << "T1 and T2 contain the same set of keys."
            << endl;
    }
    else
    {
        cout << "T1 and T2 contain different sets of keys."
            << endl;
    }

    cout << "Visited nodes: "
        << visitedC_RB << endl;


    // =================================================
    // Trees after Task C
    //
    // They should remain unchanged because
    // Task C works with copies.
    // =================================================

    cout << "\nTrees after Task C:" << endl;

    printBST(
        bstT1Copy,
        "Initial BST T1"
    );

    printBST(
        bstT2Copy,
        "Initial BST T2"
    );

    printRB(
        rbT1Copy,
        "Initial RB T1"
    );

    printRB(
        rbT2Copy,
        "Initial RB T2"
    );
    // =================================================
// TASK D
//
// Convert Red-Black trees to 2-3-4 trees
// and print both representations.
// =================================================

    cout << "\n\n========================================\n";
    cout << "TASK D\n";
    cout << "Convert Red-Black tree to 2-3-4 tree\n";
    cout << "========================================\n";

    Tree234 t234_1;
    Tree234 t234_2;

    int visitedD_T1 = 0;
    int visitedD_T2 = 0;

    // початкові дерева (копії), щоб був чистий приклад
    rbT1Copy.toTwoThreeFour(t234_1, visitedD_T1);
    rbT2Copy.toTwoThreeFour(t234_2, visitedD_T2);

    printRB(rbT1Copy, "RB T1 (initial)");
    print234(t234_1, "2-3-4 T1");
    cout << "Visited RB nodes: " << visitedD_T1 << endl;

    printRB(rbT2Copy, "RB T2 (initial)");
    print234(t234_2, "2-3-4 T2");
    cout << "Visited RB nodes: " << visitedD_T2 << endl;

    // дерево T1 після Task B (з усіма вставленими ключами)
    Tree234 t234_merged;
    int visitedD_merged = 0;

    rbT1.toTwoThreeFour(t234_merged, visitedD_merged);

    printRB(rbT1, "RB T1 (after Task B)");
    print234(t234_merged, "2-3-4 T1 (after Task B)");
    cout << "Visited RB nodes: " << visitedD_merged << endl;

    // =================================================
    // FINAL TABLE
    // =================================================

    cout << "\n\n========================================\n";
    cout << "TABLE OF VISITED NODES\n";
    cout << "========================================\n\n";


    cout << "+----------+-------------+-----------------------+\n";
    cout << "|   Task   |     BST     |     Red-Black Tree    |\n";
    cout << "+----------+-------------+-----------------------+\n";

    cout << "|    A     |"
        << "     "
        << visitedA_BST
        << "      |"
        << "          "
        << visitedA_RB
        << "          |\n";

    cout << "|    B     |"
        << "     "
        << visitedB_BST
        << "      |"
        << "          "
        << visitedB_RB
        << "          |\n";

    cout << "|    C     |"
        << "     "
        << visitedC_BST
        << "      |"
        << "          "
        << visitedC_RB
        << "          |\n";

    cout << "+----------+-------------+-----------------------+\n";


    // =================================================
    // FREE MEMORY
    //
    // Destructors will also call clear(),
    // but here we explicitly demonstrate the function.
    // =================================================

    bstT1.clear();
    bstT2.clear();

    rbT1.clear();
    rbT2.clear();

    bstT1Copy.clear();
    bstT2Copy.clear();

    rbT1Copy.clear();
    rbT2Copy.clear();
    t234_1.clear();
    t234_2.clear();
    t234_merged.clear();

    cout << "\nMemory occupied by the nodes has been released."
        << endl;

    return 0;
}
