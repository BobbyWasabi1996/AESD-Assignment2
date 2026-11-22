#!/bin/sh

if [ "$#" -ne 2 ]; then
    echo "Error: Two arguments required" >&2
    exit 1
fi

filesdir="$1"
searchstr="$2"

if [ ! -d "$filesdir" ]; then
    echo "Error: Directory does not exist" >&2
    exit 1
fi

# Count all regular files recursively
X=$(find "$filesdir" -type f -printf '.\n' | wc -l)

# Count lines containing the search string
Y=$(find "$filesdir" -type f \
    -exec grep -hF -- "$searchstr" {} + | wc -l)

echo "The number of files are $X and the number of matching lines are $Y"
