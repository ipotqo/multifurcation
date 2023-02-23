#!/usr/bin/python3

import subprocess
import re

# LAZY FRONTEND (USE EXECUTABLE)

PROGRAM_NAME = "./../bin/multifurcation"
INPUT_FILE = "multifurcation_one.in"
INPUT_PARAMETER = "0.0"

output = subprocess.run([PROGRAM_NAME, INPUT_FILE, INPUT_PARAMETER], stdout = subprocess.PIPE,
                        universal_newlines = True).stdout

