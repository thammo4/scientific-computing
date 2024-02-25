#include <iostream>
#include <queue>
#include <vector>
#include <map>



// THIS DOESNT WORK BUT IDK WHY WTF


//
// Define tree node
//

struct Node {
	char ch;
	int freq;
	Node *left, *right;
};

Node* get_node (char ch, int freq, Node* left, Node* right) {
	Node* node = new Node();

	node->ch = ch;
	node->freq = freq;

	node->left = left;
	node->right = right;

	return node;
};


//
// Comparisons for heap
// • Assign the highest priority to the lowest frequency
//

struct comp {
	bool operator() (Node* l, Node* r) {
		return l->freq > r->freq;
	}
};



//
// Xverse Huffman tree -> Store Huffman Codes
//

void encode (Node* root, std::string str, std::map<char, std::string> &huffman_code) {
	if (root == nullptr) {
		return;
	}

	//
	// Identify left node
	//

	if (! root->left && ! root->right) {
		huffman_code[root->ch] = str;
	}

	encode(root->left, str + "0", huffman_code);
	encode(root->right, str + "1", huffman_code);
}




void construct_huffman_tree (std::string text) {
	std::map<char, int> freq;
	for (char ch: text) {
		freq[ch]++;
	}

	std::priority_queue<Node*, std::vector<Node*>, comp> pq;

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

	Node* root = pq.top();

	std::map<char, std::string> huffman_code;
	encode(root, "", huffman_code);

	std::cout << "Huffman codes:" << std::endl;
	for (auto pair: huffman_code) {
		std::cout << pair.first << " " << pair.second << std::endl;
	}
}

int main() {
	std::string text = "HUFFMAN CODING ALGORITHM";
	construct_huffman_tree(text);

	return 0;
}











