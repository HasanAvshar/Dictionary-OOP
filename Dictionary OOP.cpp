#include<iostream>
#include<cassert>
using namespace std;

template <typename PairTKey, typename PairTValue>
class KeyValuePair {
public:
	PairTKey key;
	PairTValue value;
	KeyValuePair() :key(), value() {}
	KeyValuePair(const PairTKey key, const PairTValue value)
		:key(key), value(value) {}
	PairTValue& operator[](PairTKey key) { return value; }
};

template <typename TKey, typename TValue>
class Dictionary {
public:
	Dictionary() {
		_pairs = new KeyValuePair<TKey, TValue>[_capacity];
	}

	TValue& operator[](const TKey key) {
		for (size_t i = 0; i < _count; i++) {
			if (_pairs[i].key == key) return _pairs[i].value;
		}

		KeyValuePair<TKey, TValue> newItem(key, TValue());
		Add(newItem);
		return newItem.value;
	}

	void Add(KeyValuePair<TKey, TValue>& item) {
		if (ContainsKey(item.key))
			assert(!"Bu key movcuddur");

		if (_count == _capacity) {
			Resize();
		}

		_pairs[_count] = item;
		_count++;
	}

	void Add(TKey key, TValue value) {
		KeyValuePair<TKey, TValue> newItem(key, value);
		Add(newItem);
	}

	bool ContainsKey(const TKey key) const {
		for (size_t i = 0; i < _count; i++)
			if (_pairs[i].key == key)
				return true;
		return false;
	}

	size_t count() const {
		return _count;
	}

	size_t capacity() const {
		return _capacity;
	}

	TKey* keys() {
		TKey* newArray = new TKey[_count];
		for (size_t i = 0; i < _count; i++)
			newArray[i] = _pairs[i].key;
		return newArray;
	}

	TValue* values() {
		TValue* newArray = new TValue[_count];
		for (size_t i = 0; i < _count; i++)
			newArray[i] = _pairs[i].value;
		return newArray;
	}

	KeyValuePair<TKey, TValue>* items() {
		return _pairs;
	}

	void clear() {
		delete[] _pairs;
		_pairs = nullptr;
		_count = 0;
		_capacity = 5;
	}

	bool remove(const TKey key)
	{
		if (!ContainsKey(key))
			return false;

		KeyValuePair<TKey, TValue>* newArray = new KeyValuePair<TKey, TValue>[_count - 1];

		int index = 0;
		for (size_t i = 0; i < _count; i++)
		{
			if (_pairs[i].key == key)
				continue;
			newArray[index++] = _pairs[i];
		}
		_count--;

		delete[] _pairs;
		_pairs = newArray;
		return true;
	}

	void Print() const
	{
		if (_count == 0) return;

		for (size_t i = 0; i < _count; i++)
			cout << _pairs[i].key << " : " << _pairs[i].value << endl;
	}


private:
	KeyValuePair<TKey, TValue>* _pairs = nullptr;
	size_t _count = 0;
	size_t _capacity = 5;

	void Resize() {
		_capacity *= 2;
		auto newArray = new KeyValuePair<TKey, TValue>[_capacity];
		for (size_t i = 0; i < _count; i++)
			newArray[i] = _pairs[i];
		delete[] _pairs;
		_pairs = newArray;
	}
};

int main() {
	Dictionary<int, string> dict;
	dict.Add(1, "Apple");
	dict[1] = "Apple";
	cout << dict[1] << endl;
	dict[1] = "Banana";
	cout << dict[1] << endl;
	dict.Print();
}