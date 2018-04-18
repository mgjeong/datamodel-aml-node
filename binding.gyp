{
  "targets": [
    {
      "target_name": "aml",
      "sources":["./src/aml.cc", "./src/nrepresentation.cc", "./src/namlobject.cc", "./src/namldata.cc", "./src/namlutils.cc"],
      "include_dirs": [
        "<!(node -e \"require('nan')\")",
        './dependencies/datamodel-aml-cpp/include/',
        './dependencies/datamodel-aml-cpp/extlibs/pugixml/pugixml-1.8/src',
        './dependencies/datamodel-aml-cpp/protobuf/', 
      ],
      'cflags!': ['-fno-exceptions'],
      'cflags_cc!': ['-fno-exceptions', '-fno-rtti'],
      "cflags_cc": [ "-std=c++11" ],
      'conditions': [
          ['config=="x86_64_release"',
            {          
              "ldflags": [
              "-L<(module_root_dir)/dependencies/datamodel-aml-cpp/out/linux/x86_64/release/",
              "-Wl,-rpath,<(module_root_dir)/dependencies/datamodel-aml-cpp/out/linux/x86_64/release/",
              ]
            }
          ],
          ['config=="x86_64_debug"',
              {
                "ldflags": [
                "-L<(module_root_dir)/dependencies/datamodel-aml-cpp/out/linux/x86_64/debug/",
                "-Wl,-rpath,<(module_root_dir)/dependencies/datamodel-aml-cpp/out/linux/x86_64/debug/",
                ]
              }
          ],
          ['config=="x86_release"',
            {
              "ldflags": [
              "-L<(module_root_dir)/dependencies/datamodel-aml-cpp/out/linux/x86/release/",
              "-Wl,-rpath,<(module_root_dir)/dependencies/datamodel-aml-cpp/out/linux/x86/release/",
              ]
            }
          ],
          ['config=="x86_debug"',
              {
                "ldflags": [
                "-L<(module_root_dir)/dependencies/datamodel-aml-cpp/out/linux/x86/debug/",
                "-Wl,-rpath,<(module_root_dir)/dependencies/datamodel-aml-cpp/out/linux/x86/debug/",
                ]
              }
          ],
       ], 
      "libraries": [
          "-laml"
       ],
    }
  ]
}

