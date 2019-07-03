#pragma once

#include <random>
#include <algorithm>
#include <initializer_list>

namespace cdf_list {
    // Skip node class for Skip list algorithm
    // Each node has certain level and several pointers to neighbours
    template<typename T>
    struct Skip_node {
        Skip_node(float k, T v, size_t levels) : key{k}, val{v}, levels{levels}, next{new Skip_node<T> *[levels]},
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

        float key;
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

        Skip_list() : head{new Skip_node<T>(std::numeric_limits<float>::min(), T{}, max_lvl)},
                      end{new Skip_node<T>(std::numeric_limits<float>::max(), T{}, max_lvl)} {
            for (size_t i = 0; i < max_lvl; ++i) {
                head->next[i] = end;
                end->prev[i] = head;
            }
        }

        const Skip_node<T> *get_head() const {
            return head;
        }

        Skip_node<T> &get_head() {
            return *head;
        }

        bool search(float key) const {
            const Skip_node<T> *x = head;

            for (auto i = max_lvl - 1; i >= 0 && i < max_lvl; --i) {
                while (x->next[i]->key < key) {
                    x = x->next[i];
                }
            }
            return (x->next[0]->key == key) ? true : false;
        }

        void insert(float key, T new_val, size_t new_lvl) {
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
                Skip_node<T> *n = new Skip_node<T>{key, new_val, new_lvl};

                for (auto i = 0; i < new_lvl; ++i) {
                    n->next[i] = update[i]->next[i];
                    n->prev[i] = update[i];
                    update[i]->next[i]->prev[i] = n;
                    update[i]->next[i] = n;
                }
            }
        }

        void delete_node(float key) {
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
        Skip_node<T> *head;
        Skip_node<T> *end;
    };
} // cdf_list
