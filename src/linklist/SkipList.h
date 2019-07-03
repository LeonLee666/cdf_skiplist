#pragma once

#include <random>
#include <algorithm>
#include <initializer_list>
#include "LinkList.h"

namespace cdf_list {
    // Skip node class for Skip list algorithm
    // Each node has certain level and several pointers to neighbours
    template<typename T>
    struct Skip_node {
        Skip_node(int k, T v, size_t levels) : key{k}, val{v}, levels{levels}, next{new Skip_node<T> *[levels]},
                                               prev{new Skip_node<T> *[levels]} {
            for (size_t i = 0; i < levels; ++i) {
                next[i] = nullptr;
                prev[i] = nullptr;
            }
        }

        ~Skip_node() {
            delete[] next;
            delete[] prev;
        }

        int key;
        T val;
        size_t levels;
        Skip_node<T> **next;
        Skip_node<T> **prev;
    };

    // Skip list class
    template<typename T>
    class Skip_list {
    public:
        // Max level of a skip list
        static constexpr size_t max_lvl = 32;
        // Generating random level for Skip Nodes
        size_t random_lvl() {
            int level = 1;
            while (level<max_lvl && rand()%10 < 5) {
                level++;
            }
            return level;
        }

        Skip_list() : head{new Skip_node<T>(std::numeric_limits<int>::min(), T{}, max_lvl)},
                      end{new Skip_node<T>(std::numeric_limits<int>::max(), T{}, max_lvl)} {
            for (size_t i = 0; i < max_lvl; ++i) {
                head->next[i] = end;
                end->prev[i] = head;
            }
            srand(12345);
        }

        const Skip_node<T> *get_head() const {
            return head;
        }

        Skip_node<T> &get_head() {
            return *head;
        }

        bool search(int key) const {
            const Skip_node<T> *x = head;

            for (auto i = max_lvl - 1; i >= 0 && i < max_lvl; --i) {
                while (x->next[i]->key < key) {
                    x = x->next[i];
                }
            }
            return (x->next[0]->key == key) ? true : false;
        }

        void insert(int key, T new_val) {
            Skip_node<T> *update[max_lvl];
            Skip_node<T> *x = head;

            for (auto i = max_lvl - 1; i >= 0 && i < max_lvl; --i) {
                while (x->next[i]->key < key) {
                    x = x->next[i];
                }
                update[i] = x;
            }

            x = x->next[0];

            if (x->key == key) {
                x->val = new_val;
            } else {
                size_t new_lvl = random_lvl();
                Skip_node<T> *n = new Skip_node<T>{key, new_val, new_lvl};

                for (auto i = 0; i < new_lvl; ++i) {
                    n->next[i] = update[i]->next[i];
                    n->prev[i] = update[i];
                    update[i]->next[i]->prev[i] = n;
                    update[i]->next[i] = n;
                }
            }
        }

        void delete_node(int key) {
            Skip_node<T> *update[max_lvl];
            Skip_node<T> *x = head;

            for (auto i = max_lvl - 1; i >= 0 && i < max_lvl; --i) {
                while (x->next[i]->key < key) {
                    x = x->next[i];
                }
                update[i] = x;
            }

            x = x->next[0];

            if (x->key == key) {
                for (auto i = 0; i < max_lvl; ++i) {
                    if (update[i]->next[i] != x) {
                        break;
                    }
                    update[i]->next[i] = x->next[i];
                }

                delete x;
            }
        }

        // Delete all nodes from a list
        void clear() {
            Skip_node<T> *p = head->next[0];

            while (p != end) {
                Skip_node<T> *t = p->next[0];

                delete p;

                p = t;
            }
        }

        void toString() const {
            for (auto i = max_lvl - 1; i >= 0 && i < max_lvl; --i) {
                const Skip_node<T> *p = head;

                while (p) {
                    std::cout << p->key << " (" << p->val << ")";

                    if (p->next[i]) {
                        std::cout << " -> ";
                    }
                    p = p->next[i];
                }

                std::cout << std::endl;
            }
        }

        ~Skip_list() {
            clear();

            delete head;
            delete end;
        }

    private:
        void end_prepend(Skip_node<T> *const n, size_t lvl) {
            for (auto i = 0; i < lvl; ++i) {
                n->next[i] = end;
                n->prev[i] = end->prev[i];
                end->prev[i]->next[i] = n;
                end->prev[i] = n;
            }
        }

        void head_append(Skip_node<T> *const n, size_t lvl) {
            for (auto i = 0; i < lvl; ++i) {
                n->prev[i] = head;
                n->next[i] = head->next[i];
                head->next[i]->prev[i] = n;
                head->next[i] = n;
            }
        }

        void push_back(int k, T v) {
            if (!search(k)) {
                size_t new_lvl = random_lvl();
                Skip_node<T> *n = new Skip_node<T>{k, v, new_lvl};

                end_prepend(n, new_lvl);
            }
        }

        void push_back(Skip_node<T> *n) {
            if (n) {
                if (!search(n->key)) {
                    size_t lvl = std::min(n->levels, max_lvl);

                    end_prepend(n, lvl);
                }
            }
        }

        void push_front(int k, T v) {
            if (!search(k)) {
                size_t new_lvl = random_lvl();
                Skip_node<T> *n = new Skip_node<T>{k, v, new_lvl};

                head_append(n, new_lvl);
            }
        }

        void push_front(Skip_node<T> *const n) {
            if (n) {
                if (!search(n->key)) {
                    size_t lvl = std::min(n->levels, max_lvl);

                    head_append(n, lvl);
                }
            }
        }



        Skip_node<T> *head;
        Skip_node<T> *end;
    };
} // cdf_list
