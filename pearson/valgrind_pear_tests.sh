#!/bin/bash

# Define an array of dataset files
DATA_FILES=("128.data" "256.data" "512.data" "1024.data")

# Loop through each dataset file
for FILE in "${DATA_FILES[@]}"
do
    # Define the output filename based on the input file
    OUTPUT_FILE="output_${FILE%.*}_pearson.data"

    # Run Valgrind with Callgrind for each dataset file
    echo "Running Valgrind for Pearson on file $FILE..."
    valgrind --tool=callgrind ./pearson "./data/$FILE" "./data/$OUTPUT_FILE"

    # Optional: Sleep for a bit to avoid overwhelming the system
    sleep 2
done

echo "All dataset files have been processed with Callgrind!"
