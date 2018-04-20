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

#ifndef NAML_OBJECT_H
#define NAML_OBJECT_H

#include <nan.h>

#include "Representation.h"
#include "AMLInterface.h"

using namespace Nan;
using namespace v8;

namespace naml
{
    class NAMLObject : public ObjectWrap
    {
         public:
            friend class NRepresentation;

            static NAN_MODULE_INIT(Init);
            static v8::Local<v8::Object> NewInstance(int argc, v8::Local<v8::Value> argv[]);

         private:
            explicit NAMLObject() {}
            explicit NAMLObject(std::string deviceId, std::string timeStamp, std::string id);
            ~NAMLObject();

            static NAN_METHOD(New);
            static NAN_METHOD(AddData);
            static NAN_METHOD(GetData);
            static NAN_METHOD(GetDataNames);
            static NAN_METHOD(GetDeviceId);
            static NAN_METHOD(GetTimeStamp);
            static NAN_METHOD(GetId);

            static inline Nan::Persistent<v8::Function> & constructor()
            {
                static Nan::Persistent<v8::Function> constructor;
                return constructor;
            }
            AML::AMLObject *nativeHandle;
    };
}

#endif  //NAML_OBJECT_H
