#!/bin/bash
TESTCODE=$1
DIMENSION=$2
FILE=$3

java Strassen ${TESTCODE} ${DIMENSION} ${FILE}