#include "Queue.h"
#include <vector>



template <typename T>
T& Queue<T>::front() {
    if (isEmpty()) {
        throw std::out_of_range("Queue is empty.");
    }
    return data.front();
}

// template <typename T>
// const T& Queue<T>::front() const {
//     if (isEmpty()) {
//         throw std::out_of_range("Queue is empty.");
//     }
//     return data.front();
// }

template <typename T>
size_t Queue<T>::size() const {
    return data.size();
}

