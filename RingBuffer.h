#pragma once

#include <cstring>
#include <cstdio>

template<class T, unsigned S>
class RingBuffer
{
public:
    void Put(T item)
    {
        buf_[head_] = item;
        head_ = (head_ + 1) % S;

        if (head_ == tail_)
        {
            tail_ = (tail_ + 1) % S;
        }
    }

    T Get()
    {
        if (Empty())
        {
            return T();
        }

        //Read data and advance the tail (we now have a free space)
        auto val = buf_[tail_];
        tail_ = (tail_ + 1) % S;

        return val;
    }

    T Peek() const
    {
        if (Empty())
        {
            return T();
        }

        return buf_[tail_];
    }

    void Reset()
    {
        head_ = tail_;
    }

    bool Empty() const
    {
        //if head and tail are equal, we are empty
        return head_ == tail_;
    }

    bool Full() const
    {
        //If tail is ahead the head by 1, we are full
        return ((head_ + 1) % S) == tail_;
    }

    unsigned Available() const
    {
        return (S + head_ - tail_) % S;
    }

    void Read(T* buffer, uint16_t len)
    {
        //auto val = buf_[tail_];
        //tail_ = (tail_ + 1) % S;

        for (uint16_t i = 0; i < len; i++)
        {
            buffer[i] = Get();
        }
    }

private:
    T buf_[S]{};
    uint16_t head_{ 0 };
    uint16_t tail_{ 0 };
};
