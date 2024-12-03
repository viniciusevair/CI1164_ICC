#!/bin/bash

declare -A METRIC_MAP
declare -A GP_FILE

# Define mappings
METRIC_MAP["FLOPS"]="FLOPS\_DP"
METRIC_MAP["tempo"]="milliseconds"
METRIC_MAP["L3"]="Memory bandwidth [MBytes/s]"
METRIC_MAP["L2CACHE"]="Cache miss ratio"
METRIC_MAP["ENERGY"]="Energy consumption [J]"

TITLE_MAP["matMat"]="Matrix-Matrix Multiplication"
TITLE_MAP["matVec"]="Matrix-Vector Multiplication"

for FILE_NAME in *.dat; do
    BASE_NAME=$(echo $FILE_NAME | cut -d'.' -f1)
    METRIC_FROM_FILENAME=$(echo $FILE_NAME | cut -d'_' -f1)
    OUTPUT_FILE=$BASE_NAME.png
    METRIC="${METRIC_MAP[$METRIC_FROM_FILENAME]}"

    if [[ $METRIC_FROM_FILENAME == "FLOPS" ]]; then
        MARKER=$(echo $BASE_NAME | cut -d'_' -f3)
        TITLE="${TITLE_MAP[$MARKER]}"
        echo "Plotting from $FILE_NAME with title \"$TITLE\" and metric \"$METRIC\"..."
        gnuplot -c plot_alt.gp "$FILE_NAME" "$TITLE" "$METRIC" "$OUTPUT_FILE"
    else
        MARKER=$(echo $BASE_NAME | cut -d'_' -f2)
        TITLE="${TITLE_MAP[$MARKER]}"
        echo "Plotting from $FILE_NAME with title \"$TITLE\" and metric \"$METRIC\"..."
        gnuplot -c plot.gp "$FILE_NAME" "$TITLE" "$METRIC" "$OUTPUT_FILE"
    fi
done
