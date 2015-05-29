#!/usr/bin/env bash
python scripts/cpplint.py $( find src include -name "*.cc" -or -name "*.h" )
