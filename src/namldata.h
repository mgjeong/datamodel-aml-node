/*******************************************************************************
 * Copyright 2018 Samsung Electronics All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 *******************************************************************************/

#ifndef NAML_DATA_H
#define NAML_DATA_H

#include <nan.h>

#include "AMLInterface.h"

using namespace Nan;
using namespace v8;

namespace naml
{
    class NAMLData : public ObjectWrap
    {
         public:
            friend class NAMLObject;
            friend class NRepresentation;

            static NAN_MODULE_INIT(Init);
            static v8::Local<v8::Object> NewInstance();

         private:
            explicit NAMLData();
            ~NAMLData();

            static NAN_METHOD(New);
            static NAN_METHOD(GetValueToStr);
            static NAN_METHOD(GetValueToStrArr);
            static NAN_METHOD(GetValueToAMLData);
            static NAN_METHOD(GetKeys);
            static NAN_METHOD(GetValueType);
            static NAN_METHOD(SetValue);
            static NAN_METHOD(SetVectorValue);
            static NAN_METHOD(SetAMLDataValue);

            static inline Nan::Persistent<v8::Function> & constructor()
            {
                static Nan::Persistent<v8::Function> constructor;
                return constructor;
            }
            AML::AMLData *nativeHandle;
    };
}

#endif  //NAML_DATA_H
