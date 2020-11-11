/**
 * @file
 * @brief Void Timer Interface
 *
 * Description of void timer interface
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

#include "jbkernel/callback_interfaces.hpp"

namespace jblib
{
    namespace jbkernel
    {
        class IVoidTimer
        {
        public:
            IVoidTimer() = default;
            virtual ~IVoidTimer() = default;
            virtual void initialize(uint32_t periodUs) = 0;
            virtual void initializeTicks(uint32_t periodTicks){}
            virtual void deinitialize() = 0;
            virtual void start() = 0;
            virtual void stop() = 0;
            virtual void reset() = 0;
            virtual uint32_t getCounter() = 0;
            virtual uint32_t getUsecCounter(){ return 0; }
            virtual void setCounter(uint32_t ticks) = 0;
            virtual void setUsecCounter(uint32_t us){}
            virtual void changePeriod(uint32_t periodUs){};
            virtual void changePeriodTicks(uint32_t periodTicks){};
            virtual void addCallback(IVoidCallback* callback) = 0;
            virtual void addCallback(IVoidCallback* callback, void* parameter){};
            virtual void deleteCallback() = 0;
        };
    }
}
