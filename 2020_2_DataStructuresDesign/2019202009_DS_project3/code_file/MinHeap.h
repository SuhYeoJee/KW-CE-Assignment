#ifndef MIN_HEAP_H
#define MIN_HEAP_H

#include <utility>
#include <vector>
using namespace std;

template<typename TKey, typename TValue>
class MinHeap
{
private:
    // array for the elements which should be heap-sorted
    std::vector<std::pair<TKey, TValue>> m_vec;

public:
    MinHeap() {}

    /// <summary>
    /// insert key-value pair
    /// </summary>
    ///
    /// <param name="key">
    /// the key that is used for sorting
    /// </param>
    ///
    /// <param name="value">
    /// the value that is managed in this heap
    /// </param>
    void Push(TKey key, TValue value) {
        int i;
        if (m_vec.empty()) {
            m_vec.push_back(make_pair(0, NULL)); //[0] don't use
            m_vec.push_back(make_pair(key, value));
            return;
        }
        m_vec.push_back(make_pair(key, value)); //insert at last
        i = m_vec.size() - 1;
        while (i != 1) {
            if (m_vec[i / 2].first > key) m_vec[i] = m_vec[i / 2]; //bubling up
            else  break;
            i = i / 2;
        }
        m_vec[i] = make_pair(key, value); // insert sorted place
    }

    /// <summary>
    /// remove the minimum element
    /// </summary>
    void Pop() {
        m_vec[1] = m_vec.back(); //last element be a root
        m_vec.pop_back(); //delete 1 element
        Heapify(1); //sort
    }

    /// <summary>
    /// get the minimum element
    /// </summary>
    ///
    /// <returns>
    /// the minimum element
    /// </returns>
    std::pair<TKey, TValue> Top() {
        return m_vec[1];
    }

    /// <summary>
    /// get the key-value pair which the value is the same as the target
    /// </summary>
    ///
    /// <returns>
    /// the key-value pair which the value is the same as the target
    /// </returns>
    std::pair<TKey, TValue> Get(TValue target) {
        for (int i = 1; i < m_vec.size(); i++) {
            if (m_vec[i].second == target) return m_vec[i]; //target found
        }
        return m_vec[0]; //no such element
    }

    /// <summary>
    /// check whether this heap is empty or not
    /// </summary>
    ///
    /// <returns>
    /// true if this heap is empty
    /// </returns>
    bool IsEmpty() {
        return (m_vec.size() > 1) ? false : true;
    }

    /// <summary>
    /// change the key of the node which the value is the target.<para/>
    /// In general, the newKey should be smaller than the old key.<para/>
    /// </summary>
    ///
    /// <parma name="target">
    /// the target to change the key
    /// </param>
    ///
    /// <param name="newKey">
    /// new key for the target
    /// </param>
    void DecKey(TValue target, TKey newKey) {
        for (int i = 1; i < m_vec.size(); i++) {
            if (m_vec[i].second == target) { //target found
                m_vec[i].first = newKey;
                break;
            }
        }
    }

private:
    /// <summary>
    /// heap-sort, heapify.<para/>
    /// this function can be called recursively
    /// </summary>
    void Heapify(int index) {
        int child = index * 2;
        if (child > m_vec.size() - 1) return; //finish sort
        pair<TKey, TValue> temp = m_vec[index]; //element to sort
        if (child + 1 > m_vec.size() - 1); //no right child
        else if (m_vec[child].first < m_vec[child + 1].first) child++; //right child
        m_vec[index] = m_vec[child];  m_vec[child] = temp; //swap
        return Heapify(child);
    }
};

#endif

