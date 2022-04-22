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
#pragma

#include <mutex>

template<typename T>
class Node
{
public:
    T GetSortedSibling() const { return sorted_sibling_; }
    void SetSortedSibling(T sibling) {sorted_sibling_ = sibling;}

private:
    T sorted_sibling_{nullptr};
};

template<typename T>
class BlockingIntrusiveList
{
public:
    void Add(T new_node)
    {
        std::lock_guard<std::mutex> lg(mutex_);

        if(head_ == nullptr){
            head_ = new_node;
            return;
        } else {
            if(*new_node <= *head_){
                new_node->SetSortedSibling(head_);
                head_ = new_node;
                return;
            }

            T node = head_;

            while(node != nullptr && node->GetSortedSibling() != nullptr) {

                if(*new_node <= *node->GetSortedSibling()) {
                    new_node->SetSortedSibling(node->GetSortedSibling());
                    node->SetSortedSibling(new_node);
                    return;
                }

                node = node->GetSortedSibling();
            }

            // reached the end, add
            node->SetSortedSibling(new_node);
        }
    }

    bool Remove(T remove_node)
    {
        std::lock_guard<std::mutex> lg(mutex_);

        if(remove_node == nullptr){
            return false;
        }

        if(remove_node == head_){
            if(head_ != nullptr){
                head_ = head_->GetSortedSibling();
            }

            remove_node->SetSortedSibling(nullptr);

            return true;
        }

        for(T node = head_; node != nullptr; node = node->GetSortedSibling()){
            
            if(node->GetSortedSibling() == remove_node){
                // replace sibling
                if(node->GetSortedSibling() != nullptr) {
                    node->SetSortedSibling(node->GetSortedSibling()->GetSortedSibling());    
                } else {
                    node->SetSortedSibling(nullptr);
                }

                remove_node->SetSortedSibling(nullptr);

                return true;
            }
        }

        return false;
    }

    class Iterator{

    public:
        T node;
        explicit Iterator(T v) : node(v) {}

        operator T() const { return node; }
        operator T&() { return node; }
        const T &operator* () const { return node; }
        Iterator &operator++ ()
        {
            if(node){
                node = node->GetSortedSibling();
            }

            return *this;
        }
    };

    Iterator begin() { return Iterator(head_); }
    Iterator end() { return Iterator(nullptr); }

    bool IsEmpty() const { return head_ == nullptr; }

    size_t Size() const
    {
        size_t size = 0;

        for(T node = head_; node != nullptr; node = node->GetSortedSibling()){
            size++;
        }

        return size;
    }

    void DeleteNode(T node){
        if(Remove(node)){
            // only delete if node was successfully removed
            delete node;
        }
    }

    void Clear(){
        std::lock_guard<std::mutex> lg(mutex_);

        T node = head_;

        while(node != nullptr) {
            T next = node->GetSortedSibling();
            delete node;
            node = next;
        }

        head_ = nullptr;
    }

protected:

    T head_{nullptr};
    std::mutex mutex_;

};
