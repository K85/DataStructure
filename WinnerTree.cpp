#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <functional>
#include <algorithm>
#include <numeric>
#include <queue>

using namespace std;

template<typename T>

// parent = (i + offset) / 2, i <= lowExt
// parent = (i - lowExt + n - 1) / 2, i > lowExt
class WinnerTree {


public:
    class Player {
    public:
        int id;
        int key;

    public:
        Player(int id, int key) : id(id), key(key){}
        Player(){}

        operator int() const {
            return this->key;
        }
    };


public:
    T * A;
    int A_SIZE;
    Player * players;
    int players_amount;
    int lowExt;
    int offset;

public:
    WinnerTree(Player * players, int players_amount) {
        init(players, players_amount);
    }

public:
    void init(Player * players, int players_amount) {

        if (players_amount < 2) {
            printf("ERROR: must have at least 2 players !\n");
            return;
        }

        // malloc array for tree.
        this->A_SIZE = players_amount + 1;
        this->A = new T[A_SIZE]; // NOTE: we don't use A[0]
        this->players_amount = players_amount;
        this->players = players; // get players !

        // calc the leftest internal node.
        int i, s;
        for (s = 1; 2 * s <= players_amount - 1; s += s);

        lowExt = 2 * (players_amount - s);
        offset = 2 * s - 1;

        // play matches for lowest-level external nodes !
        for (int i = 2; i <= lowExt; i += 2)
            play((i + offset) / 2, i - 1, i);

        // handle remaining external nodes.
        if (players_amount % 2 == 1) {
            // special 1 play
            play(players_amount / 2, A[players_amount - 1], lowExt + 1);
            i = lowExt + 3;
        } else i = lowExt + 2;


        // i is left-most remaining external node
        for (;i <= players_amount; i += 2)
            play((i - lowExt + players_amount - 1) / 2 , i - 1, i);
    }

public:
    int winner(){
        return A[1];
    }

public:
    void play(int p, int left_child, int right_child) {

        // set p's parent the value of the laeger one.
        A[p] = (players[left_child] <= players[right_child]) ? left_child : right_child;

        // more matches possible if at right child. let's continue !
        while (p % 2 == 1 && p > 1) {
            // now, we are at a right child.
            A[p / 2] = (players[A[p - 1]] <= players[A[p]]) ? A[p - 1] : A[p];
            p /= 2; // go to parent !
        }
    }

public:
    void replay(int player){

        // replay matches for player.
        if (player <= 0 || player > A_SIZE) {
            printf("invalid player !\n");
            return;
        }

        // find first match node and its child.
        int match_node, left_child, right_child;
        if (player <= lowExt) {
            match_node = (player + offset) / 2;
            left_child = 2 * match_node - offset;
            right_child = left_child + 1;
        } else {
            left_child = 2 * match_node - n + 1 + lowExt;
            right_child = left_child + 1;
        }

        A[match_node] = (players[left_child] <= players[right_child]) ? left_child : right_child;

        // special case for second match
        if (match_node == n - 1 && n % 2 == 1) {
            match_node /= 2;
            A[match_node] = (players[A[A_SIZE - 1]] <= players[lowExt + 1]) ?
                            A[A_SIZE - 1] : lowExt + 1;
        }

        // play remaining matches
        match_node /= 2;
        for (;match_node >= 1; match_node /= 2) {
            A[match_node] = (players[A[2 * match_node]] <= players[A[2 * match_node + 1]]) ?
                            A[2 * match_node] :
                            A[2 * match_node + 1];
        }
    }


public:
    void trace() {
        for (int i = 0; i < A_SIZE; i++) {
            cout << "A[" << i << "] = " << A[i] << endl;
        }
    }


};

int main() {

    WinnerTree<int>::Player * players = new WinnerTree<int>::Player[5];
    players[0] = new WinnerTree<int>::Player(0, 100);
    players[1] = new WinnerTree<int>::Player(1, 200);
    players[2] = new WinnerTree<int>::Player(2, 300);
    players[3] = new WinnerTree<int>::Player(3, 400);
    players[4] = new WinnerTree<int>::Player(4, 500);

    WinnerTree<int> wt(players, 5);
    wt.trace();

    return 0;
}

