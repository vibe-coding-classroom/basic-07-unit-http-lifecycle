#!/bin/bash

# --- 1. Compilation Check ---
echo "Running Compilation Check..."
pio run
if [ $? -eq 0 ]; then
    echo "Compilation: PASSED"
else
    echo "Compilation: FAILED"
    exit 1
fi

# --- 2. Documentation Check ---
echo "Checking Documentation..."

# Check if Waterfall_Log.md has been modified (not just the header)
if grep -q "DNS Lookup | |" docs/Waterfall_Log.md; then
    echo "Waterfall_Log.md: NOT FILLED"
    exit 1
else
    echo "Waterfall_Log.md: PASSED"
fi

# Check if Performance.csv has data (more than just the header and empty lines)
DATA_LINES=$(grep -v "^Iteration" docs/Performance.csv | grep -c "[0-9]")
if [ "$DATA_LINES" -eq 0 ]; then
    echo "Performance.csv: NO DATA"
    exit 1
else
    echo "Performance.csv: PASSED"
fi

# --- 3. Code Structure Check ---
echo "Checking Code Structure..."

# Check for API routes
if grep -q "/api/status" src/main.cpp && grep -q "/api/command" src/main.cpp; then
    echo "API Routes: PASSED"
else
    echo "API Routes: MISSING /api/status OR /api/command"
    exit 1
fi

echo "All checks passed!"
exit 0
