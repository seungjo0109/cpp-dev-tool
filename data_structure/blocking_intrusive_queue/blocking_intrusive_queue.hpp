/****************************************************************************
 *
 *   Copyright (c) 2013-2021 PX4 Development Team. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name PX4 nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/
#pragma once

#include <mutex>

template<typename T>
class Node
{
public:

    T GetNextNode() const { return next_node_; }
    void SetNextNode(T next_node) { next_node_ = next_node; }

private:
    T next_node_{nullptr};
};

template<typename T>
class BlockingIntrusiveQueue
{
public:

    BlockingIntrusiveQueue() = default;
    BlockingIntrusiveQueue(const BlockingIntrusiveQueue&) = delete;
    BlockingIntrusiveQueue& operator=(const BlockingIntrusiveQueue&) = delete;

    bool IsEmpty() const { return head_ == nullptr; }

    T Front() const { return head_; }
    T Back() const {return tail_; }

    size_t Size() const
    {
        size_t size = 0;

        for (auto node = Front(); node != nullptr; node = node->GetNextNode() ) {
            size++;
        }

        return size;
    }

    void Push(T new_node)
    {
        std::lock_guard<std::mutex> lg(mutex_);

        if((new_node->GetNextNode() != nullptr) || (new_node == tail_)) {
            return;
        }

        if(head_ == nullptr){
            head_ = new_node;
        }

        if (tail_ != nullptr) {
            tail_->SetNextNode(new_node);
        }     

        tail_ = new_node;  
    }

    T Pop()
    {
        std::lock_guard<std::mutex> lg(mutex_);

        T ret = head_;

        if(!IsEmpty()) {
            if(head_ != tail_) {
                head_ = head_->GetNextNode();
            } else {
                // only one item left
                head_ = nullptr;
                tail_ = nullptr;
            }

            ret->SetNextNode(nullptr);
        }

        return ret;
    }

    bool Remove(T remove_node)
    {
        std::lock_guard<std::mutex> lg(mutex_);

        if(remove_node == head_) {
            if(head_->GetNextNode() != nullptr) {
                head_ = head_->GetNextNode();
                remove_node->SetNextNode(nullptr);
            } else {
                head_ = nullptr;
                tail_ = nullptr;
            }

            return true;
        }

        for(T node = head_; node != nullptr; node = node->GetNextNode()){
            
            if(node->GetNextNode() == remove_node){
                if(remove_node == tail_){
                    tail_ = node;
                }

                node->SetNextNode(remove_node->GetNextNode());
                remove_node->SetNextNode(nullptr);

                return true;
            }
        }

        return false;
    }

    void Clear()
    {
        while(!IsEmpty()){
            Pop();
        }
    }

    class Iterator {

    public:
        T node;
        Iterator(T v) : node(v) {}

        operator T() const { return node; }
        operator T&() { return node; }
        T operator* () const { return node; }
        Iterator &operator++ ()
        {
            if(node){
                node = node->GetNextNode();
            };

            return *this;
        }
    };

    Iterator begin() { return Iterator(head_); }
    Iterator end() { return Iterator(nullptr); }

private:

    std::mutex mutex_;
    T head_{nullptr};
    T tail_{nullptr};

};