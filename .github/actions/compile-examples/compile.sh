set -e
SKETCH="$1"
BOARD="$2"
LIBS="$3"

HOME=/home/blues
# split the list of libraries by semi-colon
IFS=';'
read -ra libraries <<< "$LIBS"
for lib in "${libraries[@]}"; do arduino-cli lib install $lib; done

arduino-cli compile \
      --build-property compiler.cpp.extra_flags='-Werror -Wno-unused-variable -Wno-parentheses -Wno-sign-compare -Wno-unused-parameter' \
      --fqbn "$BOARD" \
      --log-level trace \
      --verbose \
      --warnings all \
      "$SKETCH"
