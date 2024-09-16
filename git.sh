#!/bin/bash

# Check if a commit message is provided
if [ -z "$1" ]; then
    echo "Error: No commit message provided."
    echo "Usage: ./git-commit-push.sh \"Your commit message here\""
    exit 1
fi

# Stage all changes
git add .

# Commit with the provided message
git commit -m "$1"

# Push to the repository
git push
