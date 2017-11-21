#include <iostream>
#include <algorithm>
#include <utility>
#include <new>
#include <mutex>
#include <thread>
#include <memory>


template<typename T>
class stack {
public:
    stack();/*strong*/
    ~stack();
    stack(const stack&);/*strong*/
    size_t count() const;
    void push(T const &);/*strong*/
    auto pop()->std::shared_ptr<T>;
    stack& operator=(stack const& other);/*strong*/

private:
    T* array_;
    size_t array_size_;
    mutable std::mutex mutex_;
    size_t count_;
    void swap(stack<T>&);
};


template <typename T>
void stack<T>::swap(stack<T>& other)
{
    std::lock(mutex_, other.mutex_);
    std::swap(array_, other.array_);
    std::swap(array_size_, other.array_size_);
    std::swap(count_, other.count_);
    mutex_.unlock();
    other.mutex_.unlock();
}


template<typename T>
stack<T>::stack() : array_size_(1), count_(0)
{
    array_ = new T[1]();
}
template<typename T>
stack<T>::~stack()
{
    count_ = 0;
    array_size_ = 0;
    delete[] array_;
}


template <typename T>
stack<T>::stack(stack<T> const& obj)
{
    std::lock_guard<std::mutex> lock(obj.mutex_);
    T* temp = new T[obj.array_size_];
    count_ = obj.count_;
    array_size_ = obj.array_size_;
    array_ = temp;
    try
    {
        std::copy(obj.array_, obj.array_ + count_, array_);
    }
    catch (...)
    {
        std::cerr << "Error";
        delete[] array_;
    }
}


template<typename T>
stack<T>& stack<T>::operator=(stack<T> const& obj)
{
    if (this != &obj)
    {
        stack(obj).swap(*this);
    }
    return *this;
}


template<typename T>
size_t stack<T>::count() const
{
    std::lock_guard<std::mutex> lock(mutex_);
    return count_;
}


template<typename T>
void stack<T>::push(T const& el)
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (array_size_ == count_)
    {
        array_size_ *= 2;
        T* temp = new T[array_size_];
        try
        {
            std::copy(array_, array_ + count_, temp);
        }
        catch(...)
        {
            delete[] array_;
            throw;
        }
        delete[] array_;
        array_ = temp;
    }
    array_[count_] = el;
    ++count_;

}


template <typename T>
auto stack<T>::pop() -> std::shared_ptr<T>
{
    std::lock_guard<std::mutex> lock(mutex_);

    if (count_ == 0)
    {
        throw "error";
    }


    auto top = std::make_shared<T>(*(array_+count_-1));
    --count_;

    return top;
}

