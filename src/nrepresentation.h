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

#ifndef NAML_REPRESENTATION_H
#define NAML_REPRESENTATION_H

#include <nan.h>

#include "Representation.h"

using namespace Nan;
using namespace v8;

namespace naml
{
    class NRepresentation : public ObjectWrap
    {
         public:
            static NAN_MODULE_INIT(Init);
            static v8::Local<v8::Object> NewInstance(int argc, v8::Local<v8::Value> argv[]);

         private:
            explicit NRepresentation(std::string filePath);
            ~NRepresentation();

            static NAN_METHOD(New);
            static NAN_METHOD(DataToAml);
            static NAN_METHOD(AmlToData);
            static NAN_METHOD(DataToByte);
            static NAN_METHOD(ByteToData);
            static NAN_METHOD(GetRepresentationId);
            static NAN_METHOD(GetConfigInfo);

            static inline Nan::Persistent<v8::Function> & constructor()
            {
                static Nan::Persistent<v8::Function> constructor;
                return constructor;
            }
            AML::Representation *nativeHandle;
    };
}

#endif  //NAML_REPRESENTATION_H
