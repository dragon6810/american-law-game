#!/usr/bin/env bash

if make; then
    mkdir -p run
    cd run
    ../bin/tariffwar

    exit 0
fi

exit 1