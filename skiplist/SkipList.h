#pragma once
#include <vector>
#include <utility>
#include <random>
#include <type_traits>
#include <stdexcept>

template <typename Key,	typename Value, 	typename Compare = std::less<Key>,
	typename Alloc = std::allocator<std::pair<const Key, Value> > >
	class skip_list final{	
	public:
		typedef std::pair<const Key, Value> value_type;
		struct Node {		
		private:
			value_type data;			
		public:
			std::vector<Node*> forward;
			size_t lvl;
			Node(size_t _lvl) : lvl(_lvl) {	forward = { _lvl, {} }; }
			Node(size_t _lvl, value_type _data) : lvl(_lvl), data(_data) { forward = { _lvl, {} }; }
			value_type& get_data() { return this->data; }
			void set_data(const Value& new_val){ data.second = new_val; }
		};
	private:
		const size_t MAX_LVL = 3;
		Node* head;
		Node* NIL;
		const Compare &comp = Compare{};
		const Alloc &alloc = Alloc{};
	public:
		skip_list();
		skip_list(const skip_list &another) = default;
		explicit skip_list(const Compare &comp, const Alloc &a = Alloc());
		~skip_list();

		skip_list &operator=(const skip_list &another);
			
		template <typename T>
		class Iterator final{
			typename std::conditional_t<std::is_const<value_type>::value, const skip_list&, skip_list&> parent;
			Node* curr;
		public:
			using iterator_category = std::forward_iterator_tag;
			using  value_type = std::pair<const Key, Value>;
			using pointer = T*;
			using reference = T&;
			using const_reference = const T&;
		public:
			Iterator(typename std::conditional_t<std::is_const<value_type>::value, const skip_list&, skip_list&> parent,
				Node* curr) : parent(parent), curr(curr) {}
			Iterator(const Iterator &another) = default;
			Iterator& operator++();
			Iterator operator++(int);
			bool operator ==(const Iterator& it) const { return curr == it.curr && &parent == &it.parent; }
			bool operator !=(const Iterator& it) const { return !(*this == it); }
			reference operator*() {	return curr->get_data(); }
			const_reference operator*() const { return curr->get_data(); }
		};

		using iterator = Iterator<std::pair<const Key, Value>>;
		using const_iterator = Iterator<const std::pair<const Key, Value>>;

		iterator begin();
		const_iterator cbegin() const;
		iterator end();
		const_iterator cend() const;

		bool empty() const;
		size_t size() const; 
		Value &operator[](const Key &key);
		Value &at(const Key &key);
		const Value &at(const Key &key) const;
		size_t erase(const Key &key);
		void erase(iterator position);
		void erase(iterator first, iterator last);
		void swap(skip_list &another);
		void clear();
		iterator find(const Key &key);
		const_iterator find(const Key &key) const;

		size_t get_max_lvl() const { return MAX_LVL; }
		size_t random_level();
		std::pair<iterator, bool> insert(const value_type &_data);
	private:
		void find_data(const Key &key, Node** x, int i);
		std::pair<iterator, bool> insert_node(const value_type &_data, std::vector<Node*>);
		void erase_node(Node** x, std::vector<Node*>);
	
};

template <typename K, typename V, typename C, typename A>
bool operator==(const skip_list<K, V, C, A> &x, const skip_list<K, V, C, A> &y) {
	if (x.size() != y.size())
		return false;
	auto y_iter = y.begin();
	for(auto x_iter = x.begin(); x_iter != x.end(); ++x_iter){
		if(((*x_iter).first!=(*y_iter).first)||((*x_iter).second!=(*y_iter).second))
			return false;
		++y_iter;
	}
	return true;
}
template <typename K, typename V, typename C, typename A>
bool operator!=(const skip_list<K, V, C, A> &x, const skip_list<K, V, C, A> &y) {
	return !(x == y);
}


template <typename K, typename V, typename C, typename A>
skip_list<K, V, C, A>::skip_list() {
	value_type data(0,0);
	head = new Node(MAX_LVL, {});
	NIL = new Node(MAX_LVL, {});
	for (size_t i = 0; i != MAX_LVL; i++) {
		head->forward[i] = NIL;
	}
}
template <typename Key, typename Value, typename Compare, typename Alloc>
skip_list<Key, Value, Compare, Alloc>::skip_list(const Compare& comp, const Alloc& a) : comp(comp), alloc(a) {
	head = new Node(MAX_LVL, {});
	NIL = new Node(MAX_LVL, {});
	for (int i = 0; i != MAX_LVL; i++) {
		head->forward[i] = NIL;
	}
}
template <typename K, typename V, typename C, typename A>                        
skip_list<K, V, C, A>::~skip_list() {
	auto p = head;
	while (p->forward[0] != NULL) {
		auto tmp = p->forward[0];
		delete (p);
		p = tmp;
	}
	delete (p);
}

template <typename K, typename V, typename C, typename A>
skip_list<K, V, C, A>& skip_list<K, V, C, A>::operator=(const skip_list &another) {
	if (this == &another)
		return *this;
	MAX_LVL = another.MAX_LVL;
	head = another.head;
	NIL = another.NIL;
	return  *this;
}

template <typename K, typename V, typename C, typename A>
std::pair<typename skip_list<K, V, C, A>::iterator, bool> skip_list<K, V, C, A>::insert(const value_type &_data) {
	std::vector<Node*> update(MAX_LVL, head);
	if(empty())
		return insert_node(_data, update);
	Node* x = head;
	for (int i = MAX_LVL - 1; i >= 0; i--) {
		find_data(_data.first, &x, i);
		update[i] = x;
	}
	value_type data = x->get_data();
	if(x==head)
		return insert_node(_data, update);
	if (data.first == _data.first) {
		x->set_data(_data.second);
		return std::pair<iterator, bool>(iterator (*this, x), true);
	}
	return insert_node(_data, update);
}
template <typename K, typename V, typename C, typename A>          
size_t skip_list<K, V, C, A>::random_level() {
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist(1, MAX_LVL);
	return  dist(rng);
}
template <typename K, typename V, typename C, typename A>
std::pair<typename skip_list<K, V, C, A>::iterator, bool> skip_list<K, V, C, A>::insert_node
														(const value_type &_data, std::vector<Node*> update) {
	size_t lvl = random_level();
	Node* curr = new Node(lvl, _data);
	for (auto i = 0; i != lvl; i++) {
		curr->forward[i] = update[i]->forward[i];
		update[i]->forward[i] = curr;
	}	
	return std::pair<iterator, bool>(iterator(*this, curr), true);
}

template <typename K, typename V, typename C, typename A>
bool skip_list<K, V, C, A>::empty() const {
	if (head->forward[0] == NIL)
		return true;
	return false;
}
template <typename K, typename V, typename C, typename A>
size_t skip_list<K, V, C, A>::size() const {
	auto curr_node = head;
	size_t size = 0;
	while (curr_node->forward[0] != NIL){
		size++;
		curr_node = curr_node->forward[0];
	}		
	return size;
}

template <typename Key, typename Value, typename C, typename A>
Value &skip_list<Key, Value, C, A>::operator[](const Key &key) {
	Node* x = head;
	for (int i = MAX_LVL - 1; i >= 0; i--) {
		find_data(key, &x, i);
	}
	if (x->get_data().first == key)
		return x->get_data().second;
	auto it = insert(std::pair<Key, Value>(key, {}));
	return (*it.first).second;
}
template <typename Key, typename Value, typename C, typename A>
Value& skip_list<Key, Value, C, A>::at(const Key &key) {
	Node* x = head;
	for (int i = MAX_LVL - 1; i >= 0; i--) {
		find_data(key, &x, i);
	}
	if (x->get_data().first == key)
		return x->get_data().second;
	throw std::out_of_range("skip_list<K, V, C, A>::at, no values with this key");
}
template <typename Key, typename Value, typename C, typename A>
const Value &skip_list<Key, Value, C, A>::at(const Key &key) const{
	Node* x = head;
	for (int i = MAX_LVL - 1; i >= 0; i--) {
		find_data(key, &x, i);
	}
	value_type data = x->get_data();
	if (data.first == key)
		return data.second;
	throw std::out_of_range("skip_list<K, V, C, A>::at, invalid key");
}

template <typename Key, typename V, typename C, typename A>
void skip_list<Key, V, C, A>::erase_node(Node** x, std::vector<Node*> update){
	for (auto i = 0; i != (*x)->lvl; i++) {
		update[i]->forward[i] = (*x)->forward[i];
	}
	delete(*x);
}
template <typename Key, typename V, typename C, typename A>
size_t skip_list<Key, V, C, A>::erase(const Key &key) {
	std::vector<Node*> update(MAX_LVL, {});
	Node* curr_node = head;
	for (int i = MAX_LVL - 1; i >= 0; i--) {
		std::pair<Key, V> data = curr_node->forward[i]->get_data();
		while (comp(data.first, key)) {
			if (curr_node->forward[i] == NIL)
				break;
			curr_node = curr_node->forward[i];			
			data = curr_node->forward[i]->get_data();
		}
		update[i] = curr_node;
	}
	Node* x = curr_node->forward[0];
	value_type data = x->get_data();
	if (data.first == key) {
		erase_node(&x, update);
		return 1;    
	}
	return 0;
}
template <typename Key, typename V, typename C, typename A>
void skip_list<Key, V, C, A>::erase(iterator position) {
	erase((*position).first);
}
template <typename Key, typename V, typename C, typename A>
void skip_list<Key, V, C, A>::erase(iterator first, iterator last) {
	++last;
	auto it = first;
	while(it!=last){
		auto tmp = it;
		++it;
		erase((*tmp).first);
	}	
}


template <typename Key, typename V, typename C, typename A>
typename skip_list<Key, V, C, A>::iterator skip_list<Key, V, C, A>::find(const Key &key) {
	Node* x = head;
	for (int i = MAX_LVL - 1; i >= 0; i--) {
		find_data(key, &x, i);
	}
	value_type data = x->get_data();
	if((x==head)||(x==NIL))
		return end();
	if (data.first == key)
		return iterator(*this, x);
	return end();
}
template <typename Key, typename V, typename C, typename A>
void skip_list<Key, V, C, A>::find_data(const Key &key, Node** x, int i) {
	if ((*x)->forward[i] == NIL)
		return;
	std::pair<Key, V> data = (*x)->forward[i]->get_data();
	while(comp(data.first, key)){
		*x = (*x)->forward[i];
		if (*x == NIL)
			return;
		if ((*x)->forward[i] == NIL)
			return;
		data = (*x)->forward[i]->get_data();
	}
	if (!comp(key, data.first)){
		*x = (*x)->forward[0];
	}
}
template <typename Key, typename V, typename C, typename A>
typename skip_list<Key, V, C, A>::const_iterator skip_list<Key, V, C, A>::find(const Key &key) const{
	Node* x = head;
	for (int i = MAX_LVL - 1; i >= 0; i--) {
		find_data(key, &x, i);
	}
	if ((x == head) || (x == NIL))
		return end();
	value_type data = x->get_data();	
	if (data.first == key)
		return const_iterator(*this, x);
	return cend();
}

template <typename Key, typename V, typename C, typename A>
void skip_list<Key, V, C, A>::swap(skip_list &another){
	std::swap(head, another.head);
	std::swap(NIL, another.NIL);
	//std::swap(MAX_LVL, another.MAX_LVL);
	//std::swap(*this, another);
}

template <typename Key, typename V, typename C, typename A>
void skip_list<Key, V, C, A>::clear(){
	Node* x = head->forward[0];
	while(x != NIL) {
		Node* tmp = x->forward[0];
		delete(x);
		x = tmp;
	}
	for (int i = MAX_LVL - 1; i >= 0; i--) {
		head->forward[i] = NIL;
	}
}

template <typename K, typename V, typename C, typename A>
typename skip_list<K, V, C, A>::iterator skip_list<K, V, C, A>::begin() {
	iterator it(*this, head->forward[0]);
	return it;
}
template <typename Key, typename V, typename C, typename A>
typename skip_list<Key, V, C, A>::const_iterator skip_list<Key, V, C, A>::cbegin() const {
	const_iterator it(*this, head->forward[0]);
	return it;
}
template <typename K, typename V, typename C, typename A>
typename skip_list<K, V, C, A>::iterator skip_list<K, V, C, A>::end() {
	iterator it(*this, NIL);
	return it;
}
template <typename K, typename V, typename C, typename A>
typename skip_list<K, V, C, A>::const_iterator skip_list<K, V, C, A>::cend() const {
	const_iterator it(*this, NIL);
	return it;
}

template<typename Key, typename Value, typename Compare, typename Alloc>
template<typename T>
skip_list<Key, Value, Compare, Alloc>::Iterator<T>& skip_list<Key, Value, Compare, Alloc>::Iterator<T>::operator++() {
	curr = curr->forward[0];
	return *this;
}
template <typename Key, typename Value, typename Compare, typename Alloc>
template<typename T>
skip_list<Key, Value, Compare, Alloc>::Iterator<T> skip_list<Key, Value, Compare, Alloc>::Iterator<T>::operator++(int) {
	iterator tmp = *this;
	operator++();
	return tmp;
}