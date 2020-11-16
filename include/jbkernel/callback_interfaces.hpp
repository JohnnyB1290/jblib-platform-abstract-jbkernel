/**
 * @file
 * @brief Callback interfaces
 *
 * Description of interfaces used for callbacks.
 * Also has callback interface implementation to
 * bind with C functions and static methods.
 *
 * @note
 * Copyright © 2019-2020 Evgeniy Ivanov. Contacts: <strelok1290@gmail.com>
 * All rights reserved.
 * @note
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 * @note
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * @note
 * This file is a part of JB_Lib.
 */

#pragma once

#include <functional>

namespace jblib
{
    namespace jbkernel
    {
        class IVoidCallback
        {
        public:
            IVoidCallback() = default;
            virtual ~IVoidCallback() = default;
            virtual void voidCallback(void* source, void* parameter) = 0;
            virtual void operator()(void* source, void* parameter){
                this->voidCallback(source, parameter);
            }
        };

        class VoidCallback : public IVoidCallback
        {
        public:
            VoidCallback() = default;
            template <class T>
            explicit VoidCallback(T& callback) : IVoidCallback(), callback_(std::ref(callback)) {}
            template <class T>
            explicit VoidCallback(T&& callback) : IVoidCallback(), callback_(callback) {}
            ~VoidCallback() override = default;
            void voidCallback(void* source, void* parameter) override
            {
                if(callback_ != nullptr){
                    callback_(source, parameter);
                }
            }

        protected:
            std::function<void(void*,void*)> callback_ = nullptr;
        };

        class CallbackCaller
        {
        public:
            CallbackCaller() = default;
            virtual ~CallbackCaller() = default;
            template<typename Callback>
            void addCallback(Callback& callback, void* parameter = nullptr){
                this->callback_ = std::ref(callback);
                this->callbackParameter_ = parameter;
            }
            template<typename Callback>
            void addCallback(Callback&& callback, void* parameter = nullptr){
                this->callback_ = callback;
                this->callbackParameter_ = parameter;
            }
            template<typename Callback>
            void addCallback(Callback* callback, void* parameter = nullptr){
                this->addCallback(*callback, parameter);
            }
            virtual void removeCallback(){
                this->callback_ = nullptr;
                this->callbackParameter_ = nullptr;
            }
            virtual void invokeCallback(void* source)
            {
                if(this->callback_ != nullptr){
                    this->callback_(source, this->callbackParameter_);
                }
            }
            virtual void invokeCallback(void* source, void* parameter)
            {
                if(this->callback_ != nullptr){
                    this->callback_(source, parameter);
                }
            }

        protected:
            std::function<void(void*,void*)> callback_ = nullptr;
            void* callbackParameter_ = nullptr;
        };

        class IChannelCallback
        {
        public:
            IChannelCallback()  = default;
            virtual ~IChannelCallback() = default;
            virtual void channelCallback(uint8_t* buffer, uint16_t size,
                    void* source, void* parameter) = 0;
        };
    }
}
