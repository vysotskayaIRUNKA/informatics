#include <iostream>
struct subset_node {
	int key;
	subset_node *left;
	subset_node *right;
	// unsigned int height;
};

bool init(subset_node **root)
{
	(*root) = NULL;
	return true;
}

bool insert(subset_node **root, int value)
{
	if (!(*root)) {
		*root = new subset_node;
		(*root)->key = value;
		(*root)->left = NULL;
		(*root)->right = NULL;
		//(*root)->height = 1;
		return true;
	}
	if ((*root)->key < value)
		insert(&(*root)->right, value);
	else if ((*root)->key > value)
		insert(&(*root)->left, value);
	//(*root)->height = 1 + std::max(get_height((*root)->right),
	// get_height((*root)->left));
	return false;
}

/*unsigned int get_height(node* root){
if (!root) return 0;
return root->height;
  }*/

unsigned int size(subset_node *root)
{
	if (!root)
		return 0;
	return size(root->left) + size(root->right) + 1;
}

unsigned int height(subset_node *root)
{
	if (!root)
		return 0;
	return std::max(height(root->left), height(root->right)) + 1;
}

subset_node *find(subset_node *root, int k)
{
	if (root == NULL)
		return NULL;
	if (root->key < k)
		return find(root->right, k);
	else if (root->key > k)
		return find(root->left, k);
	return root;
}

subset_node *find_the_left(subset_node *root)
{
	if (root->left == NULL)
		return root;
	else
		return find_the_left(root->left);
}

bool remove(subset_node **root, int k)
{
	auto nash_slon = find(*root, k);
	if (!nash_slon)
		return false;
	if ((*root)->key < k)
		remove(&((*root)->right), k);
	else if ((*root)->key > k)
		remove(&((*root)->left), k);
	else if ((*root)->key == k) {
		if ((*root)->left == NULL && (*root)->right == NULL) {
			auto h = *root;
			*root = NULL;
			delete h;
		}
		else if (((*root)->left == NULL && (*root)->right != NULL) ||
		         ((*root)->left != NULL && (*root)->right == NULL)) {
			if ((*root)->left != NULL) {
				auto h = *root;
				*root = (*root)->left;
				delete h;
			}
			else {
				auto h = *root;
				*root = (*root)->right;
				delete h;
			}
		}
		else {
			subset_node *h = (*root)->right;
			h = find_the_left(h);
			auto storage = h->key;
			remove(root, h->key);
			(*root)->key = storage;
		}
	}
	return true;
}

/*void print(node* root){
if (!root) return;
print(root->left);
std::cout << root->value << std::endl;
print(root->right);
  }*/ //это у нас сортировка от меньшего к большему, если ты забыла

void DFS_fill(subset_node *root, int *a, int &index)
{
	if (!root)
		return;
	DFS_fill(root->left, a, index);
	a[index++] = root->key;
	DFS_fill(root->right, a, index);
}

int *DFS(subset_node *root)
{
	if (!root)
		return NULL;
	int *ans = new int[size(root)];
	int index = 0;
	DFS_fill(root, ans, index);
	return ans;
}

#include <random>
#include <chrono>
#include <climits>
using std::cout;
using std::endl;
double get_time()
{
	return std::chrono::duration_cast<std::chrono::microseconds>(
	         std::chrono::steady_clock::now().time_since_epoch())
	         .count() /
	       1e6;
}
int rand_uns(int min, int max)
{
	unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
	static std::default_random_engine e(seed);
	std::uniform_int_distribution<int> d(min, max);
	return d(e);
}
int main()
{
	unsigned int n = 10000;
	int *sequent_sequence = new int[n], *rand_sequence_10 = new int[n],
	    *rand_sequence_100 = new int[n], *rand_sequence_n = new int[n],
	    *rand_sequence_unique = new int[n], *sorted_sequence_unique = new int[n];
	double start = 0, finish = 0, total = 0;
	cout << std::fixed;
	cout.precision(4);
	//----------- Initialization
	start = get_time();
	for (unsigned int i = 0; i < n; i++) {
		sequent_sequence[i] = i;
		rand_sequence_10[i] = rand_uns(0, 10);
		rand_sequence_100[i] = rand_uns(0, 100);
		rand_sequence_n[i] = rand_uns(0, n);
	}
	for (unsigned int i = 0; i < n; i++) {
		rand_sequence_unique[i] = rand_uns(0, INT_MAX);
		for (unsigned int j = 0; j < i; j++)
			if (rand_sequence_unique[i] == rand_sequence_unique[j]) {
				i--;
				break;
			}
	}
	for (unsigned int i = 0; i < n; i++)
		sorted_sequence_unique[i] = rand_sequence_unique[i];
	for (unsigned int i = 0; i < n; i++)
		for (unsigned int j = 0; j < n - i - 1; j++)
			if (sorted_sequence_unique[j] > sorted_sequence_unique[j + 1]) {
				int tmp = sorted_sequence_unique[j];
				sorted_sequence_unique[j] = sorted_sequence_unique[j + 1];
				sorted_sequence_unique[j + 1] = tmp;
			}

	finish = get_time();
	cout << "Test sequence initialization: \t\t\t\t" << finish - start << endl;
	subset_node *sn;
	init(&sn);
	//----------- Test 000 Insert of a sequent sequence
	start = get_time();
	for (unsigned int i = 0; i < n; i++) {
		insert(&sn, sequent_sequence[i]);
	}
	finish = get_time();
	if (size(sn) != n) {
		cout << endl
		     << "--- !!! Failed insert consistency or size measurement, wrong "
		        "number of elements !!! ---"
		     << endl;
		return 0;
	}
	if (height(sn) != n) {
		cout << endl
		     << "--- !!! Failed insert consistency or height measurement, wrong "
		        "height !!! ---"
		     << endl;
		return 0;
	}
	cout << "000 Insert of a sequent sequence: \t\t\t\t" << finish - start
	     << endl;
	total += finish - start;
	//----------- Test 001 Finding of a sequent sequence
	start = get_time();
	for (unsigned int i = 0; i < n; i++) {
		if (!find(sn, sequent_sequence[i])) {
			cout << endl
			     << "--- !!! Failed insert consistency or find, an element was not "
			        "found !!! ---"
			     << endl;
			return 0;
		}
	}
	if (find(sn, n + 1)) {
		cout << endl
		     << "--- !!! Failed find, an extra element was found !!! ---" << endl;
		return 0;
	}
	if (find(sn, -1)) {
		cout << endl
		     << "--- !!! Failed find, an extra element was found !!! ---" << endl;
		return 0;
	}
	finish = get_time();
	cout << "001 Finding of a sequent sequence: \t\t\t\t" << finish - start
	     << endl;
	total += finish - start;
	//----------- Test 002 Remove of a sequent sequence
	start = get_time();
	for (unsigned int i = 0; i < n; i++) {
		remove(&sn, sequent_sequence[i]);
	}
	finish = get_time();
	if (size(sn) != 0) {
		cout << endl
		     << "--- !!! Failed insert consistency or size measurement, elements "
		        "stuck !!! ---"
		     << endl;
		return 0;
	}
	if (height(sn) != 0) {
		cout << endl
		     << "--- !!! Failed insert consistency or height measurement, too high "
		        "for an empty tree !!! ---"
		     << endl;
		return 0;
	}
	cout << "002 Remove of a sequent sequence: \t\t\t\t" << finish - start
	     << endl;
	total += finish - start;
	//----------- Test 003 Insert of a random sequence (0 - 10)
	start = get_time();
	for (unsigned int i = 0; i < n; i++) {
		insert(&sn, rand_sequence_10[i]);
	}
	finish = get_time();
	auto content = DFS(sn);
	auto size_content = size(sn);
	for (unsigned int i = 0; i < size_content - 1; i++)
		if (content[i] >= content[i + 1]) {
			cout << endl
			     << "--- !!! Failed content order, the left is larger than the right "
			        "!!! ---"
			     << endl;
			return 0;
		}
	delete[] content;
	cout << "003 Insert of a random sequence (0 - 10): \t\t\t\t" << finish - start
	     << endl;
	total += finish - start;
	//----------- Test 004 Finding of a random sequence (0 - 10)
	start = get_time();
	for (unsigned int i = 0; i < n; i++) {
		if (!find(sn, rand_sequence_10[i])) {
			cout << endl
			     << "--- !!! Failed insert consistency or find, an element was not "
			        "found !!! ---"
			     << endl;
			return 0;
		}
	}
	if (find(sn, n + 1)) {
		cout << endl
		     << "--- !!! Failed find, an extra element was found !!! ---" << endl;
		return 0;
	}
	if (find(sn, -1)) {
		cout << endl
		     << "--- !!! Failed find, an extra element was found !!! ---" << endl;
		return 0;
	}
	finish = get_time();
	cout << "004 Finding of a random sequence (0 - 10): \t\t\t\t"
	     << finish - start << endl;
	total += finish - start;
	//----------- Test 005 Remove of a random sequence (0 - 10)
	start = get_time();
	for (unsigned int i = 0; i < n; i++) {
		remove(&sn, rand_sequence_10[i]);
	}
	finish = get_time();
	if (size(sn) != 0) {
		cout << endl
		     << "--- !!! Failed insert consistency or size measurement, elements "
		        "stuck !!! ---"
		     << endl;
		return 0;
	}
	if (height(sn) != 0) {
		cout << endl
		     << "--- !!! Failed insert consistency or height measurement, too high "
		        "for an empty tree !!! ---"
		     << endl;
		return 0;
	}
	cout << "005 Remove of a random sequence (0 - 10): \t\t\t\t" << finish - start
	     << endl;
	total += finish - start;
	//----------- Test 006 Insert of a random sequence (0 - 100)
	start = get_time();
	for (unsigned int i = 0; i < n; i++) {
		insert(&sn, rand_sequence_100[i]);
	}
	finish = get_time();
	content = DFS(sn);
	size_content = size(sn);
	for (unsigned int i = 0; i < size_content - 1; i++)
		if (content[i] >= content[i + 1]) {
			cout << endl
			     << "--- !!! Failed content order, the left is larger than the right "
			        "!!! ---"
			     << endl;
			return 0;
		}
	delete[] content;
	cout << "006 Insert of a random sequence (0 - 100): \t\t\t\t"
	     << finish - start << endl;
	total += finish - start;
	//----------- Test 007 Finding of a random sequence (0 - 100)
	start = get_time();
	for (unsigned int i = 0; i < n; i++) {
		if (!find(sn, rand_sequence_100[i])) {
			cout << endl
			     << "--- !!! Failed insert consistency or find, an element was not "
			        "found !!! ---"
			     << endl;
			return 0;
		}
	}
	if (find(sn, n + 1)) {
		cout << endl
		     << "--- !!! Failed find, an extra element was found !!! ---" << endl;
		return 0;
	}
	if (find(sn, -1)) {
		cout << endl
		     << "--- !!! Failed find, an extra element was found !!! ---" << endl;
		return 0;
	}
	finish = get_time();
	cout << "007 Finding of a random sequence (0 - 100): \t\t\t\t"
	     << finish - start << endl;
	total += finish - start;
	//----------- Test 008 Remove of a random sequence (0 - 100)
	start = get_time();
	for (unsigned int i = 0; i < n; i++) {
		remove(&sn, rand_sequence_100[i]);
	}
	finish = get_time();
	if (size(sn) != 0) {
		cout << endl
		     << "--- !!! Failed insert consistency or size measurement, elements "
		        "stuck !!! ---"
		     << endl;
		return 0;
	}
	if (height(sn) != 0) {
		cout << endl
		     << "--- !!! Failed insert consistency or height measurement, too high "
		        "for an empty tree !!! ---"
		     << endl;
		return 0;
	}
	cout << "008 Remove of a random sequence (0 - 100): \t\t\t\t"
	     << finish - start << endl;
	total += finish - start;
	//----------- Test 009 Insert of a random sequence (0 - n)
	start = get_time();
	for (unsigned int i = 0; i < n; i++) {
		insert(&sn, rand_sequence_n[i]);
	}
	finish = get_time();
	cout << "009 Insert of a random sequence (0 - n): \t\t\t\t" << finish - start
	     << endl;
	total += finish - start;
	//----------- Test 010 Finding of a random sequence (0 - n)
	start = get_time();
	for (unsigned int i = 0; i < n; i++) {
		if (!find(sn, rand_sequence_n[i])) {
			cout << endl
			     << "--- !!! Failed insert consistency or find, an element was not "
			        "found !!! ---"
			     << endl;
			return 0;
		}
	}
	if (find(sn, n + 1)) {
		cout << endl
		     << "--- !!! Failed find, an extra element was found !!! ---" << endl;
		return 0;
	}
	if (find(sn, -1)) {
		cout << endl
		     << "--- !!! Failed find, an extra element was found !!! ---" << endl;
		return 0;
	}
	finish = get_time();
	cout << "010 Finding of a random sequence (0 - n): \t\t\t\t" << finish - start
	     << endl;
	total += finish - start;
	//----------- Test 011 Remove of a random sequence (0 - n)
	start = get_time();
	for (unsigned int i = 0; i < n; i++) {
		remove(&sn, rand_sequence_n[i]);
	}
	finish = get_time();
	if (size(sn) != 0) {
		cout << endl
		     << "--- !!! Failed insert consistency or size measurement, elements "
		        "stuck !!! ---"
		     << endl;
		return 0;
	}
	if (height(sn) != 0) {
		cout << endl
		     << "--- !!! Failed insert consistency or height measurement, too high "
		        "for an empty tree !!! ---"
		     << endl;
		return 0;
	}
	cout << "011 Remove of a random sequence (0 - n): \t\t\t\t" << finish - start
	     << endl;
	total += finish - start;
	//----------- Test 012 Insert of an unique sequence (0 - n)
	start = get_time();
	for (unsigned int i = 0; i < n; i++) {
		insert(&sn, rand_sequence_unique[i]);
	}
	finish = get_time();
	cout << "012 Insert of an unique sequence (0 - n): \t\t\t\t" << finish - start
	     << endl;
	total += finish - start;
	//----------- Test 013 Finding of an unique sequence (0 - n)
	start = get_time();
	for (unsigned int i = 0; i < n; i++) {
		if (!find(sn, rand_sequence_unique[i])) {
			cout << endl
			     << "--- !!! Failed insert consistency or find, an element was not "
			        "found !!! ---"
			     << endl;
			return 0;
		}
	}
	if (find(sn, n + 1)) {
		cout << endl
		     << "--- !!! Failed find, an extra element was found !!! ---" << endl;
		return 0;
	}
	if (find(sn, -1)) {
		cout << endl
		     << "--- !!! Failed find, an extra element was found !!! ---" << endl;
		return 0;
	}
	finish = get_time();
	cout << "013 Finding of an unique sequence (0 - n): \t\t\t\t"
	     << finish - start << endl;
	total += finish - start;
	//----------- Test 014 Checking the searchiness of the tree
	content = DFS(sn);
	size_content = size(sn);
	if (size_content != n) {
		cout << endl
		     << "--- !!! Failed insert consistency or size measurement, wrong "
		        "number of elements !!! ---"
		     << endl;
		return 0;
	}
	for (unsigned int i = 0; i < size_content; i++) {
		if (content[i] != sorted_sequence_unique[i]) {
			cout << endl
			     << "--- !!! Failed order, DFS is supposed to sort the data !!! ---"
			     << endl;
			return 0;
		}
	}
	delete[] content;
	cout << "014 Checking the searchiness of the tree: \t\t\t\t" << finish - start
	     << endl;
	total += finish - start;
	//----------- Test 015 Remove of an unique sequence (0 - n)
	start = get_time();
	for (unsigned int i = 0; i < n; i++) {
		remove(&sn, sorted_sequence_unique[i]);
	}
	finish = get_time();
	if (size(sn) != 0) {
		cout << endl
		     << "--- !!! Failed insert consistency or size measurement, elements "
		        "stuck !!! ---"
		     << endl;
		return 0;
	}
	if (height(sn) != 0) {
		cout << endl
		     << "--- !!! Failed insert consistency or height measurement, too high "
		        "for an empty tree !!! ---"
		     << endl;
		return 0;
	}
	cout << "015 Remove of a random sequence (0 - n): \t\t\t\t" << finish - start
	     << endl;
	total += finish - start;

	//----------- End of tests
	//
	cout << "-----------" << endl
	     << "Alltests finished, total time: \t" << total << endl;

	delete[] sequent_sequence;
	delete[] rand_sequence_10;
	delete[] rand_sequence_100;
	delete[] rand_sequence_n;
	delete[] rand_sequence_unique;
	delete[] sorted_sequence_unique;
	return 0;
}
