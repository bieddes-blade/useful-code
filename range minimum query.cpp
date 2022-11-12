#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9 + 2;
int n, m;
	
struct Node
{
	int y;
	Node* left;
	Node* right;
	int size, value, minimum;
	bool rev;
};

int size(Node* t) { return t ? t->size : 0; }

int minimum(Node* t) { return t ? t->minimum : INF; }

void update(Node* t)
{
	t->size = 1 + size(t->left) + size(t->right);
	t->minimum = min(t->value, min(minimum(t->left), minimum(t->right)));
}

Node* create_node(int value)
{
	Node* t = new Node();
	t->y = (rand() << 15) ^ rand();
	t->left = t->right = 0;
	t->value = value;
	t->rev = false;
	update(t);
	return t;
}

typedef pair<Node*, Node*> treap_pair;

void push(Node* t)
{
	if (t && t->rev)
	{
		t->rev = false;
		swap(t->left, t->right);
		if (t->left)
			t->left->rev ^= true;
		if (t->right)
			t->right->rev ^= true;
	}
}

treap_pair treap_split(Node* t, int s)
{
	if (t == 0)
		return treap_pair(0, 0);
	push(t);
	treap_pair p;
	if (size(t->left) >= s)
	{
		p = treap_split(t->left, s);
		t->left = p.second;
		p.second = t;
	}
	else
	{
		p = treap_split(t->right, s - size(t->left) - 1);
		t->right = p.first;
		p.first = t;
	}
	update(t);
	return p;
}

Node* treap_merge(Node* a, Node* b)
{	
	if (!a || !b)
		return a ? a : b;

	if (a->y > b->y)
	{
		a->right = treap_merge(a->right, b);
		update(a);
		return a;
	}
	else
	{
		b->left = treap_merge(a, b->left);
		update(b);
		return b;
	}
}

void treap_display(Node* t)
{
	if (t)
	{
		treap_display(t->left);
		cout << t->value << " ";
		treap_display(t->right);
	}
}

int treap_min(Node* t, int left_ind, int right_ind)
{
	treap_pair one, two;
	
	one = treap_split(t, right_ind);
	Node* left = one.first;
	Node* right = one.second;
	
	two = treap_split(left, left_ind);
	left = two.first;
	Node* middle = two.second;
	
	int res = 0;
	if (middle)
		res = middle->minimum;
	
	left = treap_merge(left, middle);
	left = treap_merge(left, right);
	
	return res;
}

int main()
{
	int n;
	cin >> n;

	Node* treap = 0;
	Node* pre_ans;
	treap_pair one;

	char q;
	int x, y;

	for (int i = 0; i < n; ++i)
	{
		cin >> q >> x >> y;

		if (q == '?')
			cout << treap_min(treap, x - 1, y) << "\n";
		else
		{
			one = treap_split(treap, x);
			pre_ans = treap_merge(one.first, create_node(y));
			pre_ans = treap_merge(pre_ans, one.second);
			treap = pre_ans;
		}
	}
	
	return 0;
}
