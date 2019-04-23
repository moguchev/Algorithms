/*Задача 1. Хеш-таблица
Реализуйте структуру данных типа “множество строк” на основе динамической хеш-таблицы с открытой адресацией. Хранимые строки непустые и состоят из строчных латинских букв. Начальный размер таблицы должен быть равным 8-ми. Перехеширование выполняйте при добавлении элементов в случае, когда коэффициент заполнения таблицы достигает 3/4.
Хеш-функцию строки реализуйте с помощью вычисления значения многочлена методом Горнера.
Структура данных должна поддерживать операции добавления строки в множество, удаления строки из множества и проверки принадлежности данной строки множеству.
1_2. Для разрешения коллизий используйте двойное хеширование.
Формат входных данных
Каждая строка входных данных задает одну операцию над множеством. Запись операции состоит из типа операции и следующей за ним через пробел строки, над которой проводится операция.
Тип операции  – один из трех символов:
    +  означает добавление данной строки в множество;
    -  означает удаление  строки из множества;
    ?  означает проверку принадлежности данной строки множеству.
При добавлении элемента в множество НЕ ГАРАНТИРУЕТСЯ, что он отсутствует в этом множестве. При удалении элемента из множества НЕ ГАРАНТИРУЕТСЯ, что он присутствует в этом множестве.
Формат выходных данных
Программа должна вывести для каждой операции одну из двух строк OK или FAIL, в зависимости от того, встречается ли данное слово в нашем множестве.
*/
#include <iostream>
#include <string>
#include <vector>


template<class T = std::string>
int Hash1(const T& key, int m) {
    int hash = 0;
    int a = 11;
    for (size_t i = 0; i < key.size(); i++) {
        hash = (hash * a + key[i]) % m;
    }
    return hash;
}

template<class T = std::string>
int Hash2(const T& key, int m) {
    int hash = 0;
    int a = 17;
    for (size_t i = 0; i < key.size(); i++) {
        hash = (hash * a + key[i]) % m;
    }
    hash = (2 * hash + 1) % m;
    return hash;
}

int HashFunction(int h1, int h2, int i, int m) {
    if (m != 0) {
        return(h1 + i * h2) % m;
    }
    else {
        return 0;
    }
}

template <class T>
class HashTable {
public:
    HashTable() : table(DEFAULT_SIZE, nullptr), _size(0) {}
    ~HashTable();
    bool Insert(const T& key);
    bool Remove(const T& key);
    bool Has(const T& key) const;
    void ReHash();
private:
    const double REHASH_COEF = 0.75;
    const size_t DEFAULT_SIZE = 8;

    struct HashTableNode {
        HashTableNode(const T&_key) : key(_key), is_optional(false) {}
        T key;
        bool is_optional;
    };

    std::vector<HashTableNode*> table;
    size_t _size;
};

int main()
{
    HashTable<std::string> table;
    while (!std::cin.fail()) {
        char command = 0;
        std::string value;
        std::cin >> command >> value;
        switch (command)
        {
        case '?':
            std::cout << (table.Has(value) ? "OK" : "FAIL") << std::endl;
            break;
        case '+':
            std::cout << (table.Insert(value) ? "OK" : "FAIL") << std::endl;
            break;
        case '-':
            std::cout << (table.Remove(value) ? "OK" : "FAIL") << std::endl;
            break;
        }
    }
    return 0;
}

template <class T>
HashTable<T>::~HashTable() {
    for (auto e : table)
        if (e != nullptr)
            delete e;
}

template <class T>
bool HashTable<T>::Insert(const T& key) {
    if (static_cast<double>(_size) / static_cast<double>(table.size()) >= REHASH_COEF) {
        ReHash();
    }

    int h1 = Hash1<T>(key, table.size());
    int h2 = Hash2<T>(key, table.size());
    int h = HashFunction(h1, h2, 0, table.size());

    for (int i = 0; i < table.size() && table[h] != nullptr; i++) {
        if (table[h]->key == key && table[h]->is_optional == false) {
            return false;
        }
        if (table[h]->is_optional == true) {
            table[h]->key = key;
            table[h]->is_optional = false;
            _size++;
            return true;
        }
        h = HashFunction(h1, h2, i + 1, table.size());
    }

    table[h] = new HashTableNode(key);
    _size++;
    return true;
}

template <class T>
bool HashTable<T>::Remove(const T& key) {
    int h1 = Hash1<T>(key, table.size());
    int h2 = Hash2<T>(key, table.size());
    int j = HashFunction(h1, h2, 0, table.size());
    for (int i = 0; i < table.size(); i++) {
        if (table[j] != nullptr) {
            if (table[j]->key == key && table[j]->is_optional == false) {
                table[j]->is_optional = true;
                _size--;
                return true;
            }
        }
        else {
            return false;
        }
        j = HashFunction(h1, h2, i + 1, table.size());
    }
    return false;
}

template <class T>
bool HashTable<T>::Has(const T& key) const {
    int h1 = Hash1<T>(key, table.size());
    int h2 = Hash2<T>(key, table.size());
    int h = h1;

    int i = 0;
    while (table[h] != nullptr && i < table.size()) {
        if (table[h]->key == key && table[h]->is_optional == false) {
            return true;
        }
        h = HashFunction(h1, h2, i + 1, table.size());
        i++;
    }
    return false;
}

template <class T>
void HashTable<T>::ReHash() {
    int new_size = table.size() * 2;
    std::vector<HashTableNode*> new_table(new_size, nullptr);

    for (int i = 0; i < table.size(); i++) {
        if (table[i] != nullptr && table[i]->is_optional == false) {
            int j = 0;
            int h1 = Hash1<T>(table[i]->key, new_size);
            int h2 = Hash2<T>(table[i]->key, new_size);
            int h = HashFunction(h1, h2, j, new_size);

            while (j < new_size) {
                if (new_table[h] == nullptr) {
                    break;
                }
                j++;
                h = HashFunction(h1, h2, j, new_size);
            }
            new_table[h] = table[i];
        }
    }
    table = new_table;
}
