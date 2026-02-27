#!/bin/bash
# Hamilton CI-Pipeline Simulation

echo "--- STARTING CI PIPELINE ---"

# 1. Build-Schritt
echo "Step 1: Building Project with CMake..."
cd src_org
mkdir -p build && cd build
cmake .. && make
if [ $? -ne 0 ]; then
    echo "BUILD FAILED!"
    exit 1
fi

# 2. Scan-Schritt
echo "Step 2: Running SonarQube Analysis..."
cd ..
sonar-scanner -Dsonar.token=sqp_f4a9a32b6ac965a1b0470744ef030ba8dd8845a0

echo "--- CI PIPELINE FINISHED ---"
