### What is this?

This is an extension created to PHP using the Dynatrace OneAgentSDK. The objective here is to make available oneagent SDK functions available to PHP.

This is a work in progress and we still need to figure out why the agent is not loaded.

### PreReqs to build this extension

First you need to have the following on your environment:

1. Fully working PHP devel packages, either install the source through a package manager or by fully building PHP on you system
    1. To install you can follow this (document)[https://php.watch/articles/compile-php-fedora-rhel-centos]
2. Build tools gcc, make etc...
3. OneAgent SDK available on the disk

### How to build this extension

1. Clone the repo
2. ```cd dynatrace_sdk_extension\dynatrace_sdk_extension```
3. Edit the config.m4 file pointing to the path fro the OneAgent SDK
4. Run: ```phpize && ./configure --with-onesdk && make && sudo make install```

### How to test this extension

Crate test file, test.php:

```
<?php
printf("Hello!!!! Starting trace");
simple_trace();
printf("Finished trace");
?>
```

Execute the following command: ```php -dextension=dynatrace_sdk_extension.so processor.php```

This will load the extension and the ```simple_trace()``` function will be available and will be executed by your PHP code.

### Known problems

This is a working in progress and right now the function to load the agent does not work, we need to understand why this happens, any help with that is much apreciated.

### Extra tests

There is a ```python_wrapper``` directory on this repo, this is just to test the same process we are doing with PHP but now on Python.

To make this run, execute the following:

1. ```gcc -I<OneAgentSDK Path>/include -L<OneAgentSDK Path>/lib/linux-x86_64 -shared -o liboneagent_wrapper.so -fPIC wrapper.c -lonesdk_shared```
      1. Change the directories above to the ones on your environment
2. Run the python example: ```python3 example.py```
  	  1. This will bring the script up and will generate a trace simulating a remote call

We need to make this work for PHP, and then add extra instrumentation to PHP code