#ifndef PAIR_H_
#define PAIR_H_

template <class K, class T>
class Pair {
public:
    Pair() = default;
    Pair(const K& key, const T& value);
    Pair(const Pair &pair) = default;
    Pair &operator=(const Pair &pair) = default;

    const K& getKey() const;
    const T& getValue() const;
    void setKey(const K& key);
    void setValue(const T& value);

private:
    K m_key;
    T m_value;
    friend bool operator>(const Pair& pair1, const Pair& pair2);
    friend bool operator==(const Pair& pair1, const Pair& pair2);
};

template <class K, class T>
bool operator<(const Pair<K, T>& pair1, const Pair<K, T>& pair2);


template <class K, class T>
Pair<K, T>::Pair(const K& key, const T& value):
        m_key(key),
        m_value(value)
{}

template <class K, class T>
const K& Pair<K, T>::getKey() const {
    return m_key;
}

template<class K, class T>
const T& Pair<K, T>::getValue() const {
    return m_value;
}

template<class K, class T>
void Pair<K, T>::setKey(const K& key) {
    m_key = key;
}

template<class K, class T>
void Pair<K, T>::setValue(const T &value) {
    m_value = value;
}

template<class K, class T>
bool operator>(const Pair<K, T>& pair1, const Pair<K, T>& pair2) {
    if(pair1.m_key > pair2.m_key) {
        return true;
    }

    if(pair1.m_key == pair2.m_key) {
        return pair1.m_value > pair2.m_value;
    }

    return false;
}

template<class K, class T>
bool operator==(const Pair<K, T>& pair1, const Pair<K, T>& pair2) {
    return ((pair1.m_key == pair2.m_key) && (pair1.m_value == pair2.m_value));
}

template <class K, class T>
bool operator<(const Pair<K, T>& pair1, const Pair<K, T>& pair2) {
    return pair2 > pair1;
}
#endif // PAIR_H_

