//
// Created by bombehub on 2019/7/3.
//
#pragma once
#include <algorithm>
#include <initializer_list>

namespace cdf_list {
    // Node class for a linked list
    template<typename T>
    struct ListNode {
        ListNode(T v, ListNode *n = nullptr) : val{v}, next{n} {};

        // Inserting nn after current node
        void insert(ListNode *nn) {
            if (nn) {
                ListNode *tmp = next;
                next = nn;
                nn->next = tmp;
            }
        }
        T val;
        ListNode *next;
    };

    // Singly linked list class
    template<typename T>
    struct LinkList {
        LinkList() : head{nullptr}, end{head}, sz{0} {};

        // Create linked list by passing a list of values like {1,2,3} : 1 -> 2 -> 3
        LinkList(std::initializer_list<T> l) : sz{0} {
            auto it = l.begin();

            head = new ListNode<T>{*it++};
            end = head;
            ++sz;

            while (it != l.end()) {
                end->insert(new ListNode<T>{*it});
                end = end->next;
                ++it;
                ++sz;
            }
        }

        const ListNode<T> *get_head() const {
            return head;
        }

        const ListNode<T> *get_end() const {
            return end;
        }

        const size_t size() const {
            return sz;
        }

        const ListNode<T> *find(const T &key) const {
            const ListNode<T> *x = head;

            if (head) {
                while (x != nullptr && x->val != key) {
                    x = x->next;
                }
            }

            return (x && x->val == key) ? x : nullptr;
        }

        void push_back(ListNode<T> *const n) {
            if (!n) {
                return;
            }

            if (!head) {
                head = n;
                end = head;
            } else {
                end->insert(n);
                end = end->next;
            }
        }

        void push_back(T n) {
            if (!head) {
                head = new ListNode<T>{n};
                end = head;
            } else {
                end->next = new ListNode<T>{n};
                end = end->next;
            }
        }

        ~LinkList() {
            ListNode<T> *p = head;

            while (p) {
                ListNode<T> *tmp = p->next;

                delete p;

                p = tmp;
            }

            head = nullptr;
            end = nullptr;
        }

    private:
        ListNode<T> *head;
        ListNode<T> *end;
        size_t sz;
    };
// Printing whole skip list
    template<typename T>
    void print_link(const LinkList<T> &l) {
        const ListNode<T> *p = l.get_head();

        while (p) {
            std::cout << p->val;
            if (p->next) {
                std::cout << " -> ";
            }

            p = p->next;
        }
        std::cout << std::endl;
    }
}
