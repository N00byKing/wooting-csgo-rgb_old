{
  "targets": [
    {
      "target_name": "wooting_interface",
      "sources": [
        "main.cpp"
      ],
      "include_dirs": [
        "<!@(node -p \"require('node-addon-api').include\")",
        "/usr/include/"
      ],
      "libraries": [
        "/lib64/libhidapi-libusb.so",
        "/lib64/libwooting-rgb-sdk.so",
        "/lib64/libjsoncpp.so"
      ],
      "dependencies": [
        "<!(node -p \"require('node-addon-api').gyp\")"
      ],
      "cflags!": ["-fno-exceptions"],
      "cflags_cc!": ["-fno-exceptions"],
      "defines": ["NAPI_CPP_EXCEPTIONS"]
    }
  ]
}