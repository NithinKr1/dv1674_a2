#!/bin/bash

# Define an array of radii to test (adjust as needed for different blur intensities)
RADIUS_VALUES=(1 100 500 900 1000)

# Define an array of input PPM files
INPUT_FILES=("im1.ppm" "im2.ppm" "im3.ppm" "im4.ppm")

# Loop through each input file
for FILE in "${INPUT_FILES[@]}"
do
    # Loop through each radius
    for RADIUS in "${RADIUS_VALUES[@]}"
    do
        # Define the output filename based on the input file and radius
        OUTPUT_FILE="output_${FILE%.*}_r${RADIUS}.ppm"
        
        # Run Valgrind with Callgrind for the given file and radius
        echo "Running Valgrind for file $FILE with radius $RADIUS..."
        valgrind --tool=callgrind ./blur $RADIUS "./data/$FILE" "./odata/$OUTPUT_FILE"
        
        # Optional: Sleep for a bit to avoid overwhelming the system
        sleep 2
    done
done

echo "All combinations of input files and radii have been processed!"
