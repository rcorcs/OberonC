./oberonc $1 -x86
gcc "${1%%.*}.s" -o "${1%%.*}"
