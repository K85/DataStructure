#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <functional>
#include <algorithm>
#include <numeric>

using namespace std;

template<typename K, typename V>
class SkipList{

    /* Struct Node */
public:
    template<typename K, typename V>
    class Node {
        typedef pair<const K, V> PairType; // NOTE: use typedef for convenience.

    public:
        PairType element;
        Node<K, V> **next; // NOTE: the array of pointers.

    public:
        Node(const PairType& pair, int size) : element(pair) {
            next = new Node<K, V>* [size];
        }
    };

    /* Class Props */
    float cut_off; // cut_off use for calc level
    int cur_max_level; // currently max not-null list
    int limit_max_level; // allowed max list cur_max_level.
    K limit_tail_key; // max key

    Node<K, V> *header_node;
    Node<K, V> *tail_node;
    Node<K, V> ** last; // last[i] means the last node in level i.
    int dictionary_size; // the pair amount of dictionary

    /* Constructors */
public:
    SkipList(K largest_key, int max_pairs, float prob) {
        // init props
        cut_off = prob * RAND_MAX;
        limit_max_level = (int) ceil(logf((float) max_pairs) / logf(1 / prob)) - 1;
        cur_max_level = 0;
        limit_tail_key = largest_key;
        dictionary_size = 0;

        // gen head, tail, and last.
        pair<K, V> tail_pair;
        tail_pair.first = limit_tail_key;

        header_node = new Node<K, V> (tail_pair, limit_max_level + 1);
        tail_node = new Node<K, V>(tail_pair, 0);
        last = new Node<K, V> * [limit_max_level + 1];

        // when list is empty: set all cur_max_level' headers point to tail node.
        for (int i = 0; i <= limit_max_level; i++)
            header_node->next[i] = tail_node;
    }

    /* Operation Functions */
public:
    pair<const K, V> * find(const K & key) const {
        // key too big ?
        if (key >= limit_tail_key) return nullptr;

        // store prev node.
        Node<K, V>* max_less_than_node = header_node;
        for (int i = cur_max_level; i >= 0; i--) {
            // locate
            while (max_less_than_node->next[i]->element.first < key)
                max_less_than_node = max_less_than_node->next[i];

            // check if we find.
            if (max_less_than_node->next[0]->element.first == key)
                return &max_less_than_node->next[0]->element; // NOTE: next[0] means the node itself
            else return nullptr;
        }
    }

    // generate random valid level.
public:
    int get_random_valid_level() const {
        int random_level = 0;
        while (rand() <= cut_off) random_level++;
        return min(random_level, limit_max_level);
    }


public:
    Node<K, V>* search(const K& key) const {

        Node<K, V> * max_less_than_node = header_node;
        for (int i = cur_max_level; i >= 0 ; i--) {
            // locate
            while (max_less_than_node->next[i]->element.first < key)
                max_less_than_node = max_less_than_node->next[i];

            last[i] = max_less_than_node; // NOTE: update last in every level
        }

        return max_less_than_node->next[0];
    }

public:
    void insert(const pair<const K, V> & target) {

        // is the key of target node too max ?
        if (target.first >= limit_tail_key) return;

        // already exist ?
        Node<K, V> * searched_node = search(target.first);
        if (searched_node->element.first == target.first) {
            // yes, update value.
            searched_node->element.second = target.second;
            return;
        }

        // not exist !
        int insert_level = get_random_valid_level();
        if (insert_level > cur_max_level) {
            // create a new level !
            insert_level = ++cur_max_level;
            last[insert_level] = header_node;
        }

        // insert node.
        Node<K, V> * new_node = new Node<K, V>(target, insert_level + 1);
        for (int i = 0; i <= insert_level; i++) {
            // insert the new node into level i: just like SLL.
            new_node->next[i] = last[i]->next[i];
            last[i]->next[i] = new_node;
        }

        // update props
        dictionary_size++;
    }

public:
    void erase(const K & key) {
        // key > max key ?
        if (key >= limit_tail_key) return;

        // can find ?
        Node<K, V> * searched_node = search(key);
        if(searched_node->element.first != key) return;

        // delete node
        for (int i = 0; i <= cur_max_level && last[i]->next[i] == searched_node; i++)
            last[i]->next[i] = searched_node->next[i]; // NOTE: just like SLL

        // should delete the highest level (when the level is empty elements !)?
        while (cur_max_level > 0 && header_node->next[cur_max_level] == tail_node)
            cur_max_level--;

        // free
        delete searched_node;

        // update props
        dictionary_size--;
    }

};

int main() {

    SkipList<int, string> sl(100, 30, 0.5);
    auto p1 = new pair<int, string>(10, "value is 10");
    sl.insert(*p1);
    auto p2 = new pair<int, string>(20, "value is 20");
    sl.insert(*p2);
    return 0;
}
