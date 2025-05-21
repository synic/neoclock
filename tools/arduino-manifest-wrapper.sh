#!/bin/bash
# Wrapper script for arduino-manifest.pl that automatically determines library paths

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ARDUINO_MANIFEST="$SCRIPT_DIR/arduino-manifest/arduino-manifest.pl"

# Check if arduino-manifest exists and is executable
if [ ! -x "$ARDUINO_MANIFEST" ]; then
  echo "Error: arduino-manifest.pl not found or not executable at $ARDUINO_MANIFEST" >&2
  exit 1
fi

# Extract Arduino library paths
USER_LIBS_PATH=$(arduino-cli config dump | grep "user:" -A 2 | grep "libraries:" | awk '{print $2}')
IDE_LIBS_PATH=$(arduino-cli config dump | grep "directories:" -A 5 | grep "libraries:" | awk '{print $2}')

# Check if paths were found
if [ -z "$USER_LIBS_PATH" ] || [ -z "$IDE_LIBS_PATH" ]; then
  echo "Warning: Could not determine Arduino library paths" >&2
  
  # Try to use default locations
  if [ -d "$HOME/Arduino/libraries" ]; then
    USER_LIBS_PATH="$HOME/Arduino/libraries"
  fi
  
  # Check for common IDE library locations
  for path in "/usr/local/share/arduino/libraries" "/Applications/Arduino.app/Contents/Java/libraries"; do
    if [ -d "$path" ]; then
      IDE_LIBS_PATH="$path"
      break
    fi
  done
fi

# Add Arduino core libraries directory if available
ARDUINO_CLI_DATA_DIR=$(arduino-cli config dump | grep "data:" | awk '{print $2}')
if [ -n "$ARDUINO_CLI_DATA_DIR" ]; then
  PACKAGES_DIR="$ARDUINO_CLI_DATA_DIR/packages"
  if [ -d "$PACKAGES_DIR" ]; then
    # Search for avr core libraries
    AVR_CORE_LIBS=$(find "$PACKAGES_DIR" -type d -path "*/hardware/avr/*/libraries" | head -1)
    if [ -n "$AVR_CORE_LIBS" ]; then
      CORE_LIBS_PATH="$AVR_CORE_LIBS"
    fi
  fi
fi

# Build library path string
LIB_PATHS=""
[ -n "$USER_LIBS_PATH" ] && LIB_PATHS="$USER_LIBS_PATH"
[ -n "$IDE_LIBS_PATH" ] && LIB_PATHS="${LIB_PATHS:+$LIB_PATHS:}$IDE_LIBS_PATH"
[ -n "$CORE_LIBS_PATH" ] && LIB_PATHS="${LIB_PATHS:+$LIB_PATHS:}$CORE_LIBS_PATH"

echo "Using Arduino Manifest: $ARDUINO_MANIFEST" >&2
echo "Using library paths: $LIB_PATHS" >&2

# Execute arduino-manifest with the determined paths
if [ -n "$LIB_PATHS" ]; then
  "$ARDUINO_MANIFEST" -l "$LIB_PATHS" "$@"
else
  # Fallback to running without -l if no paths were found
  "$ARDUINO_MANIFEST" "$@"
fi