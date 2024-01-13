#!/bin/bash

python setup.py build

cp build/lib.linux-x86_64-cpython-312/math_tools_c.cpython-312-x86_64-linux-gnu.so .

python -i test_after_compile.py