#!/bin/bash

if [ $# -eq 0 ]; then
    echo "Usage: $0 <svn-url>"
    exit 1
fi

URL="$1"
REPO_NAME=$(basename "$URL" | sed 's/\.svn$//')

if [ ! -d "libraries" ]; then
    mkdir libraries || {
        echo "Error: Failed to create 'libraries' directory"
        exit 1
    }
fi

if [ -d "libraries/$REPO_NAME" ]; then
    echo "Note: Directory 'libraries/$REPO_NAME' already exists. Skipping checkout."
    exit 0
fi

echo "Checking out $REPO_NAME..."
svn checkout "$URL" "libraries/$REPO_NAME" || {
    echo "Error: Failed to checkout $REPO_NAME repository"
    exit 1
}

echo "Successfully checked out $REPO_NAME"
