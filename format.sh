clear
tempfile="fjiweopfqwejfpwq"
clang-format "$1" > "$tempfile"
cat "$tempfile" > "$1"
rm "$tempfile"
