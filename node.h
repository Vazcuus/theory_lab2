#pragma once
#include <iostream>

class node
{
    char ch;
    float odds;
    node *left, *right;

    public:
        node() {};
        node(char _ch, float _odds);
};

node::node(char _ch, float _odds)
{
	left = right = NULL;
	ch = _ch;
	odds = _odds;
}
