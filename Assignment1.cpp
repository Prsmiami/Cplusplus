#include <string>
#include <iostream>

using namespace std;

struct Node {

	string data;
	Node *left;
	Node *right;

	Node() {
		data = "";
		left = NULL;
		right = NULL;
	};
};

int chartoint(char temp) {

	if (temp >= 65 && temp <= 90) temp = temp + 32;
	if (temp >= 97 && temp <= 122) return temp;
	else return 0;

};

int lowmidhigh(string input, string compare) {

	int inputi = 0;
	int comparei = 0;
	while (true) {

		if (input[inputi] == NULL&&compare[comparei] == NULL) return 1;
		if (input[inputi] == NULL) return 0;
		if (compare[comparei] == NULL) return 2;
		if (chartoint(input[inputi])<chartoint(compare[comparei])) return 0;
		if (chartoint(input[inputi])>chartoint(compare[comparei])) return 2;
		inputi++;
		comparei++;

	}
};


struct Tree {

	Node *topnode;

	Tree() {
		topnode = NULL;
	};

	void Addnode(string input) {

		if (topnode == NULL) {

			Node *newnode = new Node;
			newnode->data = input;
			topnode = newnode;
			return;

		}

		Node *tptr = topnode;

		while (true) {
			string compare = tptr->data;
			if (lowmidhigh(input, compare) == 1) return;
			if (lowmidhigh(input, compare) == 0) {

				if (tptr->left == NULL) {

					Node *newnode = new Node;
					newnode->data = input;
					tptr->left = newnode;
					return;
				}
				else tptr = tptr->left;
			}

			if (lowmidhigh(input, compare) == 2) {

				if (tptr->right == NULL) {

					Node *newnode = new Node;
					newnode->data = input;
					tptr->right = newnode;
					return;
				}
				else tptr = tptr->right;

			}
		}
	};

	bool Findnode(string input, Node *recurnode) {

		if (recurnode == NULL)recurnode = topnode;
		if (recurnode->data == input)return 1;
		if (recurnode->left != NULL) {
			if (Findnode(input, recurnode->left)) return 1;
		}
		if (recurnode->right != NULL) {
			if (Findnode(input, recurnode->right)) return 1;
		}
		return 0;
	};
};


int main() {

	Tree *stringtree = new Tree;
	string usrentry = "";
	while (usrentry != "cont") {

		cout << "Please enter a string and hit enter. Type {cont} to continue to search." << endl;
		cin >> usrentry;
		stringtree->Addnode(usrentry);

	}
	usrentry = "";
	bool flag = 0;
	while (usrentry != "cont") {

		cout << "Please enter a string to search from your previous entries and hit enter. Type {cont} to exit." << endl;
		cin >> usrentry;
		if (usrentry != "cont") {

			flag = stringtree->Findnode(usrentry, NULL);
			if (!flag) cout << "No" << endl;
			if (flag) cout << "Yes" << endl;

		}
	}
	return 0;
}
