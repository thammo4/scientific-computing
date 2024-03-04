#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <iomanip>

using namespace std;


//
// Tree node structure
//

struct Node {
	char ch;
	int freq;
	Node *left, *right;
};



//
// Function to allocate a new tree node
//

Node* get_node (char ch, int freq, Node* left, Node* right) {
	Node* node = new Node();

	node->ch = ch;
	node->freq = freq;
	node->left = left;
	node->right = right;

	return node;
};


//
// Compare elements of heap
//

struct compare_elems {
	bool operator ()(Node* l, Node* r) {
		return l->freq > r->freq;
	}
};


//
// Traverse the Huffman Tree -> Encode source symbols
//

void encode (Node* root, string str, unordered_map<char,string> &huffman_code) {
	if (root == nullptr) {
		return;
	}

	if (! root->left && !root->right) {
		huffman_code[root->ch] = str;
	}

	encode(root->left, str+"0", huffman_code);
	encode(root->right, str+"1", huffman_code);
}


//
// Traverse Huffman Tree -> decode codewords
//

void decode (Node* root, int &index, string str) {
	if (root == nullptr) {
		return;
	}

	if (!root->left && !root->right) {
		cout << root->ch;
		return;
	}

	index++;

	if (str[index] == '0') {
		decode(root->left, index, str);
	} else {
		decode(root->right, index, str);
	}
}


//
// Construct the Huffman Tree
//

void construct_huffman_tree (string text) {

	//
	// Establish frequency counts for each symbol occurring in the input string
	//

	unordered_map<char,int> freq;
	for (char ch: text) {
		freq[ch]++;
	}

	int input_length = text.length();
	cout << "Total Input Length: " << text.length() << "\n";

	cout << "\nFREQUENCY DISTRIBUTION OF INPUT SYMBOLS\n\n";
	cout << "Symbol " << "\t" << "Frequency " << "\t" << "Rel Freq" << "\n";

	unordered_set<char> printed_symbol;
	for (char ch: text) {
		if (printed_symbol.find(ch) == printed_symbol.end()) {
			double relative_frequency = static_cast<double>(freq[ch]) / input_length;
			cout << ch << " " << "\t" << freq[ch] << " " << "\t\t" << std::fixed << std::setprecision(3) << relative_frequency << "\n";
			printed_symbol.insert(ch);
		}
	}

	// unordered_set<char> printed_symbol;
	// for (char ch: text) {
	// 	if (printed_symbol.find(ch) == printed_symbol.end()) {
	// 		cout << ch << " " << "\t" << freq[ch] << "\n";
	// 		printed_symbol.insert(ch);
	// 	}
	// }

	//
	// Priority queue to store Huffman nodes
	//

	priority_queue<Node*, vector<Node*>, compare_elems> pq;

	//
	// Create leaf node for each character -> add to priority queue
	//

	for (auto pair: freq) {
		pq.push(get_node(pair.first, pair.second, nullptr, nullptr));
	}

	while (pq.size() != 1) {
		Node *left = pq.top();
		pq.pop();

		Node *right = pq.top();
		pq.pop();

		int sum = left->freq + right->freq;
		pq.push(get_node('\0', sum, left, right));
	}

	//
	// Pointer to root of the Huffman tree
	//

	Node* root = pq.top();

	//
	// Traverse Huffman tree -> store Huffman codes
	//

	unordered_map<char, string> huffman_code;
	encode(root, "", huffman_code);

	cout << "\nHuffman Codes:\n" << '\n';
	for (auto pair: huffman_code) {
		cout << pair.first << " " << pair.second << '\n';
	}

	cout << "\nOriginal String: " << text << '\n';

	string str = "";
	for (char ch: text) {
		str += huffman_code[ch];
	}
	cout << "\nEncoded String: " << str << '\n';

	//
	// Traverse Huffman Tree and decode codewords
	//

	int index = -1;
	cout << "\nDecoded String:\n";
	while (index < (int) str.size() - 2) {
		decode(root, index, str);
	}
}




int main () {
	// string text = "hello world hello world hello world hello world";
	string text = "hello world";

	construct_huffman_tree(text);
	cout << '\n';

	return 0;
}



//
// SAMPLE OUTPUT FOR `hello world`
//

// Total Input Length: 11
//
// FREQUENCY DISTRIBUTION OF INPUT SYMBOLS
//
// Symbol 	Frequency 	Rel Freq
// h 	1 		0.091
// e 	1 		0.091
// l 	3 		0.273
// o 	2 		0.182
//   	1 		0.091
// w 	1 		0.091
// r 	1 		0.091
// d 	1 		0.091
//
// Huffman Codes:
//
//   1101
// r 1100
// w 001
// l 10
// o 111
// d 011
// h 010
// e 000
//
// Original String: hello world
//
// Encoded String: 01000010101111101001111110010011
//
// Decoded String:
// hello world