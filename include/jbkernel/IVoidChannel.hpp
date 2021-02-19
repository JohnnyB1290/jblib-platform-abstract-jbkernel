/**
 * @file
 * @brief Void Channel Interface
 *
 *
 * @note
 * Copyright © 2019,2021 Evgeniy Ivanov. Contacts: <strelok1290@gmail.com>
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

#include <cstddef>
#include "jbkernel/callback_interfaces.hpp"

namespace jblib
{
    namespace jbkernel
    {

        class IVoidChannel
        {
        public:
            typedef struct
            {
                void* parameters = nullptr;
                uint32_t parametersSize = 0;
            }ConnectionParameter_t;

            IVoidChannel()= default;
            virtual ~IVoidChannel()= default;
            virtual void initialize(void* (*mallocFunc)(size_t),
                    uint16_t txBufferSize, IChannelCallback* callback) = 0;
            virtual void deinitialize() = 0;
            virtual void tx(uint8_t* buffer, uint16_t size, void* parameter) = 0;
            virtual void getParameter(uint8_t number, void* value) = 0;
            virtual void setParameter(uint8_t number, void* value) = 0;
        };

        class VoidChannel
        {
        public:
            VoidChannel() = default;
            virtual ~VoidChannel() = default;
            virtual void initialize() = 0;
            virtual void tx(uint8_t* data, uint16_t size, void* connectionParameter) = 0;

            template<typename Callback>
            void addCallback(Callback& callback){
                this->callback_ = std::ref(callback);
            }
            template<typename Callback>
            void addCallback(Callback&& callback){
                this->callback_ = callback;
            }
            template<typename Callback>
            void addCallback(Callback* callback){
                this->addCallback(*callback);
            }
            virtual void removeCallback(){
                this->callback_ = nullptr;
            }
            virtual void invokeCallback(uint8_t* data, uint16_t size, void* source,
                                        void* connectionParameter)
            {
                if(this->callback_ != nullptr){
                    this->callback_(data, size, source, connectionParameter);
                }
            }

        protected:
            std::function<void(uint8_t* data, uint16_t size, void* source,
                    void* connectionParameter)> callback_ = nullptr;
        };

    }
}
