###############################################################################
# Copyright 2018 Samsung Electronics All Rights Reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
###############################################################################

#!/bin/bash
set +e
#Colors
RED="\033[0;31m"
GREEN="\033[0;32m"
BLUE="\033[0;34m"
NO_COLOUR="\033[0m"

PROJECT_ROOT=$(pwd)
DEP_ROOT=$(pwd)/dependencies
AML_TARGET_ARCH="$(uname -m)"
AML_INSTALL_PREREQUISITES=false
AML_BUILD_MODE="release"
AML_DISABLE_PROTOBUF=false
AML_JS_DEP=false

install_aml_dependencies() {
    if [ "debug" = ${AML_BUILD_MODE} ]; then
        AML_LOGGING="on"
    fi

    if [ -d "./dependencies/datamodel-aml-cpp" ] ; then
        echo "dependencies folder exist"
    else
        mkdir dependencies
        cd ./dependencies
        #clone datamodel-aml-cpp
        git clone git@github.sec.samsung.net:RS7-EdgeComputing/datamodel-aml-cpp.git
        cd $PROJECT_ROOT
    fi

    cd ./dependencies/datamodel-aml-cpp
    git fetch origin
	 git checkout v1.0_rel

    # Build datamodel-aml-cpp for given architecture [x86/x86_64]
    echo -e "${GREEN}Installing aml library and its dependencies${NO_COLOUR}"
    ./build_common.sh --target_arch=${AML_TARGET_ARCH} --install_prerequisites=${AML_INSTALL_PREREQUISITES} --build_mode=${AML_BUILD_MODE} --logging=${AML_LOGGING} --disable_protobuf=${AML_DISABLE_PROTOBUF}
    echo -e "${GREEN}Installation of aml dependencies [datamodel-aml-cpp] done${NO_COLOUR}"
}

install_jsdependencies() {
    echo -e "${GREEN}Installing node-gyp${NO_COLOUR}"
    npm install node-gyp
    echo -e "${GREEN}Installing NAN${NO_COLOUR}"
    npm install --save nan
    echo -e "${GREEN}Installing jsdoc${NO_COLOUR}"
    npm install --save-dev jsdoc
    echo -e "${GREEN}Installing mocha [unit test]${NO_COLOUR}"
    npm install --save-dev mocha
    echo -e "${GREEN}Installing nyc [Code Coverage]${NO_COLOUR}"
    npm install --save-dev nyc
    echo -e "${GREEN}Installation of js dependencies done${NO_COLOUR}"
}

build_x86() {
    cd $PROJECT_ROOT
    node_modules/node-gyp/bin/node-gyp.js clean
    if [ "debug" = ${AML_BUILD_MODE} ]; then
        node_modules/node-gyp/bin/node-gyp.js --config=x86_debug configure
    else
        node_modules/node-gyp/bin/node-gyp.js --config=x86_release configure
    fi
    node_modules/node-gyp/bin/node-gyp.js build
    echo -e "${GREEN}Installation of aml addon done${NO_COLOUR}"
}

build_x86_64() {
    cd $PROJECT_ROOT
    node_modules/node-gyp/bin/node-gyp.js clean
    if [ "debug" = ${AML_BUILD_MODE} ]; then
        node_modules/node-gyp/bin/node-gyp.js --config=x86_64_debug configure
    else
        node_modules/node-gyp/bin/node-gyp.js --config=x86_64_release configure
    fi
    node_modules/node-gyp/bin/node-gyp.js build
    echo -e "${GREEN}Installation of aml addon done${NO_COLOUR}"
}

clean_aml() {
    echo -e "Cleaning ${BLUE}${PROJECT_ROOT}${NO_COLOUR}"
    echo -e "Deleting  ${RED}${PROJECT_ROOT}/dependencies/${NO_COLOUR}"
    rm -rf ./dependencies/datamodel-aml-cpp
    echo -e "Finished Cleaning ${BLUE}${aml}${NO_COLOUR}"
}

usage() {
    echo -e "${BLUE}Usage:${NO_COLOUR} ./build_common.sh <option>"
    echo -e "${GREEN}Options:${NO_COLOUR}"
    echo "  --target_arch=[x86|x86_64]                                         :  Choose Target Architecture"
    echo "  --build_mode=[release|debug](default: release)                     :  Build in release or debug mode"
    echo "  --js_dependencies=[true|false](default: false)                     :  install js dependencies"
    echo "  --disable_protobuf=[true|false](default: false)                    :  Disable protobuf feature"
    echo "  --install_prerequisites=[true|false](default: false)               :  Install the prerequisite S/W to build aml [Protocol-buffer]"
    echo "  -c                                                                 :  Clean aml Repository and its dependencies"
    echo "  -h / --help                                                        :  Display help and exit"
    echo -e "${GREEN}Examples: ${NO_COLOUR}"
    echo -e "${BLUE}  build:-${NO_COLOUR}"
    echo "  $ ./build_common.sh --target_arch=x86_64"
    echo "  $ ./build_common.sh --install_prerequisites=true --target_arch=x86_64 "
    echo -e "${BLUE}  debug mode build:-${NO_COLOUR}"
    echo "  $ ./build_common.sh --target_arch=x86_64 --build_mode=debug"
    echo -e "${BLUE}  clean:-${NO_COLOUR}"
    echo "  $ ./build_common.sh -c"
    echo -e "${BLUE}  help:-${NO_COLOUR}"
    echo "  $ ./build_common.sh -h"
    echo -e "${GREEN}Notes: ${NO_COLOUR}"
    echo "  - While building for the first time use: --js_dependencies=true option."
}

build_aml() {
    if [ ${AML_JS_DEP} = true ]; then
        install_jsdependencies
    fi

    if [ "x86" = ${AML_TARGET_ARCH} ]; then
         build_x86;
    elif [ "x86_64" = ${AML_TARGET_ARCH} ]; then
         build_x86_64;
    else
         echo -e "${RED}Not a supported architecture${NO_COLOUR}"
         usage; exit 1;
    fi
}

process_cmd_args() {
    if [ "$#" -eq 0  ]; then
        echo -e "No argument.."
        usage; exit 1
    fi

    while [ "$#" -gt 0  ]; do
        case "$1" in
            --install_prerequisites=*)
                AML_INSTALL_PREREQUISITES="${1#*=}";
                if [ ${AML_INSTALL_PREREQUISITES} != true ] && [ ${AML_INSTALL_PREREQUISITES} != false ]; then
                    echo -e "${RED}Unknown option for --install_prerequisites${NO_COLOUR}"
                    shift 1; exit 0
                fi
                echo -e "${GREEN}Install the prerequisites before build: ${AML_INSTALL_PREREQUISITES}${NO_COLOUR}"
                shift 1;
                ;;
            --target_arch=*)
                AML_TARGET_ARCH="${1#*=}";
                echo -e "${GREEN}Target Arch is: $AML_TARGET_ARCH${NO_COLOUR}"
                shift 1
                ;;
            --build_mode=*)
                AML_BUILD_MODE="${1#*=}";
                echo -e "${GREEN}Build mode is: $AML_BUILD_MODE${NO_COLOUR}"
                shift 1;
                ;;
            --js_dependencies=*)
                AML_JS_DEP="${1#*=}";
                if [ ${AML_JS_DEP} != true ] && [ ${AML_JS_DEP} != false ]; then
                    echo -e "${RED}Unknown option for --js_dependencies${NO_COLOUR}"
                    shift 1; exit 0
                fi
                echo -e "${GREEN}Build js dependencies: $AML_JS_DEP${NO_COLOUR}"
                shift 1;
                ;;
            --disable_protobuf=*)
                AML_DISABLE_PROTOBUF="${1#*=}";
                if [ ${AML_DISABLE_PROTOBUF} != true ] && [ ${AML_DISABLE_PROTOBUF} != false ]; then
                    echo -e "${RED}Unknown option for --disable_protobuf${NO_COLOUR}"
                    shift 1; exit 0
                fi
                echo -e "${GREEN}is Protobuf disabled : $AML_DISABLE_PROTOBUF${NO_COLOUR}"
                shift 1;
                ;;
            -c)
                clean_aml
                shift 1; exit 0
                ;;
            -h)
                usage; exit 0
                ;;
            --help)
                usage; exit 0
                ;;
            -*)
                echo -e "${RED}"
                echo "unknown option: $1" >&2;
                echo -e "${NO_COLOUR}"
                usage; exit 1
                ;;
            *)
                echo -e "${RED}"
                echo "unknown option: $1" >&2;
                echo -e "${NO_COLOUR}"
                usage; exit 1
                ;;
        esac
    done
}

process_cmd_args "$@"
install_aml_dependencies
build_aml
echo -e "${GREEN}Build done${NO_COLOUR}"


