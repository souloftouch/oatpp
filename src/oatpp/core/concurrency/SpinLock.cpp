/***************************************************************************
 *
 * Project         _____    __   ____   _      _
 *                (  _  )  /__\ (_  _)_| |_  _| |_
 *                 )(_)(  /(__)\  )( (_   _)(_   _)
 *                (_____)(__)(__)(__)  |_|    |_|
 *
 *
 * Copyright 2018-present, Leonid Stryzhevskyi <lganzzzo@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ***************************************************************************/

#include "SpinLock.hpp"

#include "./Thread.hpp"

namespace oatpp { namespace concurrency {
  
  
SpinLock::SpinLock(Atom& atom)
  : m_atom(&atom)
{
  while (std::atomic_exchange_explicit(m_atom, true, std::memory_order_acquire)) {
    std::this_thread::yield();
  }
}

SpinLock::~SpinLock(){
  std::atomic_store_explicit(m_atom, false, std::memory_order_release);
}
  
void SpinLock::lock(Atom& atom) {
  while (std::atomic_exchange_explicit(&atom, true, std::memory_order_acquire)) {
    std::this_thread::yield();
  }
}

void SpinLock::unlock(Atom& atom) {
  std::atomic_store_explicit(&atom, false, std::memory_order_release);
}
  
}}
