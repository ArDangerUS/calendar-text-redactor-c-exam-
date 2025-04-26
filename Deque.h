#ifndef DEQUE_H
#define DEQUE_H

#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <set>
#include <memory>
#include <algorithm>
#include <iostream>
#include <functional>
#include <stdexcept>


template <typename T>
class Deque {
public:
    void pushFront(const T& value) { doPushFront(value); }
    void pushBack(const T& value) { doPushBack(value); }
    T popFront() { return doPopFront(); }
    T popBack() { return doPopBack(); }
    const T& front() const { return doFront(); }
    const T& back() const { return doBack(); }
    bool isEmpty() const { return doIsEmpty(); }
    size_t size() const { return doSize(); }
    void clear() { doClear(); }

    virtual ~Deque() = default;

protected:
    virtual void doPushFront(const T& value) = 0;
    virtual void doPushBack(const T& value) = 0;
    virtual T doPopFront() = 0;
    virtual T doPopBack() = 0;
    virtual const T& doFront() const = 0;
    virtual const T& doBack() const = 0;
    virtual bool doIsEmpty() const = 0;
    virtual size_t doSize() const = 0;
    virtual void doClear() = 0;
};


template <typename T>
class ArrayDeque : public Deque<T> {
private:
    static const size_t INITIAL_SIZE = 10;
    T* elements;
    size_t head;
    size_t tail;
    size_t elementCount;
    size_t arraySize;

    void expand();
    size_t nextPosition(size_t pos) const;
    size_t prevPosition(size_t pos) const;

protected:
    void doPushFront(const T& value) override;
    void doPushBack(const T& value) override;
    T doPopFront() override;
    T doPopBack() override;
    const T& doFront() const override;
    const T& doBack() const override;
    bool doIsEmpty() const override;
    size_t doSize() const override;
    void doClear() override;

public:
    ArrayDeque();
    ~ArrayDeque();
    ArrayDeque(const ArrayDeque& other);
    ArrayDeque& operator=(const ArrayDeque& other);
    ArrayDeque(ArrayDeque&& other) noexcept;
    ArrayDeque& operator=(ArrayDeque&& other) noexcept;
};


template <typename T>
class ListDeque : public Deque<T> {
private:
    struct Node {
        T element;
        Node* previous;
        Node* next;
        Node(const T& value) : element(value), previous(nullptr), next(nullptr) {}
    };

    Node* firstNode;
    Node* lastNode;
    size_t nodeCount;

protected:
    void doPushFront(const T& value) override;
    void doPushBack(const T& value) override;
    T doPopFront() override;
    T doPopBack() override;
    const T& doFront() const override;
    const T& doBack() const override;
    bool doIsEmpty() const override;
    size_t doSize() const override;
    void doClear() override;

public:
    ListDeque();
    ~ListDeque();
    ListDeque(const ListDeque& other);
    ListDeque& operator=(const ListDeque& other);
    ListDeque(ListDeque&& other) noexcept;
    ListDeque& operator=(ListDeque&& other) noexcept;
};


template <typename T, typename Implementation>
class DequeWithImpl {
private:
    Implementation impl;

public:
    void pushFront(const T& value) { impl.pushFront(value); }
    void pushBack(const T& value) { impl.pushBack(value); }
    T popFront() { return impl.popFront(); }
    T popBack() { return impl.popBack(); }
    const T& front() const { return impl.front(); }
    const T& back() const { return impl.back(); }
    bool isEmpty() const { return impl.isEmpty(); }
    size_t size() const { return impl.size(); }
    void clear() { impl.clear(); }
};


template <typename T>
class ArrayImpl {
private:
    static const size_t INITIAL_SIZE = 10;
    T* elements;
    size_t head;
    size_t tail;
    size_t elementCount;
    size_t arraySize;

    void expand();
    size_t nextPosition(size_t pos) const;
    size_t prevPosition(size_t pos) const;

public:
    ArrayImpl();
    ~ArrayImpl();
    ArrayImpl(const ArrayImpl& other);
    ArrayImpl& operator=(const ArrayImpl& other);
    ArrayImpl(ArrayImpl&& other) noexcept;
    ArrayImpl& operator=(ArrayImpl&& other) noexcept;

    void pushFront(const T& value);
    void pushBack(const T& value);
    T popFront();
    T popBack();
    const T& front() const;
    const T& back() const;
    bool isEmpty() const;
    size_t size() const;
    void clear();
};


template <typename T>
class ListImpl {
private:
    struct Node {
        T element;
        Node* previous;
        Node* next;
        Node(const T& value) : element(value), previous(nullptr), next(nullptr) {}
    };

    Node* firstNode;
    Node* lastNode;
    size_t nodeCount;

public:
    ListImpl();
    ~ListImpl();
    ListImpl(const ListImpl& other);
    ListImpl& operator=(const ListImpl& other);
    ListImpl(ListImpl&& other) noexcept;
    ListImpl& operator=(ListImpl&& other) noexcept;

    void pushFront(const T& value);
    void pushBack(const T& value);
    T popFront();
    T popBack();
    const T& front() const;
    const T& back() const;
    bool isEmpty() const;
    size_t size() const;
    void clear();
};

template <typename T>
using ArrayDequeComposition = DequeWithImpl<T, ArrayImpl<T>>;

template <typename T>
using ListDequeComposition = DequeWithImpl<T, ListImpl<T>>;

#endif


template <typename T>
ArrayDeque<T>::ArrayDeque()
    : elements(new T[INITIAL_SIZE]),
    head(0),
    tail(0),
    elementCount(0),
    arraySize(INITIAL_SIZE) {}

template <typename T>
ArrayDeque<T>::~ArrayDeque() {
    delete[] elements;
}

template <typename T>
ArrayDeque<T>::ArrayDeque(const ArrayDeque& other)
    : elements(new T[other.arraySize]),
    head(other.head),
    tail(other.tail),
    elementCount(other.elementCount),
    arraySize(other.arraySize) {
    std::copy(other.elements, other.elements + arraySize, elements);
}

template <typename T>
ArrayDeque<T>& ArrayDeque<T>::operator=(const ArrayDeque& other) {
    if (this != &other) {
        delete[] elements;
        arraySize = other.arraySize;
        head = other.head;
        tail = other.tail;
        elementCount = other.elementCount;
        elements = new T[arraySize];
        std::copy(other.elements, other.elements + arraySize, elements);
    }
    return *this;
}

template <typename T>
ArrayDeque<T>::ArrayDeque(ArrayDeque&& other) noexcept
    : elements(other.elements),
    head(other.head),
    tail(other.tail),
    elementCount(other.elementCount),
    arraySize(other.arraySize) {
    other.elements = nullptr;
    other.head = other.tail = 0;
    other.elementCount = other.arraySize = 0;
}

template <typename T>
ArrayDeque<T>& ArrayDeque<T>::operator=(ArrayDeque&& other) noexcept {
    if (this != &other) {
        delete[] elements;
        elements = other.elements;
        head = other.head;
        tail = other.tail;
        elementCount = other.elementCount;
        arraySize = other.arraySize;
        other.elements = nullptr;
        other.head = other.tail = 0;
        other.elementCount = other.arraySize = 0;
    }
    return *this;
}

template <typename T>
void ArrayDeque<T>::expand() {
    size_t newSize = arraySize * 2;
    T* newElements = new T[newSize];

    for (size_t i = 0; i < elementCount; ++i) {
        newElements[i] = elements[(head + i) % arraySize];
    }

    delete[] elements;
    elements = newElements;
    head = 0;
    tail = (elementCount == 0) ? 0 : elementCount - 1;
    arraySize = newSize;
}

template <typename T>
size_t ArrayDeque<T>::nextPosition(size_t pos) const {
    return (pos + 1) % arraySize;
}

template <typename T>
size_t ArrayDeque<T>::prevPosition(size_t pos) const {
    return (pos + arraySize - 1) % arraySize;
}

template <typename T>
void ArrayDeque<T>::doPushFront(const T& value) {
    if (elementCount == arraySize) {
        expand();
    }

    head = prevPosition(head);
    elements[head] = value;
    elementCount++;
}

template <typename T>
void ArrayDeque<T>::doPushBack(const T& value) {
    if (elementCount == arraySize) {
        expand();
    }

    if (elementCount > 0) {
        tail = nextPosition(tail);
    }
    elements[tail] = value;
    elementCount++;
}

template <typename T>
T ArrayDeque<T>::doPopFront() {
    if (doIsEmpty()) {
        throw std::runtime_error("Cannot pop from empty deque");
    }

    T value = elements[head];
    head = nextPosition(head);
    elementCount--;

    if (elementCount == 0) {
        head = tail = 0;
    }

    return value;
}

template <typename T>
T ArrayDeque<T>::doPopBack() {
    if (doIsEmpty()) {
        throw std::runtime_error("Cannot pop from empty deque");
    }

    T value = elements[tail];
    if (elementCount > 1) {
        tail = prevPosition(tail);
    }
    elementCount--;

    if (elementCount == 0) {
        head = tail = 0;
    }

    return value;
}

template <typename T>
const T& ArrayDeque<T>::doFront() const {
    if (doIsEmpty()) {
        throw std::runtime_error("Empty deque has no front element");
    }
    return elements[head];
}

template <typename T>
const T& ArrayDeque<T>::doBack() const {
    if (doIsEmpty()) {
        throw std::runtime_error("Empty deque has no back element");
    }
    return elements[tail];
}

template <typename T>
bool ArrayDeque<T>::doIsEmpty() const {
    return elementCount == 0;
}

template <typename T>
size_t ArrayDeque<T>::doSize() const {
    return elementCount;
}

template <typename T>
void ArrayDeque<T>::doClear() {
    head = tail = 0;
    elementCount = 0;
}


template <typename T>
ListDeque<T>::ListDeque() : firstNode(nullptr), lastNode(nullptr), nodeCount(0) {}

template <typename T>
ListDeque<T>::~ListDeque() {
    doClear();
}

template <typename T>
ListDeque<T>::ListDeque(const ListDeque& other) : firstNode(nullptr), lastNode(nullptr), nodeCount(0) {
    Node* current = other.firstNode;
    while (current) {
        doPushBack(current->element);
        current = current->next;
    }
}

template <typename T>
ListDeque<T>& ListDeque<T>::operator=(const ListDeque& other) {
    if (this != &other) {
        doClear();
        Node* current = other.firstNode;
        while (current) {
            doPushBack(current->element);
            current = current->next;
        }
    }
    return *this;
}

template <typename T>
ListDeque<T>::ListDeque(ListDeque&& other) noexcept
    : firstNode(other.firstNode), lastNode(other.lastNode), nodeCount(other.nodeCount) {
    other.firstNode = other.lastNode = nullptr;
    other.nodeCount = 0;
}

template <typename T>
ListDeque<T>& ListDeque<T>::operator=(ListDeque&& other) noexcept {
    if (this != &other) {
        doClear();
        firstNode = other.firstNode;
        lastNode = other.lastNode;
        nodeCount = other.nodeCount;
        other.firstNode = other.lastNode = nullptr;
        other.nodeCount = 0;
    }
    return *this;
}

template <typename T>
void ListDeque<T>::doPushFront(const T& value) {
    Node* newNode = new Node(value);

    if (doIsEmpty()) {
        firstNode = lastNode = newNode;
    }
    else {
        newNode->next = firstNode;
        firstNode->previous = newNode;
        firstNode = newNode;
    }

    nodeCount++;
}

template <typename T>
void ListDeque<T>::doPushBack(const T& value) {
    Node* newNode = new Node(value);

    if (doIsEmpty()) {
        firstNode = lastNode = newNode;
    }
    else {
        newNode->previous = lastNode;
        lastNode->next = newNode;
        lastNode = newNode;
    }

    nodeCount++;
}

template <typename T>
T ListDeque<T>::doPopFront() {
    if (doIsEmpty()) {
        throw std::runtime_error("Cannot pop from empty deque");
    }

    T value = firstNode->element;
    Node* oldFirst = firstNode;

    if (firstNode == lastNode) {
        firstNode = lastNode = nullptr;
    }
    else {
        firstNode = firstNode->next;
        firstNode->previous = nullptr;
    }

    delete oldFirst;
    nodeCount--;

    return value;
}

template <typename T>
T ListDeque<T>::doPopBack() {
    if (doIsEmpty()) {
        throw std::runtime_error("Cannot pop from empty deque");
    }

    T value = lastNode->element;
    Node* oldLast = lastNode;

    if (firstNode == lastNode) {
        firstNode = lastNode = nullptr;
    }
    else {
        lastNode = lastNode->previous;
        lastNode->next = nullptr;
    }

    delete oldLast;
    nodeCount--;

    return value;
}

template <typename T>
const T& ListDeque<T>::doFront() const {
    if (doIsEmpty()) {
        throw std::runtime_error("Empty deque has no front element");
    }
    return firstNode->element;
}

template <typename T>
const T& ListDeque<T>::doBack() const {
    if (doIsEmpty()) {
        throw std::runtime_error("Empty deque has no back element");
    }
    return lastNode->element;
}

template <typename T>
bool ListDeque<T>::doIsEmpty() const {
    return nodeCount == 0;
}

template <typename T>
size_t ListDeque<T>::doSize() const {
    return nodeCount;
}

template <typename T>
void ListDeque<T>::doClear() {
    while (firstNode) {
        Node* temp = firstNode;
        firstNode = firstNode->next;
        delete temp;
    }

    firstNode = lastNode = nullptr;
    nodeCount = 0;
}


template <typename T>
ArrayImpl<T>::ArrayImpl()
    : elements(new T[INITIAL_SIZE]),
    head(0),
    tail(0),
    elementCount(0),
    arraySize(INITIAL_SIZE) {}

template <typename T>
ArrayImpl<T>::~ArrayImpl() {
    delete[] elements;
}

template <typename T>
ArrayImpl<T>::ArrayImpl(const ArrayImpl& other)
    : elements(new T[other.arraySize]),
    head(other.head),
    tail(other.tail),
    elementCount(other.elementCount),
    arraySize(other.arraySize) {
    std::copy(other.elements, other.elements + arraySize, elements);
}

template <typename T>
ArrayImpl<T>& ArrayImpl<T>::operator=(const ArrayImpl& other) {
    if (this != &other) {
        delete[] elements;
        arraySize = other.arraySize;
        head = other.head;
        tail = other.tail;
        elementCount = other.elementCount;
        elements = new T[arraySize];
        std::copy(other.elements, other.elements + arraySize, elements);
    }
    return *this;
}

template <typename T>
ArrayImpl<T>::ArrayImpl(ArrayImpl&& other) noexcept
    : elements(other.elements),
    head(other.head),
    tail(other.tail),
    elementCount(other.elementCount),
    arraySize(other.arraySize) {
    other.elements = nullptr;
    other.head = other.tail = 0;
    other.elementCount = other.arraySize = 0;
}

template <typename T>
ArrayImpl<T>& ArrayImpl<T>::operator=(ArrayImpl&& other) noexcept {
    if (this != &other) {
        delete[] elements;
        elements = other.elements;
        head = other.head;
        tail = other.tail;
        elementCount = other.elementCount;
        arraySize = other.arraySize;
        other.elements = nullptr;
        other.head = other.tail = 0;
        other.elementCount = other.arraySize = 0;
    }
    return *this;
}

template <typename T>
void ArrayImpl<T>::expand() {
    size_t newSize = arraySize * 2;
    T* newElements = new T[newSize];

    for (size_t i = 0; i < elementCount; ++i) {
        newElements[i] = elements[(head + i) % arraySize];
    }

    delete[] elements;
    elements = newElements;
    head = 0;
    tail = (elementCount == 0) ? 0 : elementCount - 1;
    arraySize = newSize;
}

template <typename T>
size_t ArrayImpl<T>::nextPosition(size_t pos) const {
    return (pos + 1) % arraySize;
}

template <typename T>
size_t ArrayImpl<T>::prevPosition(size_t pos) const {
    return (pos + arraySize - 1) % arraySize;
}

template <typename T>
void ArrayImpl<T>::pushFront(const T& value) {
    if (elementCount == arraySize) {
        expand();
    }

    head = prevPosition(head);
    elements[head] = value;
    elementCount++;
}

template <typename T>
void ArrayImpl<T>::pushBack(const T& value) {
    if (elementCount == arraySize) {
        expand();
    }

    if (elementCount > 0) {
        tail = nextPosition(tail);
    }
    elements[tail] = value;
    elementCount++;
}

template <typename T>
T ArrayImpl<T>::popFront() {
    if (isEmpty()) {
        throw std::runtime_error("Cannot pop from empty deque");
    }

    T value = elements[head];
    head = nextPosition(head);
    elementCount--;

    if (elementCount == 0) {
        head = tail = 0;
    }

    return value;
}

template <typename T>
T ArrayImpl<T>::popBack() {
    if (isEmpty()) {
        throw std::runtime_error("Cannot pop from empty deque");
    }

    T value = elements[tail];
    if (elementCount > 1) {
        tail = prevPosition(tail);
    }
    elementCount--;

    if (elementCount == 0) {
        head = tail = 0;
    }

    return value;
}

template <typename T>
const T& ArrayImpl<T>::front() const {
    if (isEmpty()) {
        throw std::runtime_error("Empty deque has no front element");
    }
    return elements[head];
}

template <typename T>
const T& ArrayImpl<T>::back() const {
    if (isEmpty()) {
        throw std::runtime_error("Empty deque has no back element");
    }
    return elements[tail];
}

template <typename T>
bool ArrayImpl<T>::isEmpty() const {
    return elementCount == 0;
}

template <typename T>
size_t ArrayImpl<T>::size() const {
    return elementCount;
}

template <typename T>
void ArrayImpl<T>::clear() {
    head = tail = 0;
    elementCount = 0;
}


template <typename T>
ListImpl<T>::ListImpl() : firstNode(nullptr), lastNode(nullptr), nodeCount(0) {}

template <typename T>
ListImpl<T>::~ListImpl() {
    clear();
}

template <typename T>
ListImpl<T>::ListImpl(const ListImpl& other) : firstNode(nullptr), lastNode(nullptr), nodeCount(0) {
    Node* current = other.firstNode;
    while (current) {
        pushBack(current->element);
        current = current->next;
    }
}

template <typename T>
ListImpl<T>& ListImpl<T>::operator=(const ListImpl& other) {
    if (this != &other) {
        clear();
        Node* current = other.firstNode;
        while (current) {
            pushBack(current->element);
            current = current->next;
        }
    }
    return *this;
}

template <typename T>
ListImpl<T>::ListImpl(ListImpl&& other) noexcept
    : firstNode(other.firstNode), lastNode(other.lastNode), nodeCount(other.nodeCount) {
    other.firstNode = other.lastNode = nullptr;
    other.nodeCount = 0;
}

template <typename T>
ListImpl<T>& ListImpl<T>::operator=(ListImpl&& other) noexcept {
    if (this != &other) {
        clear();
        firstNode = other.firstNode;
        lastNode = other.lastNode;
        nodeCount = other.nodeCount;
        other.firstNode = other.lastNode = nullptr;
        other.nodeCount = 0;
    }
    return *this;
}

template <typename T>
void ListImpl<T>::pushFront(const T& value) {
    Node* newNode = new Node(value);

    if (isEmpty()) {
        firstNode = lastNode = newNode;
    }
    else {
        newNode->next = firstNode;
        firstNode->previous = newNode;
        firstNode = newNode;
    }

    nodeCount++;
}

template <typename T>
void ListImpl<T>::pushBack(const T& value) {
    Node* newNode = new Node(value);

    if (isEmpty()) {
        firstNode = lastNode = newNode;
    }
    else {
        newNode->previous = lastNode;
        lastNode->next = newNode;
        lastNode = newNode;
    }

    nodeCount++;
}

template <typename T>
T ListImpl<T>::popFront() {
    if (isEmpty()) {
        throw std::runtime_error("Cannot pop from empty deque");
    }

    T value = firstNode->element;
    Node* oldFirst = firstNode;

    if (firstNode == lastNode) {
        firstNode = lastNode = nullptr;
    }
    else {
        firstNode = firstNode->next;
        firstNode->previous = nullptr;
    }

    delete oldFirst;
    nodeCount--;

    return value;
}

template <typename T>
T ListImpl<T>::popBack() {
    if (isEmpty()) {
        throw std::runtime_error("Cannot pop from empty deque");
    }

    T value = lastNode->element;
    Node* oldLast = lastNode;

    if (firstNode == lastNode) {
        firstNode = lastNode = nullptr;
    }
    else {
        lastNode = lastNode->previous;
        lastNode->next = nullptr;
    }

    delete oldLast;
    nodeCount--;

    return value;
}

template <typename T>
const T& ListImpl<T>::front() const {
    if (isEmpty()) {
        throw std::runtime_error("Empty deque has no front element");
    }
    return firstNode->element;
}

template <typename T>
const T& ListImpl<T>::back() const {
    if (isEmpty()) {
        throw std::runtime_error("Empty deque has no back element");
    }
    return lastNode->element;
}

template <typename T>
bool ListImpl<T>::isEmpty() const {
    return nodeCount == 0;
}

template <typename T>
size_t ListImpl<T>::size() const {
    return nodeCount;
}

template <typename T>
void ListImpl<T>::clear() {
    while (firstNode) {
        Node* temp = firstNode;
        firstNode = firstNode->next;
        delete temp;
    }

    firstNode = lastNode = nullptr;
    nodeCount = 0;
}


template class ArrayDeque<int>;
template class ListDeque<int>;
template class ArrayDeque<std::string>;
template class ListDeque<std::string>;
template class ArrayImpl<int>;
template class ListImpl<int>;
template class ArrayImpl<std::string>;
template class ListImpl<std::string>;