#include <iostream>
#include <string> // Include for std::string

typedef int Rank;
#define DEFAULT_CAPACITY 10000

template <typename T>
class Vector {
protected:
    Rank _size;
    int _capacity;
    T* _elem;

public:
    // Constructor
    Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = T()) : _capacity(c), _size(0) {
        _elem = new T[_capacity];
        for (_size = 0; _size < s; ++_size)
            _elem[_size] = v;
    }

    // Destructor
    ~Vector() { delete[] _elem; }

    // Read-only
    Rank size() const { return _size; }
    bool empty() const { return _size == 0; }

    // Write-only
    T& operator[](Rank r) const { return _elem[r]; }

    T remove(Rank r) {
        T v = _elem[r];
        for (Rank i = r; i < _size - 1; ++i)
            _elem[i] = _elem[i + 1];
        _size--;
        return v;
    }

    Rank insert(Rank r, T const& e) {
        if (_size == _capacity) { // Check if the vector is full
            // Handle resizing of the vector (not shown in this simplified example)
        }
        for (Rank i = _size; i > r; --i)
            _elem[i] = _elem[i - 1];
        _elem[r] = e;
        _size++;
        return r;
    }

    Rank insert(T const& e) { return insert(_size, e); }
};

template <typename T>
class Stack : public Vector<T> {
public:
    void push(T const& e) { this->insert(this->size(), e); }
    T pop() { return this->remove(this->size() - 1); }
    T& top() { return (*this)[this->size() - 1]; }
};

int main() {
    int N, operand;
    std::string operation;
    // Initialize stack
    Stack<int> stack;

    std::cin >> N;
    for (int i = 0; i < N; i++) {
        std::cin >> operation;
        if (operation == "push") {
            std::cin >> operand;
            stack.push(operand);
        } else if (operation == "top") {
            if (!stack.empty())
                std::cout << stack.top() << std::endl;
            else
                std::cout << -1 << std::endl;
        } else if (operation == "size") {
            std::cout << stack.size() << std::endl;
        } else if (operation == "empty") {
            std::cout << stack.empty() << std::endl;
        } else if (operation == "pop") {
			if(stack.empty()) std::cout<<-1<<std::endl;
            else std::cout<<stack.pop()<<std::endl;
        }
    }
    return 0;
}
