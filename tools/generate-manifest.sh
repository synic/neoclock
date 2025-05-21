#!/bin/bash
# Script to generate a manifest of Arduino libraries used in the project

set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ARDUINO_MANIFEST="$SCRIPT_DIR/arduino-manifest/arduino-manifest.pl"
PROJECT_DIR="$(cd "$SCRIPT_DIR/.." && pwd)"
MANIFEST_FILE="$PROJECT_DIR/manifest.txt"

# Check if the required variables are set
if [ -z "$1" ]; then
  echo "Usage: $0 <fqbn> [source_files...]"
  echo "Example: $0 arduino:avr:micro neoclock.ino"
  exit 1
fi

FQBN="$1"
shift
SOURCE_FILES="$@"

# If no source files are provided, use default
if [ -z "$SOURCE_FILES" ]; then
  SOURCE_FILES="$(find "$PROJECT_DIR" -name "*.ino" -o -name "*.h" | tr '\n' ' ')"
fi

echo "Generating manifest for FQBN: $FQBN"
echo "Source files: $SOURCE_FILES"

# First, create a simple version that just lists the includes
echo "# Arduino Library Dependencies" > "$MANIFEST_FILE"
echo "Generated on $(date)" >> "$MANIFEST_FILE"
echo "" >> "$MANIFEST_FILE"
echo "## Direct Includes" >> "$MANIFEST_FILE"

grep -h "#include" $SOURCE_FILES | sort | uniq >> "$MANIFEST_FILE"
echo "" >> "$MANIFEST_FILE"

# Now try to get detailed library information
echo "## Library Details" >> "$MANIFEST_FILE"
echo "Note: This section may be incomplete if arduino-manifest can't find all libraries." >> "$MANIFEST_FILE"
echo "" >> "$MANIFEST_FILE"

# Try to find library paths
USER_LIBS_PATH=$(arduino-cli config dump | grep "user:" -A 2 | grep "libraries:" | awk '{print $2}' || echo "")
IDE_LIBS_PATH=$(arduino-cli config dump | grep "directories:" -A 5 | grep "libraries:" | awk '{print $2}' || echo "")
DATA_DIR=$(arduino-cli config dump | grep "data:" | awk '{print $2}' || echo "")

# Build paths string
LIB_PATHS=""
[ -n "$USER_LIBS_PATH" ] && LIB_PATHS="$USER_LIBS_PATH"
[ -n "$IDE_LIBS_PATH" ] && LIB_PATHS="${LIB_PATHS:+$LIB_PATHS:}$IDE_LIBS_PATH"

# Try to find Arduino core libraries
if [ -n "$DATA_DIR" ]; then
  find "$DATA_DIR" -path "*/hardware/*/*/libraries" -type d | while read -r dir; do
    LIB_PATHS="${LIB_PATHS:+$LIB_PATHS:}$dir"
  done
fi

# Add common locations for good measure
for path in ~/Documents/Arduino/libraries /Applications/Arduino.app/Contents/Java/libraries; do
  if [ -d "$path" ]; then
    LIB_PATHS="${LIB_PATHS:+$LIB_PATHS:}$path"
  fi
done

echo "Using library paths: $LIB_PATHS" >&2

if [ -x "$ARDUINO_MANIFEST" ]; then
  # First try with library paths
  if [ -n "$LIB_PATHS" ]; then
    "$ARDUINO_MANIFEST" -l "$LIB_PATHS" -b "$FQBN" $SOURCE_FILES >> "$MANIFEST_FILE" 2>/dev/null || true
  fi
  
  # If that didn't add anything useful, try without -l
  if ! grep -q "Library Name" "$MANIFEST_FILE"; then
    echo "Retrying without library paths..." >&2
    "$ARDUINO_MANIFEST" -b "$FQBN" $SOURCE_FILES >> "$MANIFEST_FILE" 2>/dev/null || true
  fi
else
  echo "arduino-manifest.pl not found or not executable" >> "$MANIFEST_FILE"
  echo "Check that the git submodule is properly initialized with:" >> "$MANIFEST_FILE"
  echo "git submodule update --init --recursive" >> "$MANIFEST_FILE"
fi

# Finally, add the required libraries list
echo "" >> "$MANIFEST_FILE"
echo "## Required Libraries" >> "$MANIFEST_FILE"
echo "These libraries must be installed for the project to compile:" >> "$MANIFEST_FILE"
echo "" >> "$MANIFEST_FILE"

# Add install instructions for each required library
echo "### Installation" >> "$MANIFEST_FILE"
echo "To install the required libraries, run:" >> "$MANIFEST_FILE"
echo '```' >> "$MANIFEST_FILE"
echo "arduino-cli lib install \$(cat requirements.txt)" >> "$MANIFEST_FILE"
echo '```' >> "$MANIFEST_FILE"
echo "" >> "$MANIFEST_FILE"

echo "### Library List" >> "$MANIFEST_FILE"
cat "$PROJECT_DIR/requirements.txt" >> "$MANIFEST_FILE"

echo "Manifest generated at: $MANIFEST_FILE"