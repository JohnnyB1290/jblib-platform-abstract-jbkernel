/**
 * @file
 * @brief Callback interfaces
 *
 * Description of interfaces used for callbacks.
 * Also has callback interface implementation to
 * bind with C functions and static methods.
 *
 * @note
 * Copyright © 2019 Evgeniy Ivanov. Contacts: <strelok1290@gmail.com>
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

#ifndef CALLBACK_INTERFACES_HPP_
#define CALLBACK_INTERFACES_HPP_

#include <cstdint>
#include <functional>

namespace jblib
{
namespace jbkernel
{

class IVoidCallback
{
public:
    IVoidCallback() = default;
    template <class T>
    explicit IVoidCallback(T callback) : callback_(callback){}
    virtual ~IVoidCallback() = default;
    virtual void voidCallback(void* source, void* parameter)
    {
        callback_(source, parameter);
    }

protected:
    std::function<void(void*,void*)> callback_;
};

class FunctionBindVoidCallbackImpl : public IVoidCallback
{
public:
	explicit FunctionBindVoidCallbackImpl(void (*callback)()) : IVoidCallback()
	{
		this->callback_ = callback;
	}

	void voidCallback(void* const source, void* parameter) override
	{
		if(this->callback_ != nullptr)
			this->callback_();
	}

private:
	void (*callback_)() = nullptr;
};

class FunctionWithParametersBindVoidCallbackImpl : public IVoidCallback
{
public:
	explicit FunctionWithParametersBindVoidCallbackImpl(void (*callback)(void* parameter)) : IVoidCallback()
	{
		this->callback_ = callback;
	}

	void voidCallback(void* const source, void* parameter) override
	{
		if(this->callback_ != nullptr)
			this->callback_(parameter);
	}

private:
	void (*callback_)(void* parameter) = nullptr;
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

#endif /* CALLBACK_INTERFACES_HPP_ */
